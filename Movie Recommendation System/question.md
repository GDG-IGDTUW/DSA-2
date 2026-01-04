# Movie Recommendation System

## Problem Statement

Design a Movie Recommendation System that suggests movies to users based on their preferences and ratings.  
The system should support basic user and movie management along with personalized recommendations.

The recommendation logic should be **content-based**, using similarity between movies based on genres.

---

## Functional Requirements

1. **Add User**  
   Register a new user with a unique user ID.

2. **Add Movie**  
   Add a movie with a unique movie ID, title, and genres.

3. **Rate Movie**  
   Allow users to rate movies on a scale of 1 to 5.

4. **Movie Recommendation**  
   Recommend movies to a user based on similarity of genres with movies the user has rated highly.

5. **View User Ratings**  
   Display all movies rated by a user.
---
## Input Format

Operations are provided as function calls.

### Operations

- `addUser(user_id)`
- `addMovie(movie_id, title, genres)`
- `rateMovie(user_id, movie_id, rating)`
- `getRecommendations(user_id)`
- `viewRatings(user_id)`

---
## Example Input:
addUser(1)
addUser(2)
addMovie(101, Action)
addMovie(102, Drama)
rateMovie(1, 101, 5)
rateMovie(2, 101, 4)
rateMovie(2, 102, 5)
getRecommendations(1)
viewUserHistory(1)

## Example Output:
User 1 added.
User 2 added.
Movie 101 added with genre Action.
Movie 102 added with genre Drama.
User 1 rated Movie 101 with 5.
User 2 rated Movie 101 with 4.
User 2 rated Movie 102 with 5.
Recommendations for User 1: [102]
User 1 watched: [101]

## Concepts Used

- Hash Maps: Store users, movies, and ratings efficiently.
- Sets / Lists: Track watched movies.
- Similarity Logic:Users with common rated movies.
                   Genre-based filtering.
- Basic Recommendation Logic (No ML required).

## Constraints

- 1 ≤ Users ≤ 10,000  
- 1 ≤ Movies ≤ 50,000  
- Ratings range: 1–5  
- Optimize recommendation lookup.

