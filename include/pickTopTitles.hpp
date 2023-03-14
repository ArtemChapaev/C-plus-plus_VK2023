#pragma once

#include <string>
#include <tuple>
#include <vector>

const int MIN_VOTES = 1000;
const int PICKED_TOP_AMOUNT = 500;

int PickTopTitles(const std::string &filename,
                  std::vector<std::tuple<std::string, float>> &topTitlesWithRating,
                  std::tuple<std::string, float> &titleFromLastTop);
/// Parameters - filename with ratings, empty vector of top pair "titleID-averageRating",
/// tuple that describe last top for selection best titles. Return values - 0 or error.
/// Top rule: will be higher title with higher rating. For two title with one rating, first will be higher.

int InsertRatingToTop(std::vector<std::tuple<std::string, float>> &topTitlesWithRating, std::string &titleID,
                      float titleRating);
/// Parameters - vector of top pair "titleID-averageRating", info about current title.
/// Return values - 0 or error.
/// Insert current title into TitlesWithRating. Keep TitlesWithRating always in order.
