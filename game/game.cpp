#include <algorithm>
#include <iostream>
#include <vector>

#include <QString>

#include "common.h"
#include "game.h"

using namespace std;

std::ostream& operator<<( std::ostream& os, const QString& s)
{
  os << s.toStdString().c_str();
  return os;
}


Game::Game() {
  init();
}

void Game::init()
{
  if ( competitorTypes_.size() ) competitorTypes_.clear();
  if ( competitors_.size() ) competitors_.clear();
  if ( choiceTable_.size() ) choiceTable_.clear();
  if ( numberCompetitorsMap_.size() ) {
    numberCompetitorsMap_.clear();
  }
  for ( auto c : registeredCompetitors ) {
    numberCompetitorsMap_[ c.first ] = 0;
  }

  setIterations( 100 );
  setRandomSeed( 0 );
  nCompetitors_ = 0;

  choiceTable_ [ qMakePair( COOPERATE, COOPERATE ) ] = qMakePair (1,1);
  choiceTable_ [ qMakePair( COOPERATE, DEFECT) ] = qMakePair (0,2);
  choiceTable_ [ qMakePair( DEFECT, DEFECT) ] = qMakePair (0,0);
  choiceTable_ [ qMakePair( DEFECT, COOPERATE) ] = qMakePair (2,0);

}

void Game::registerCompetitorType(Competitor *competitor)
{
  competitorTypes_.push_back(competitor);
}

void Game::addCompetitor( const competitor_ptr& competitor )
{
  competitors_.push_back( competitor->create() );
  nCompetitors_ = competitors_.size();
  competitors_.back()->setGame(this);
  ++numberCompetitorsMap_ [ competitor->output() ];
}

void Game::setCompetitors( const vector<int>& nCompetitors )
{
  auto it = registeredCompetitors.begin();

  for ( auto i : nCompetitors) {
    for (int j = 0; j < i; j++ ) {
      addCompetitor( it->second );
    }
    it++;
  }
}

void Game::setCompetitors( const map<string, int>& nCompetitorsMap )
{
  for( auto it = nCompetitorsMap.begin(); it != nCompetitorsMap.end(); ++it ) {
    auto c = registeredCompetitors.find( QString().fromStdString(it->first) );
    if ( c != registeredCompetitors.end() ) {
      for ( int i = 0; i < it->second; i++ ) {
        addCompetitor( c->second );
      }
    } else {
      throw string( "Unknown competitor: ") + it->first;
    }
  }
}

void Game::setRandomSeed( int randomSeed ) {
  randomSeed_ = randomSeed;
  mersenne_twister.seed( randomSeed_);
};

int Game::getRandomSeed() const
{
  return randomSeed_;
}

QVector <int> Game::generateRandomIndices() const
{
  QVector <int> indices(nCompetitors_);
  for ( int i = 0; i < nCompetitors_; i++) {
    indices[i] = i;
  }
  QVector <int> output;
  for ( int i = nCompetitors_; i > 0; i-- ) {
    int index = irand(i);
    output.push_back( indices[index] );
    indices[ index ] = indices[ i - 1 ];
  }
  return output;
}

void Game::shuffleCompetitors()
{
  random_shuffle( competitors_.begin(), competitors_.end(), irand );
}

void Game::play( bool print_contests_csv )
{
  if ( print_contests_csv ) {
    csvHeader();
  }

  for ( int i = 0; i < nIterations_; i++ ) {
    executeRound(print_contests_csv);
  }
}

void Game::csvHeader()
{
  cout << "Match, Player1, Id1, Player2, Id2, Output1, Output2, Score1, Score2" << endl;
}

