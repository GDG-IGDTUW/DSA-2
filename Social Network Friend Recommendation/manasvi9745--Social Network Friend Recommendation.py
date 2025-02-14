from collections import defaultdict  
from collections import deque

class SocialNetwork:
    def __init__(self):
        self.network = defaultdict(set)
    
    def addUser(self, user_id):
        if user_id not in self.network:
            self.network[user_id] = set()
            print(f"User {user_id} added.")
        else:
            print(f"User {user_id} already exists.")
    
    def addFriendship(self, user_id1, user_id2):
        if user_id1 in self.network and user_id2 in self.network:
            self.network[user_id1].add(user_id2)
            self.network[user_id2].add(user_id1)
            print(f"Friendship established between {user_id1} and {user_id2}.")
        else:
            print("One or both users do not exist.")
    
    def getFriendRecommendations(self, user_id):
        if user_id not in self.network:
            print("User does not exist.")
            return
        
        direct_friends = self.network[user_id]
        recommendations = defaultdict(int)
        
        for friend in direct_friends:
            for friend_of_friend in self.network[friend]:
                if friend_of_friend != user_id and friend_of_friend not in direct_friends:
                    recommendations[friend_of_friend] += 1
        
        sorted_recommendations = sorted(recommendations.keys(), key=lambda x: -recommendations[x])
        print(f"Friend Recommendations for {user_id}: {sorted_recommendations}")
    
    def viewFriends(self, user_id):
        if user_id not in self.network:
            print("User does not exist.")
            return
        print(f"Friends of {user_id}: {list(self.network[user_id])}")

# Example execution
if __name__ == "__main__":
    sn = SocialNetwork()
    sn.addUser(1)
    sn.addUser(2)
    sn.addUser(3)
    sn.addFriendship(1, 2)
    sn.addFriendship(2, 3)
    sn.getFriendRecommendations(1)
    sn.viewFriends(1)
