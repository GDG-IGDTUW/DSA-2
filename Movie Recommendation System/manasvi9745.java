import java.util.*;

class MovieRecommendationSystem {

    // userId -> (movieId -> rating)
    private Map<Integer, Map<Integer, Integer>> userRatings;

    // movieId -> genre
    private Map<Integer, String> movies;

    public MovieRecommendationSystem() {
        userRatings = new HashMap<>();
        movies = new HashMap<>();
    }

    // Add new user
    void addUser(int userId) {
        userRatings.putIfAbsent(userId, new HashMap<>());
    }

    // Add new movie
    void addMovie(int movieId, String genre) {
        movies.put(movieId, genre);
    }

    // Rate a movie
    void rateMovie(int userId, int movieId, int rating) {
        if (!movies.containsKey(movieId)) return; // Movie must exist

        userRatings.putIfAbsent(userId, new HashMap<>());
        userRatings.get(userId).put(movieId, rating);
    }

    // Get recommendations using collaborative filtering
    List<Integer> getRecommendations(int userId) {

        List<Integer> recommendations = new ArrayList<>();

        if (!userRatings.containsKey(userId))
            return recommendations;

        Map<Integer, Integer> targetRatings = userRatings.get(userId);
        Map<Integer, Double> score = new HashMap<>();
        Map<Integer, Integer> count = new HashMap<>();

        // Compare with other users
        for (Map.Entry<Integer, Map<Integer, Integer>> entry : userRatings.entrySet()) {

            int otherUserId = entry.getKey();
            if (otherUserId == userId) continue;

            Map<Integer, Integer> otherRatings = entry.getValue();

            // Compute similarity
            int similarity = 0;

            for (Map.Entry<Integer, Integer> ratingEntry : targetRatings.entrySet()) {
                int movieId = ratingEntry.getKey();
                int rating = ratingEntry.getValue();

                if (otherRatings.containsKey(movieId)
                        && rating >= 4
                        && otherRatings.get(movieId) >= 4) {
                    similarity++;
                }
            }

            if (similarity == 0) continue;

            // Recommend movies
            for (Map.Entry<Integer, Integer> ratingEntry : otherRatings.entrySet()) {

                int movieId = ratingEntry.getKey();
                int rating = ratingEntry.getValue();

                if (!targetRatings.containsKey(movieId) && rating >= 4) {
                    score.put(movieId,
                            score.getOrDefault(movieId, 0.0) + similarity * rating);
                    count.put(movieId,
                            count.getOrDefault(movieId, 0) + 1);
                }
            }
        }

        // Convert to list for sorting
        List<Map.Entry<Integer, Double>> ranked =
                new ArrayList<>(score.entrySet());

        ranked.sort((a, b) -> Double.compare(b.getValue(), a.getValue()));

        for (Map.Entry<Integer, Double> entry : ranked) {
            recommendations.add(entry.getKey());
        }

        return recommendations;
    }

    // View user history
    List<Integer> viewUserHistory(int userId) {

        List<Integer> history = new ArrayList<>();

        if (!userRatings.containsKey(userId))
            return history;

        history.addAll(userRatings.get(userId).keySet());

        return history;
    }
}
