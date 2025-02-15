class SocialNetwork:
    def __init__(self):
        # Dictionary to store user ID as key and a set of friends as value
        self.network = {}

    def add_user(self, user_id, name):
        # Adds a new user to the social network
        if user_id in self.network:
            print("User ID already exists.")
            return
        self.network[user_id] = {"name": name, "friends": set()}
        print(f"User '{name}' added successfully.")

    def add_friendship(self, user1, user2):
        # Establishes a friendship between two users
        if user1 not in self.network or user2 not in self.network:
            print("-1")  # One or both users not found
            return
        self.network[user1]["friends"].add(user2)
        self.network[user2]["friends"].add(user1)
        print(f"Friendship established between '{self.network[user1]['name']}' and '{self.network[user2]['name']}'.")

    def recommend_friends(self, user_id):
        # Suggests friend recommendations based on mutual friends
        if user_id not in self.network:
            print("-1")  # User not found
            return
        
        friends = self.network[user_id]["friends"]
        recommendations = set()
        
        for friend in friends:
            for friend_of_friend in self.network[friend]["friends"]:
                if friend_of_friend != user_id and friend_of_friend not in friends:
                    recommendations.add(friend_of_friend)
        
        if not recommendations:
            print("No friend recommendations available.")
        else:
            print(f"Friend recommendations for '{self.network[user_id]['name']}':", recommendations)

    def display_network(self):
        # Displays the entire social network
        if not self.network:
            print("No users available.")
            return
        for user_id, data in self.network.items():
            print(f"ID: {user_id}, Name: {data['name']}, Friends: {list(data['friends'])}")

    def remove_user(self, user_id):
        # Removes a user from the social network
        if user_id not in self.network:
            print("-1")  # User not found
            return
        
        # Remove user from their friends' lists
        for friend in self.network[user_id]["friends"]:
            self.network[friend]["friends"].discard(user_id)
        
        name = self.network[user_id]["name"]
        del self.network[user_id]
        print(f"User '{name}' removed successfully.")


def main():
    # Main function to interact with the social network
    social_network = SocialNetwork()
    
    while True:
        # Display menu options
        print("\n1. Add User\n2. Add Friendship\n3. Recommend Friends\n4. Display Network\n5. Remove User\n6. Exit")
        choice = input("Enter choice: ")
        
        if choice == "6":
            break  # Exit the program
        
        if choice == "1":
            # Adding a new user
            user_id = input("Enter user ID: ")
            name = input("Enter user name: ")
            social_network.add_user(user_id, name)
        
        elif choice == "2":
            # Establishing a friendship
            user1 = input("Enter first user ID: ")
            user2 = input("Enter second user ID: ")
            social_network.add_friendship(user1, user2)
        
        elif choice == "3":
            # Recommending friends
            user_id = input("Enter user ID: ")
            social_network.recommend_friends(user_id)
        
        elif choice == "4":
            # Display all users and their friends
            social_network.display_network()
        
        elif choice == "5":
            # Removing a user
            user_id = input("Enter user ID: ")
            social_network.remove_user(user_id)
        
        else:
            print("Invalid choice.")

if __name__ == "__main__":
    main()
