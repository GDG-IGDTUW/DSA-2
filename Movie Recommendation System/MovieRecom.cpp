#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class MovieRecommendationSystem {
    unordered_map<int, unordered_map<int, int>> userRatings;
    unordered_map<int, string> movies;

public:
    // add user
    void addUser(int userId) {
        userRatings[userId]={};
    }

    // add movie
    void addMovie(int movieId,string genre) {
        movies[movieId]=genre;
    }

    // rate movie
    void rateMovie(int userId,int movieId,int rating) {
        if(userRatings.find(userId)==userRatings.end())
            return;
        if(movies.find(movieId)==movies.end())
            return;
        userRatings[userId][movieId]=rating;
    }

    // recommend movies based on genre similarity
    vector<int> getRecommendations(int userId) {
        vector<int>res;
        if(userRatings.find(userId)==userRatings.end())
            return res;

        unordered_map<string,bool>likedGenres;

        // collect genres of highly rated movies
        for(auto &p:userRatings[userId]){
            if(p.second>=4){
                likedGenres[movies[p.first]]=true;
            }
        }

        // find movies with similar genres not yet rated
        for(auto &m:movies){
            int movieId=m.first;
            string genre=m.second;
            if(likedGenres[genre]&&
               userRatings[userId].find(movieId)==userRatings[userId].end()){
                res.push_back(movieId);
            }
        }

        return res;
    }

    // view user rating history
    vector<int> viewUserHistory(int userId) {
        vector<int>res;
        if(userRatings.find(userId)==userRatings.end())
            return res;
        for(auto &p:userRatings[userId])
            res.push_back(p.first);
        return res;
    }
};
