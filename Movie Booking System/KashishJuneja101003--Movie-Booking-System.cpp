#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

class MovieBookingSystem {
private:
    struct Movie {
        string name;
        string showtime;
        int totalPremiumSeats;
        int availablePremiumSeats;
        int totalRegularSeats;
        int availableRegularSeats;
    };

    unordered_map<string, Movie> movies;

public:
    void addMovie(const string& name, const string& showtime, int premiumSeats, int regularSeats) {
        if (movies.find(name) != movies.end()) {
            cout << "Movie already exists. Use a different name." << endl;
            return;
        }
        movies[name] = {name, showtime, premiumSeats, premiumSeats, regularSeats, regularSeats};
        cout << "Movie '" << name << "' added successfully with " << premiumSeats << " premium seats and "
             << regularSeats << " regular seats." << endl;
    }

    void bookTicket(const string& name, int numTickets, bool isPremium) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        Movie& movie = movies[name];

        if (isPremium) {
            if (movie.availablePremiumSeats >= numTickets) {
                movie.availablePremiumSeats -= numTickets;
                cout << "Booking confirmed for " << numTickets << " premium seat(s). Remaining premium seats: "
                     << movie.availablePremiumSeats << endl;
            } else {
                cout << "Not enough premium seats available. Only " << movie.availablePremiumSeats << " left." << endl;
            }
        } else {
            if (movie.availableRegularSeats >= numTickets) {
                movie.availableRegularSeats -= numTickets;
                cout << "Booking confirmed for " << numTickets << " regular seat(s). Remaining regular seats: "
                     << movie.availableRegularSeats << endl;
            } else {
                cout << "Not enough regular seats available. Only " << movie.availableRegularSeats << " left." << endl;
            }
        }
    }

    void cancelTicket(const string& name, int numTickets, bool isPremium) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        Movie& movie = movies[name];

        if (isPremium) {
            if (movie.availablePremiumSeats + numTickets <= movie.totalPremiumSeats) {
                movie.availablePremiumSeats += numTickets;
                cout << "Cancellation successful. Remaining premium seats: " << movie.availablePremiumSeats << endl;
            } else {
                cout << "Invalid cancellation. Cannot exceed original premium seat count of "
                     << movie.totalPremiumSeats << "." << endl;
            }
        } else {
            if (movie.availableRegularSeats + numTickets <= movie.totalRegularSeats) {
                movie.availableRegularSeats += numTickets;
                cout << "Cancellation successful. Remaining regular seats: " << movie.availableRegularSeats << endl;
            } else {
                cout << "Invalid cancellation. Cannot exceed original regular seat count of "
                     << movie.totalRegularSeats << "." << endl;
            }
        }
    }

    void deleteMovie(const string& name) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        Movie& movie = movies[name];
        if (movie.availablePremiumSeats == movie.totalPremiumSeats &&
            movie.availableRegularSeats == movie.totalRegularSeats) {
            movies.erase(name);
            cout << "Movie '" << name << "' deleted successfully." << endl;
        } else {
            cout << "Movie cannot be deleted. Some tickets have been booked." << endl;
        }
    }

    void viewAvailableShows() {
        if (movies.empty()) {
            cout << "No available shows at the moment." << endl;
            return;
        }

        cout << "\nAvailable Movies:\n";
        cout << "---------------------------------------------------------\n";
        cout << "Name          Showtime   Premium Seats   Regular Seats  \n";
        cout << "---------------------------------------------------------\n";

        for (const auto& pair : movies) {
            const Movie& movie = pair.second;
            cout << movie.name << "   | " << movie.showtime << " | "
                 << movie.availablePremiumSeats << "/" << movie.totalPremiumSeats << " | "
                 << movie.availableRegularSeats << "/" << movie.totalRegularSeats << endl;
        }
        cout << "---------------------------------------------------------\n";
    }

    void searchMovie(const string& name) {
        if (movies.find(name) == movies.end()) {
            cout << "Movie not found." << endl;
            return;
        }

        const Movie& movie = movies[name];
        cout << "\nMovie Found: " << movie.name << "\nShowtime: " << movie.showtime
             << "\n💺 Premium Seats Available: " << movie.availablePremiumSeats << "/"
             << movie.totalPremiumSeats
             << "\n💺 Regular Seats Available: " << movie.availableRegularSeats << "/"
             << movie.totalRegularSeats << endl;
    }
};

void displayMenu() {
    cout << "\nMovie Booking System Menu \n";
    cout << "1. Add Movie\n";
    cout << "2. Book Ticket\n";
    cout << "3. Cancel Ticket\n";
    cout << "4. View Available Shows\n";
    cout << "5. Search Movie\n";
    cout << "6. Delete Movie\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    MovieBookingSystem system;
    int choice;
    
    do {
        displayMenu();
        cin >> choice;

        string name, showtime;
        int seats, premiumSeats, regularSeats, numTickets;
        bool isPremium;

        switch (choice) {
            case 1:
                cout << "Enter movie name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter showtime: ";
                getline(cin, showtime);
                cout << "Enter premium seats: ";
                cin >> premiumSeats;
                cout << "Enter regular seats: ";
                cin >> regularSeats;
                system.addMovie(name, showtime, premiumSeats, regularSeats);
                break;

            case 2:
                cout << "Enter movie name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter number of tickets: ";
                cin >> numTickets;
                cout << "Choose seat type (1: Premium, 0: Regular): ";
                cin >> isPremium;
                system.bookTicket(name, numTickets, isPremium);
                break;

            case 3:
                cout << "Enter movie name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter number of tickets to cancel: ";
                cin >> numTickets;
                cout << "Choose seat type (1: Premium, 0: Regular): ";
                cin >> isPremium;
                system.cancelTicket(name, numTickets, isPremium);
                break;

            case 4:
                system.viewAvailableShows();
                break;

            case 5:
                cout << "Enter movie name: ";
                cin >> ws;
                getline(cin, name);
                system.searchMovie(name);
                break;

            case 6:
                cout << "Enter movie name to delete: ";
                cin >> ws;
                getline(cin, name);
                system.deleteMovie(name);
                break;

            case 7:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
