
## C++
```cpp
#include <bits/stdc++.h>
using namespace std;

class MusicPlaylistManager {
private:
    // trackId -> [title, artist, album, duration, genre]
    unordered_map<int, vector<string>> tracks;
    vector<int> playlistOrder;

public:
    MusicPlaylistManager() {}

    void addTrack(int trackId, string title, string artist,
                  string album, int duration, string genre) {

    }

    void removeTrack(int trackId) {
        
    }

    vector<vector<string>> searchTrack(string query, string field) {
        
    }

    vector<string> playNext() {
        
    }

    void shufflePlaylist() {

    }

    vector<vector<string>> getPlaylistSummary() {
        
    }
};

int main() {
    MusicPlaylistManager m;
    return 0;
}
```

## Java
```java
import java.util.*;

class MusicPlaylistManager {

    // trackId -> [title, artist, album, duration, genre]
    private Map<Integer, List<String>> tracks = new HashMap<>();
    private List<Integer> playlistOrder = new ArrayList<>();

    public void addTrack(int trackId, String title, String artist,
                         String album, int duration, String genre) {
        
    }

    public void removeTrack(int trackId) {
        
    }

    public List<List<String>> searchTrack(String query, String field) {

    }

    public List<String> playNext() {
        
    }

    public void shufflePlaylist() {
       
    }

    public List<List<String>> getPlaylistSummary() {
        
    }
}
```

## Python
```py
import random

class MusicPlaylistManager:
    def __init__(self):
        # trackId -> [title, artist, album, duration, genre]
        self.tracks = {}
        self.playlist_order = []

    def addTrack(self, trackId, title, artist, album, duration, genre):
        

    def removeTrack(self, trackId):
        

    def searchTrack(self, query, field):
        

    def playNext(self):
        

    def shufflePlaylist(self):
        

    def getPlaylistSummary(self):
        
```