void Game::executeRound(bool print_contests_csv)
{
  QVector <int> indices = generateRandomIndices();
  for ( int j = 0; j < indices.size(); j += 2 ) {
    if ( j + 1 < indices.size() ) {
      auto player1 = indices[ j ];
      auto player2 = indices[ j + 1 ];
      auto decision1 = competitors_[ player1 ]->decision( player2 );
      auto decision2 = competitors_[ player2 ]->decision( player1 );
      auto scores = choiceTable_[ qMakePair( decision1, decision2 ) ];
      competitors_[ player1 ]->changeScore( scores.first );
      competitors_[ player2 ]->changeScore( scores.second );
      competitors_[ player1 ]->recordChoices( decision1, player2, decision2 );
      competitors_[ player2 ]->recordChoices( decision2, player1, decision1 );

      if ( print_contests_csv ) {
        QString name1 = competitors_[ player1 ]->output();
        QString name2 = competitors_[ player2 ]->output();
        QString output1 = (decision1 == COOPERATE) ? "COOPERATE" : "DEFECT";
        QString output2 = (decision2 == COOPERATE) ? "COOPERATE" : "DEFECT";

        cout << "Match, ";
        cout << ( (player1 < player2) ? name1 : name2 ) << ", ";
        cout << ( (player1 < player2) ? player1 :  player2 ) << ", ";
        cout << ( (player1 < player2) ? name2 : name1) << ", ";
        cout << ( (player1 < player2) ? player2 :  player1 ) << ", ";
        cout << ( (player1 < player2) ? output1 : output2) << ", ";
        cout << ( (player1 < player2) ? output2 : output1) << ", ";
        cout << ( (player1 < player2) ? scores.first : scores.second) << ", ";
        cout << ( (player1 < player2) ? scores.second : scores.first) << endl;
      }
    }
  }
}

int Game::minScore() const
{
  auto competitor = max_element( competitors_.begin(), competitors_.end(),
    [](const competitor_ptr& a, const competitor_ptr& b) {
      return ( a->getScore() > b->getScore() ) ? true : false;
    });
  return (*competitor)->getScore();
}

int Game::maxScore() const
{
  auto competitor = max_element( competitors_.begin(), competitors_.end(),
    [](const competitor_ptr& a, const competitor_ptr& b) {
      return ( a->getScore() < b->getScore() ) ? true : false;
    });
  return (*competitor)->getScore();
}

void Game::output() const
{
  // Print score for each competitor
  cout << "Score, Competitor, Index, Amount" << endl;
  for ( int i = 0; i < nCompetitors_; i++ ) {
    cout << "Score, ";
    cout << competitors_[i]->output() << ", " << i << ", "
            << competitors_[i]->getScore() << endl;
  }

  // Get minimum, maximum, median, mean, total and total on offer entry

  // Get maximum
  cout << "Statistics, Description, Competitor, Index, Amount" << endl;
  cout << "Statistics, Max, ";
  auto competitor = max_element( competitors_.begin(), competitors_.end(),
    [](const competitor_ptr& a, const competitor_ptr& b) {
      return ( a->getScore() < b->getScore() ) ? true : false;
    });
  cout << (*competitor)->output() << ", "
          << competitor - competitors_.begin() << ", "
          << (*competitor)->getScore() << endl;


  // Get minimum
  cout << "Statistics, Min, ";
  competitor = min_element( competitors_.begin(), competitors_.end(),
                            [](const competitor_ptr& a, const competitor_ptr& b) {

                              return ( a->getScore() < b->getScore() )
                                      ? true : false;
                            });
  cout << (*competitor)->output() << ", "
          << competitor - competitors_.begin() << ", "
          << (*competitor)->getScore() << endl;

  // Get total
  cout << "Statistics, Total, ";
  int total = 0;
  for ( auto competitor : competitors_ ) {
    total += competitor->getScore();
  }
  cout << ", "
          << ", "
          << total << endl;


  // Get maximum possible total

  cout << "Statistics, MaxTotal, ";
  cout << ", "
          << ", "
          << competitors_.size() * nIterations_  << endl;

  // Get mean
  cout << "Statistics, Mean, ";
  int mean = total / competitors_.size();
  cout << ", "
          << ", "
          << mean << endl;

  // Get median
  cout << "Statistics, Median, ";
  QVector < competitor_ptr > c;
  copy ( competitors_.begin(), competitors_.end(), back_inserter(c) );
  sort( c.begin(), c.end(),
        [] (const competitor_ptr& a, const competitor_ptr& b) {
          return a->getScore() < b->getScore();
        });
  int median;
  if ( c.size() % 2 == 1 || c.size() < 2 ) {
    median = c[ c.size() / 2 ]->getScore();
  } else {
    median = (c[ c.size() / 2 ]->getScore() +
             c[ c.size() / 2 + 1 ]->getScore() ) / 2;
  }
  cout << ", "
          << ", "
          << median << endl;
}

int Game::getRank(int score) const
{
  int ranking = 0;
  for( auto it = competitors_.begin(); it != competitors_.end(); it++ )
    if ( (*it)->getScore() > score ) ++ranking;
  return ranking;
}
