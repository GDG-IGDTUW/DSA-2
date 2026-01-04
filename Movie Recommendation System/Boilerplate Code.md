## Python
```
class MovieRecommendationSystem:
    def __init__(self):
        self.users = {}
        self.movies = {}
        self.ratings = {}

    def add_user(self, user_id):
        pass

    def add_movie(self, movie_id, genre):
        pass

    def rate_movie(self, user_id, movie_id, rating):
        pass

    def get_recommendations(self, user_id):
        pass

    def view_user_history(self, user_id):
        pass
```
-----

## C++
```
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class MovieRecommendationSystem {
    unordered_map<int, unordered_map<int, int>> userRatings;
    unordered_map<int, string> movies;

public:
    void addUser(int userId) {
    }

    void addMovie(int movieId, string genre) {
    }

    void rateMovie(int userId, int movieId, int rating) {
    }

    vector<int> getRecommendations(int userId) {
        return {};
    }

    vector<int> viewUserHistory(int userId) {
        return {};
    }
};
```
----

## JAVA
```
import java.util.*;

class MovieRecommendationSystem {
    private Map<Integer, Map<Integer, Integer>> userRatings;
    private Map<Integer, String> movies;

    public MovieRecommendationSystem() {
        userRatings = new HashMap<>();
        movies = new HashMap<>();
    }

    void addUser(int userId) {
    }

    void addMovie(int movieId, String genre) {
    }

    void rateMovie(int userId, int movieId, int rating) {
    }

    List<Integer> getRecommendations(int userId) {
        return new ArrayList<>();
    }

    List<Integer> viewUserHistory(int userId) {
        return new ArrayList<>();
    }
}
```
