import java.util.*;

class MovieRecommendationSystem {
    private Map<Integer, Map<Integer, Integer>> userRatings;
    private Map<Integer, String> movies;

    public MovieRecommendationSystem() {
        userRatings = new HashMap<>();
        movies = new HashMap<>();
    }

    void addUser(int userId) {
        if (!userRatings.containsKey(userId)) {
            userRatings.put(userId, new HashMap<>());
            System.out.println("User " + userId + " added.");
        }
    }

    void addMovie(int movieId, String genre) {
        if (!movies.containsKey(movieId)) {
            movies.put(movieId, genre);
            System.out.println("Movie " + movieId + " added with genre " + genre + ".");
        }
    }

    void rateMovie(int userId, int movieId, int rating) {
        if (!userRatings.containsKey(userId) || !movies.containsKey(movieId)) {
            return;
        }
        userRatings.get(userId).put(movieId, rating);
        System.out.println(
            "User " + userId + " rated Movie " + movieId + " with " + rating + "."
        );
    }

    List<Integer> getRecommendations(int userId) {
        List<Integer> recommendations = new ArrayList<>();

        if (!userRatings.containsKey(userId)) {
            return recommendations;
        }

        // Genres liked by the user (rating >= 4)
        Set<String> likedGenres = new HashSet<>();
        Map<Integer, Integer> ratings = userRatings.get(userId);

        for (Map.Entry<Integer, Integer> entry : ratings.entrySet()) {
            if (entry.getValue() >= 4) {
                likedGenres.add(movies.get(entry.getKey()));
            }
        }

        // Recommend unseen movies with similar genres
        for (Map.Entry<Integer, String> movie : movies.entrySet()) {
            int movieId = movie.getKey();
            String genre = movie.getValue();

            if (!ratings.containsKey(movieId) && likedGenres.contains(genre)) {
                recommendations.add(movieId);
            }
        }

        System.out.println("Recommendations for User " + userId + ": " + recommendations);
        return recommendations;
    }

    List<Integer> viewUserHistory(int userId) {
        List<Integer> history = new ArrayList<>();

        if (!userRatings.containsKey(userId)) {
            return history;
        }

        history.addAll(userRatings.get(userId).keySet());
        System.out.println("User " + userId + " watched: " + history);
        return history;
    }
}
