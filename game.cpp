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
    int rand = qrand();
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
    int index = qrand() % i;
    output.push_back( indices[index] );
    indices[ index ] = indices[ i - 1 ];
  }
  return output;
}

void Game::play()
{
  for ( int i = 0; i < nIterations_; i++ ) {
    QVector <int> indices = generateRandomIndices();

    for ( int j = 0; j < indices.size(); j += 2 ) {
      if ( j + 1 < indices.size() ) {
        auto player1 = indices[ j ];
        auto player2 = indices[ j + 1 ];
        auto output1 = competitors_[ player1 ]->decision( player2 );
        auto output2 = competitors_[ player2 ]->decision( player1 );
        auto scores = choiceTable_[ qMakePair( output1, output2 ) ];
        competitors_[ player1 ]->changeScore( scores.first );
        competitors_[ player2 ]->changeScore( scores.second );
        competitors_[ player1 ]->recordChoices( output1, player2, output2 );
        competitors_[ player2 ]->recordChoices( output2, player1, output1 );

        QString player1Name = competitors_[ player1 ]->output() + "["
                              + QString::number(player1)+ "]";
        QString player2Name = competitors_[ player2 ]->output() + "["
                              + QString::number(player2)+ "]";
        qDebug();
        qDebug() << "Contest between" << player1Name
                 << "and" << player2Name;
        qDebug() << player1Name << "decides to"
                 << ((output1 == COOPERATE) ? "COOPERATE" : "DEFECT");
        qDebug() << player2Name << "decides to"
                 << ((output2 == COOPERATE) ? "COOPERATE" : "DEFECT");
        qDebug() << player1Name << "scores" << scores.first;
        qDebug() << player2Name << "scores" << scores.second;
        qDebug();
      }
    }
  }
}

void Game::output()
{
  for (auto competitor : competitors_ ) {
    qDebug() << competitor->output() << ": "
             << competitor->getScore();
  }
}

