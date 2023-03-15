#include "pickTopTitles.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int PickTopTitles(const std::string &filename,
                  std::vector<std::tuple<std::string, float>> &topTitlesWithRating,
                  std::tuple<std::string, float> &titleFromLastTop) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error in open rating filename" << std::endl;
        return FILE_NOT_OPEN;
    }

    std::string first_line;
    getline(file, first_line);

    std::string titleIdFromLastTop = std::get<0>(titleFromLastTop);
    float titleRatingFromLastTop = std::get<1>(titleFromLastTop);

    // if id of titleFromLastTop is empty then we pick the best titles. else we use top rule
    bool wasTitleFromLastTop = titleIdFromLastTop.empty();

    std::string titleID, averageRating, numVotes;
    while (!file.eof()) {
        getline(file, titleID, '\t');
        getline(file, averageRating, '\t');
        getline(file, numVotes);

        if (titleID == "\\N" || averageRating == "\\N" || numVotes == "\\N") {
            continue;
        }
        if (std::stoi(numVotes) < MIN_VOTES) {
            continue;
        }

        if (titleIdFromLastTop == titleID) {
            wasTitleFromLastTop = true;
        }

        float titleRating = std::stof(averageRating);

        // if this title was in past top then skip it. top rule is in .hpp file
        if (titleRating > titleRatingFromLastTop) {
            continue;
        } else if (!wasTitleFromLastTop && titleRatingFromLastTop == titleRating) {
            continue;
        }

        if (topTitlesWithRating.size() == PICKED_TOP_AMOUNT) {
            // comparing last elem of topTitlesWithRating and titleRating of current title
            if (std::get<1>(topTitlesWithRating[PICKED_TOP_AMOUNT - 1]) < titleRating) {
                topTitlesWithRating.pop_back();
            } else {
                // if rating so little we skip this title
                continue;
            }
        }

        InsertRatingToTop(topTitlesWithRating, titleID, titleRating);
    }
    file.close();
    return 0;
}

int InsertRatingToTop(std::vector<std::tuple<std::string, float>> &topTitlesWithRating, std::string &titleID,
                      float titleRating) {
    // binary search of right place for insertion
    auto insertIter = std::lower_bound(topTitlesWithRating.begin(), topTitlesWithRating.end(), titleRating,
                                       [](const std::tuple<std::string, float> &title, float rating) {
                                           return std::get<1>(title) >= rating;
                                       });

    int insertionIndex = insertIter - topTitlesWithRating.begin();

    // firstly point to current title, after swap help not lose some title
    auto titleForInsert = std::make_tuple(titleID, titleRating);

    // sequentially move all elements of vector. we begin from insert current title
    for (int i = insertionIndex; i < topTitlesWithRating.size(); ++i) {
        std::swap(topTitlesWithRating[i], titleForInsert);
    }

    topTitlesWithRating.push_back(titleForInsert);
    return 0;
}
