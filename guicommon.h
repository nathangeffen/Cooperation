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

#ifndef GUICOMMON_H
#define GUICOMMON_H

/** Determines how GUI displays competitors.
 *
 ** \enum DisplayMethodology enum has three values:
 * RATIO Display each competitor's size relative to its points.
 * RATIO_WITH_MIN_AT_0 Same as ratio except subtract the lowest score from
 *  every competitor.
 * RANK: Display each competitor's size relative to its rank.
 */

enum DisplayMethodology {
  RATIO = 0,
  RATIO_WITH_MIN_AT_0,
  RANK
};

#endif // GUICOMMON_H
