#ifndef PLAYER_H
#define PLAYER_H

#include <QtGui>
#include "guicommon.h"

class Competitor;
class QLabel;
class QHBoxLayout;
class QGridLayout;
class CompetitorShape;

/** Manages the widget used to represent a competitor.
  */

class CompetitorWidget: public QWidget
{
  Q_OBJECT

public:

  /** Constructs the widget.
    * @param[in] maxDiameter the maximum diameter of the shape of the widget.
    * @param[in] competitor associated with this widget.
    * @param[in] displayMethodology how to display the competitors relative to
    *                               each others scores.
    * @param[in] color of the widget
    */
  CompetitorWidget(int maxDiameter,
                   Competitor& competitor,
                   DisplayMethodology displayMethodology,
                   QColor color,
                   QWidget *parent = 0);

public slots:
  void executeUpdate(int min_score, int max_score, bool updateScore);

private:
  Competitor& competitor_;
  CompetitorShape* competitorShape_;
  QHBoxLayout *topline_;
  QGridLayout *layout_;
  QLabel *nameLabel_;
  QLabel *scoreLabel_;
  int maxDiameter_;
  int maxScore_;
  int minScore_;
  int savedScore_;
  bool updateScore_;
  DisplayMethodology displayMethodology_;
  QColor color_;

  /** Updates the shape using the ratio method.
    *
    * See the DisplayMethodology enum.
    */
  void updateUsingRatio();

  /** The maximum score in the game is needed by this widget so that its size and
    * shape can be calculated.
    */
  void setMaxScore( int max_score ) { maxScore_ = max_score; }

  /** The minimum score in the game is needed by this widget so that its size
    * can be calculated.
    */
  void setMinScore( int min_score ) { minScore_ = min_score; }

  /** Updates the shape using the rank method.
    *
    * See the DisplayMethodology enum.
    */
  void updateUsingRank();

  /** Updates the shape using the ratio normalized to zero method.
    *
    * See the DisplayMethodology enum.
    */
  void updateUsingRatioNormalizedToZero();

};

#endif // PLAYER_H
