#include <algorithm>
#include <iostream>
#include "common.h"
#include "game.h"

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
}

void Game::setCompetitors()
{
  int size = competitorTypes_.size();
  for ( int i = 0; i < nCompetitors_; i++ ) {
    int rand = irand();
    int index = rand % size;
    auto c = competitorTypes_[ index ]->create();
    competitors_.push_back(c);
  }
}

QVector <int> Game::generateRandomIndices() const
{
  QVector <int> indices(nCompetitors_);
  for ( int i = 0; i < nCompetitors_; i++) {
    indices[i] = i;
  }
  QVector <int> output;
  for ( int i = nCompetitors_; i > 0; i-- ) {
    int index = irand() % i;
    output.push_back( indices[index] );
    indices[ index ] = indices[ i - 1 ];
  }
  return output;
}

void Game::play()
{
  std::cout << "Match, Player1, Id1, Player2, Id2, Output1, Output2, Score1, Score2" << std::endl;
  for ( int i = 0; i < nIterations_; i++ ) {
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

        QString name1 = competitors_[ player1 ]->output();
        QString name2 = competitors_[ player2 ]->output();
        QString output1 = (decision1 == COOPERATE) ? "COOPERATE" : "DEFECT";
        QString output2 = (decision2 == COOPERATE) ? "COOPERATE" : "DEFECT";

        std::cout << "Match, ";
        std::cout << ( (player1 < player2) ? name1 : name2 ) << ", ";
        std::cout << ( (player1 < player2) ? player1 :  player2 ) << ", ";
        std::cout << ( (player1 < player2) ? name2 : name1) << ", ";
        std::cout << ( (player1 < player2) ? player2 :  player1 ) << ", ";
        std::cout << ( (player1 < player2) ? output1 : output2) << ", ";
        std::cout << ( (player1 < player2) ? output2 : output1) << ", ";
        std::cout << ( (player1 < player2) ? scores.first : scores.second) << ", ";
        std::cout << ( (player1 < player2) ? scores.second : scores.first) << std::endl;
      }
    }
  }
}

void Game::output() const
{
  // Print score for each competitor
  std::cout << "Score, Competitor, Index, Amount" << std::endl;
  for ( int i = 0; i < nCompetitors_; i++ ) {
    std::cout << "Score, ";
    std::cout << competitors_[i]->output() << ", " << i << ", "
            << competitors_[i]->getScore() << std::endl;
  }

  // Get minimum, maximum, median, mean, total and total on offer entry

  // Get maximum
  std::cout << "Statistics, Description, Competitor, Index, Amount" << std::endl;
  std::cout << "Statistics, Max, ";
  auto competitor = std::max_element( competitors_.begin(), competitors_.end(),
                            [](const competitor_ptr& a, const competitor_ptr& b) {
                              return ( a->getScore() < b->getScore() )
                                      ? true : false;
                            });
  std::cout << (*competitor)->output() << ", "
          << competitor - competitors_.begin() << ", "
          << (*competitor)->getScore() << std::endl;


  // Get minimum
  std::cout << "Statistics, Min, ";
  competitor = std::min_element( competitors_.begin(), competitors_.end(),
                            [](const competitor_ptr& a, const competitor_ptr& b) {

                              return ( a->getScore() < b->getScore() )
                                      ? true : false;
                            });
  std::cout << (*competitor)->output() << ", "
          << competitor - competitors_.begin() << ", "
          << (*competitor)->getScore() << std::endl;

  // Get total
  std::cout << "Statistics, Total, ";
  int total = 0;
  for ( auto competitor : competitors_ ) {
    total += competitor->getScore();
  }
  std::cout << ", "
          << ", "
          << total << std::endl;


  // Get maximum possible total

  std::cout << "Statistics, MaxTotal, ";
  std::cout << ", "
          << ", "
          << competitors_.size() * nIterations_  << std::endl;

  // Get mean
  std::cout << "Statistics, Mean, ";
  int mean = total / competitors_.size();
  std::cout << ", "
          << ", "
          << mean << std::endl;

  // Get median
  std::cout << "Statistics, Median, ";
  QVector < competitor_ptr > c;
  copy ( competitors_.begin(), competitors_.end(), back_inserter(c) );
  std::sort( c.begin(), c.end(),
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
  std::cout << ", "
          << ", "
          << median << std::endl;
}

