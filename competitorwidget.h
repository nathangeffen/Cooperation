/* This source file is part of Cooperation, an implementation of the 
 * Prisoner's Dilemna game.
 *
 * Copyright (C) 2012 by Nathan Geffen 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
