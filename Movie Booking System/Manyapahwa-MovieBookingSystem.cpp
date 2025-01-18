#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

class MovieBookingSystem {
private:
    struct Movie {
        string name;
        string showtime;
        int seats;
        int maxSeats; // To track maximum seat capacity for cancellation
    };
    unordered_map<string, Movie> movies;

public:
    // Add a movie with details
    void addMovie(string name, string showtime, int seats) {
        if (movies.find(name) != movies.end()) {
            cout << "Movie already exists. Use a unique movie name." << endl;
            return;
        }
        if (seats <= 0) {
            cout << "Seats must be greater than 0." << endl;
            return;
        }
        movies[name] = {name, showtime, seats, seats};
        cout << "Movie added successfully." << endl;
    }

    // Book a ticket for a specific movie
    void bookTicket(string name) {
        if (movies.find(name) != movies.end() && movies[name].seats > 0) {
            movies[name].seats--;
            cout << "Booking confirmed. Seats Left: " << movies[name].seats << endl;
        } else if (movies.find(name) != movies.end()) {
            cout << "Booking failed. No seats available." << endl;
        } else {
            cout << "Movie not found. Please check the movie name." << endl;
        }
    }

    // Cancel a ticket for a specific movie
    void cancelTicket(string name) {
        if (movies.find(name) != movies.end()) {
            if (movies[name].seats < movies[name].maxSeats) {
                movies[name].seats++;
                cout << "Ticket canceled. Seats Left: " << movies[name].seats << endl;
            } else {
                cout << "Cancellation failed. No tickets to cancel." << endl;
            }
        } else {
            cout << "Movie not found. Please check the movie name." << endl;
        }
    }

    // View all available shows
    void viewAvailableShows() {
        if (movies.empty()) {
            cout << "No movies available." << endl;
            return;
        }
        for (const auto& pair : movies) {
            const Movie& movie = pair.second;
            cout << movie.name << " - Showtime: " << movie.showtime << " - Seats Left: " << movie.seats << endl;
        }
    }

    // Search for a movie by its name
    void searchMovie(string name) {
        auto it = movies.find(name);
        if (it != movies.end()) {
            const Movie& movie = it->second;
            cout << "Movie Found: " << movie.name << " - Showtime: " << movie.showtime << " - Seats Left: " << movie.seats << endl;
        } else {
            cout << "Movie not found." << endl;
        }
    }
};

int main() {
    MovieBookingSystem system;

    // Menu-driven interface
    while (true) {
        cout << "\n--- Movie Booking System ---\n";
        cout << "1. Add Movie\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. View Available Shows\n";
        cout << "5. Search Movie by Name\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        string name, showtime;
        int seats, target;

        switch (choice) {
            case 1:
                cout << "Enter movie name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter showtime: ";
                getline(cin, showtime);
                cout << "Enter number of seats: ";
                cin >> seats;
                system.addMovie(name, showtime, seats);
                break;
            case 2:
                cout << "Enter movie name to book a ticket: ";
                cin.ignore();
                getline(cin, name);
                system.bookTicket(name);
                break;
            case 3:
                cout << "Enter movie name to cancel a ticket: ";
                cin.ignore();
                getline(cin, name);
                system.cancelTicket(name);
                break;
            case 4:
                system.viewAvailableShows();
                break;
            case 5:
                cout << "Enter movie name to search: ";
                cin.ignore();
                getline(cin, name);
                system.searchMovie(name);
                break;
            case 6:
                cout << "Exiting the system. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
