# Movie Recommendation System (C++)

## Overview

This is a simple movie recommendation system implemented in C++ using collaborative filtering.

It:
- Stores user ratings
- Stores movie genres
- Recommends movies liked by similar users
- Allows viewing user history

---

## Data Structures Used

- `unordered_map<int, unordered_map<int, int>> userRatings`
  - Stores user → (movie → rating)
- `unordered_map<int, string> movies`
  - Stores movie → genre

---

## Implementation

```cpp
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class MovieRecommendationSystem {
    // userId -> (movieId -> rating)
    unordered_map<int, unordered_map<int, int>> userRatings;

    // movieId -> genre
    unordered_map<int, string> movies;

public:
    void addUser(int userId) {
        if (userRatings.find(userId) == userRatings.end()) {
            userRatings[userId] = unordered_map<int, int>();
        }
    }

    void addMovie(int movieId, string genre) {
        movies[movieId] = genre;
    }

    void rateMovie(int userId, int movieId, int rating) {
        if (movies.find(movieId) == movies.end()) return; // movie must exist
        userRatings[userId][movieId] = rating;
    }

    vector<int> getRecommendations(int userId) {
        vector<int> recommendations;

        if (userRatings.find(userId) == userRatings.end())
            return recommendations;

        unordered_map<int, int>& targetRatings = userRatings[userId];
        unordered_map<int, double> score;
        unordered_map<int, int> count;

        // Compare with other users
        for (auto& [otherUserId, otherRatings] : userRatings) {
            if (otherUserId == userId) continue;

            // Compute similarity (number of common movies rated >=4)
            int similarity = 0;
            for (auto& [movieId, rating] : targetRatings) {
                if (otherRatings.count(movieId) && rating >= 4 && otherRatings[movieId] >= 4) {
                    similarity++;
                }
            }

            if (similarity == 0) continue;

            // Recommend movies other user liked but target hasn't seen
            for (auto& [movieId, rating] : otherRatings) {
                if (!targetRatings.count(movieId) && rating >= 4) {
                    score[movieId] += similarity * rating;
                    count[movieId]++;
                }
            }
        }

        // Convert to sortable vector
        vector<pair<int, double>> ranked;
        for (auto& [movieId, totalScore] : score) {
            ranked.push_back({movieId, totalScore});
        }

        sort(ranked.begin(), ranked.end(),
             [](auto& a, auto& b) {
                 return a.second > b.second;
             });

        for (auto& [movieId, _] : ranked) {
            recommendations.push_back(movieId);
        }

        return recommendations;
    }

    vector<int> viewUserHistory(int userId) {
        vector<int> history;

        if (userRatings.find(userId) == userRatings.end())
            return history;

        for (auto& [movieId, _] : userRatings[userId]) {
            history.push_back(movieId);
        }

        return history;
    }
};
```
---

### Time Complexity

- Adding user/movie: O(1)

- Rating movie: O(1)

- Getting recommendations: O(U × M)
(Where U = users, M = movies rated)
