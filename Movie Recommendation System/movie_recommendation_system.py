class MovieRecommendationSystem:
    def __init__(self):
        self.users = set()                 
        self.movies = {}                 
        self.ratings = {}                 

    def add_user(self, user_id):
        self.users.add(user_id)
        self.ratings[user_id] = {}
        print(f"User {user_id} added.")

    def add_movie(self, movie_id, genre):
        self.movies[movie_id] = genre
        print(f"Movie {movie_id} added with genre {genre}.")

    def rate_movie(self, user_id, movie_id, rating):
        if user_id not in self.users:
            print("User not found.")
            return

        if movie_id not in self.movies:
            print("Movie not found.")
            return

        self.ratings[user_id][movie_id] = rating
        print(f"User {user_id} rated Movie {movie_id} with {rating}.")

    def get_recommendations(self, user_id):
        if user_id not in self.users:
            print("User not found.")
            return []

        liked_genres = set()

        for movie_id, rating in self.ratings[user_id].items():
            if rating >= 4:
                liked_genres.add(self.movies[movie_id])

        watched = set(self.ratings[user_id].keys())
        recommendations = []

        for movie_id, genre in self.movies.items():
            if movie_id not in watched and genre in liked_genres:
                recommendations.append(movie_id)

        print(f"Recommendations for User {user_id}: {recommendations}")
        return recommendations

    def view_user_history(self, user_id):
        if user_id not in self.users:
            print("User not found.")
            return

        watched = list(self.ratings[user_id].keys())
        print(f"User {user_id} watched: {watched}")
        return watched

# Example usage
system = MovieRecommendationSystem()

system.add_user(1)
system.add_user(2)

system.add_movie(101, "Action")
system.add_movie(102, "Drama")

system.rate_movie(1, 101, 5)
system.rate_movie(2, 101, 4)
system.rate_movie(2, 102, 5)

system.get_recommendations(1)
system.view_user_history(1)
