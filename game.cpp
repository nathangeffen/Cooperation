#include <algorithm>
#include "game.h"

Game::Game(int nIterations, int nCompetitors) :
  nIterations_ (nIterations),
  nCompetitors_ (nCompetitors)
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

void Game::setCompetitors()
{
  int size = competitorTypes_.size();
  for ( int i = 0; i < nCompetitors_; i++ ) {
    int rand = irand();
    int index = rand % size;
    Competitor* c = competitorTypes_[ index ]->copyTo();
    competitors_.push_back(c);
  }
}

QVector <int> Game::generateRandomIndices()
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
  consout << "Match, Player1, Id1, Player2, Id2, Output1, Output2, Score1, Score2" << endl;
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

        consout << "Match, ";
        consout << ( (player1 < player2) ? name1 : name2 ) << ", ";
        consout << ( (player1 < player2) ? player1 :  player2 ) << ", ";
        consout << ( (player1 < player2) ? name2 : name1) << ", ";
        consout << ( (player1 < player2) ? player2 :  player1 ) << ", ";
        consout << ( (player1 < player2) ? output1 : output2) << ", ";
        consout << ( (player1 < player2) ? output2 : output1) << ", ";
        consout << ( (player1 < player2) ? scores.first : scores.second) << ", ";
        consout << ( (player1 < player2) ? scores.second : scores.first) << endl;
      }
    }
  }
}

void Game::output()
{
  // Print score for each competitor
  consout << "Score, Competitor, Index, Amount" << endl;
  for ( int i = 0; i < nCompetitors_; i++ ) {
    consout << "Score, ";
    consout << competitors_[i]->output() << ", " << i << ", "
            << competitors_[i]->getScore() << endl;
  }

  // Get minimum, maximum, median, mean, total and total on offer entry

  // Get maximum
  consout << "Statistics, Description, Competitor, Index, Amount" << endl;
  consout << "Statistics, Max, ";
  auto competitor = std::max_element( competitors_.begin(), competitors_.end(),
                            [](const Competitor* a, const Competitor* b) {
                              return ( a->getScore() < b->getScore() )
                                      ? true : false;
                            });
  consout << (*competitor)->output() << ", "
          << competitor - competitors_.begin() << ", "
          << (*competitor)->getScore() << endl;


  // Get minimum
  consout << "Statistics, Min, ";
  competitor = std::min_element( competitors_.begin(), competitors_.end(),
                            [](const Competitor* a, const Competitor* b) {
                              return ( a->getScore() < b->getScore() )
                                      ? true : false;
                            });
  consout << (*competitor)->output() << ", "
          << competitor - competitors_.begin() << ", "
          << (*competitor)->getScore() << endl;

  // Get total
  consout << "Statistics, Total, ";
  int total = 0;
  for ( auto competitor : competitors_ ) {
    total += competitor->getScore();
  }
  consout << ", "
          << ", "
          << total << endl;


  // Get maximum possible total

  consout << "Statistics, MaxTotal, ";
  consout << ", "
          << ", "
          << competitors_.size() * nIterations_  << endl;

  // Get mean
  consout << "Statistics, Mean, ";
  int mean = total / competitors_.size();
  consout << ", "
          << ", "
          << mean << endl;

  // Get median
  consout << "Statistics, Median, ";
  std::sort( competitors_.begin(), competitors_.end(),
        [] (const Competitor* a, const Competitor* b) {
          return a->getScore() < b->getScore();
        });
  int median;
  if ( competitors_.size() % 2 == 1 || competitors_.size() < 2 ) {
    median = competitors_[ competitors_.size() / 2 ]->getScore();
  } else {
    median = (competitors_[ competitors_.size() / 2 ]->getScore() +
             competitors_[ competitors_.size() / 2 + 1 ]->getScore() ) / 2;
  }
  consout << ", "
          << ", "
          << median << endl;
}

