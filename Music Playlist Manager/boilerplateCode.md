
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
        tracks[trackId] = {
            title, artist, album, to_string(duration), genre
        };
        if (find(playlistOrder.begin(), playlistOrder.end(), trackId) == playlistOrder.end())
            playlistOrder.push_back(trackId);
    }

    void removeTrack(int trackId) {
        tracks.erase(trackId);
        playlistOrder.erase(
            remove(playlistOrder.begin(), playlistOrder.end(), trackId),
            playlistOrder.end()
        );
    }

    vector<vector<string>> searchTrack(string query, string field) {
        vector<vector<string>> res;
        int idx = (field == "title") ? 0 : (field == "artist") ? 1 : 4;
        for (auto &it : tracks) {
            if (it.second[idx].find(query) != string::npos) {
                res.push_back({
                    to_string(it.first),
                    it.second[0], it.second[1],
                    it.second[2], it.second[3], it.second[4]
                });
            }
        }
        return res;
    }

    vector<string> playNext() {
        if (playlistOrder.empty()) return {};
        int id = playlistOrder.front();
        playlistOrder.erase(playlistOrder.begin());
        auto &t = tracks[id];
        return {to_string(id), t[0], t[1], t[2], t[3], t[4]};
    }

    void shufflePlaylist() {
        random_shuffle(playlistOrder.begin(), playlistOrder.end());
    }

    vector<vector<string>> getPlaylistSummary() {
        vector<vector<string>> res;
        for (int id : playlistOrder) {
            auto &t = tracks[id];
            res.push_back({
                to_string(id), t[0], t[1], t[2], t[3], t[4]
            });
        }
        return res;
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
        tracks.put(trackId, Arrays.asList(title, artist, album,
                String.valueOf(duration), genre));
        if (!playlistOrder.contains(trackId))
            playlistOrder.add(trackId);
    }

    public void removeTrack(int trackId) {
        tracks.remove(trackId);
        playlistOrder.remove(Integer.valueOf(trackId));
    }

    public List<List<String>> searchTrack(String query, String field) {
        List<List<String>> res = new ArrayList<>();
        int idx = field.equals("title") ? 0 : field.equals("artist") ? 1 : 4;
        for (Map.Entry<Integer, List<String>> e : tracks.entrySet()) {
            if (e.getValue().get(idx).contains(query)) {
                List<String> t = e.getValue();
                res.add(Arrays.asList(
                    String.valueOf(e.getKey()),
                    t.get(0), t.get(1), t.get(2), t.get(3), t.get(4)
                ));
            }
        }
        return res;
    }

    public List<String> playNext() {
        if (playlistOrder.isEmpty()) return new ArrayList<>();
        int id = playlistOrder.remove(0);
        List<String> t = tracks.get(id);
        return Arrays.asList(
            String.valueOf(id),
            t.get(0), t.get(1), t.get(2), t.get(3), t.get(4)
        );
    }

    public void shufflePlaylist() {
        Collections.shuffle(playlistOrder);
    }

    public List<List<String>> getPlaylistSummary() {
        List<List<String>> res = new ArrayList<>();
        for (int id : playlistOrder) {
            List<String> t = tracks.get(id);
            res.add(Arrays.asList(
                String.valueOf(id),
                t.get(0), t.get(1), t.get(2), t.get(3), t.get(4)
            ));
        }
        return res;
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
        self.tracks[trackId] = [title, artist, album, duration, genre]
        if trackId not in self.playlist_order:
            self.playlist_order.append(trackId)

    def removeTrack(self, trackId):
        self.tracks.pop(trackId, None)
        if trackId in self.playlist_order:
            self.playlist_order.remove(trackId)

    def searchTrack(self, query, field):
        idx = {"title":0, "artist":1, "genre":4}[field]
        res = []
        for k, v in self.tracks.items():
            if query in v[idx]:
                res.append([k] + v)
        return res

    def playNext(self):
        if not self.playlist_order:
            return []
        trackId = self.playlist_order.pop(0)
        return [trackId] + self.tracks[trackId]

    def shufflePlaylist(self):
        random.shuffle(self.playlist_order)

    def getPlaylistSummary(self):
        return [[k] + self.tracks[k] for k in self.playlist_order]
```
