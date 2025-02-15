class MovieTheater:
    def __init__(self, name):
        self.name = name
        self.movies = {}  # Stores movie names and available seats

    def add_movie(self, movie_name, seats):
        """Adds a movie with available seats."""
        self.movies[movie_name] = seats
        print(f"Movie '{movie_name}' added with {seats} available seats.")

    def display_movies(self):
        """Displays available movies and their seat availability."""
        if not self.movies:
            print("No movies available.")
            return
        print("\nAvailable Movies:")
        for movie, seats in self.movies.items():
            print(f"{movie}: {seats} seats left")

    def book_ticket(self, movie_name, num_tickets):
        """Books tickets for a selected movie."""
        if movie_name not in self.movies:
            print("Movie not found.")
            return
        if self.movies[movie_name] < num_tickets:
            print("Not enough seats available.")
            return

        self.movies[movie_name] -= num_tickets
        print(f"Successfully booked {num_tickets} ticket(s) for '{movie_name}'.")

    def cancel_booking(self, movie_name, num_tickets):
        """Cancels a booking and restores the seats."""
        if movie_name not in self.movies:
            print("Movie not found.")
            return
        
        self.movies[movie_name] += num_tickets
        print(f"Canceled {num_tickets} ticket(s) for '{movie_name}'. Seats restored.")

# Main function to interact with the movie booking system
def main():
    theater = MovieTheater("CineWorld")

    while True:
        print("\n1. Add Movie\n2. Display Movies\n3. Book Ticket\n4. Cancel Booking\n5. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            movie_name = input("Enter movie name: ")
            seats = int(input("Enter number of seats available: "))
            theater.add_movie(movie_name, seats)

        elif choice == "2":
            theater.display_movies()

        elif choice == "3":
            movie_name = input("Enter movie name: ")
            num_tickets = int(input("Enter number of tickets to book: "))
            theater.book_ticket(movie_name, num_tickets)

        elif choice == "4":
            movie_name = input("Enter movie name: ")
            num_tickets = int(input("Enter number of tickets to cancel: "))
            theater.cancel_booking(movie_name, num_tickets)

        elif choice == "5":
            print("Exiting system.")
            break

        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main()
