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
