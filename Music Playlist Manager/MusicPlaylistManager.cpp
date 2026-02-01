#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

//  Track Structure 
struct Track {
    int trackId;
    string title;
    string artist;
    string album;
    int duration;
    string genre;
};

// Utility
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

//  Music Playlist Manager
class MusicPlaylistManager {
private:
    unordered_map<int, Track> tracks;   // trackId -> Track
    deque<int> playlist;                // maintains order

public:
    //  1. Add / Update Track
    void addTrack(int trackId, string title, string artist,
                  string album, int duration, string genre) {

        bool exists = tracks.count(trackId);

        tracks[trackId] = {trackId, title, artist, album, duration, genre};

        if (!exists) {
            playlist.push_back(trackId);
        }
    }

    //  2. Remove Track
    void removeTrack(int trackId) {
        if (!tracks.count(trackId)) return;

        tracks.erase(trackId);

        playlist.erase(
            remove(playlist.begin(), playlist.end(), trackId),
            playlist.end()
        );
    }

    //  3. Search Track
    vector<vector<string>> searchTrack(string query, string field) {
        vector<vector<string>> result;
        query = toLower(query);

        for (auto &p : tracks) {
            Track &t = p.second;
            string value;

            if (field == "title") value = t.title;
            else if (field == "artist") value = t.artist;
            else if (field == "genre") value = t.genre;
            else continue;

            if (toLower(value).find(query) != string::npos) {
                result.push_back({
                    to_string(t.trackId),
                    t.title,
                    t.artist,
                    t.album,
                    to_string(t.duration),
                    t.genre
                });
            }
        }
        return result;
    }

    //  4. Play Next
    vector<string> playNext() {
        if (playlist.empty()) return {};

        int id = playlist.front();
        playlist.pop_front();

        Track &t = tracks[id];
        return {
            to_string(t.trackId),
            t.title,
            t.artist,
            t.album,
            to_string(t.duration),
            t.genre
        };
    }

    //  5. Shuffle Playlist
    void shufflePlaylist() {
        vector<int> temp(playlist.begin(), playlist.end());
        shuffle(temp.begin(), temp.end(), default_random_engine(time(0)));
        playlist = deque<int>(temp.begin(), temp.end());
        cout << "Playlist Shuffled\n";
    }

    //  6. Playlist Summary
    void getPlaylistSummary() {
        int totalDuration = 0;

        cout << "[";
        for (int i = 0; i < playlist.size(); i++) {
            Track &t = tracks[playlist[i]];
            totalDuration += t.duration;

            cout << "[" << t.trackId << ", "
                 << t.title << ", "
                 << t.artist << ", "
                 << t.album << ", "
                 << t.duration << ", "
                 << t.genre << "]";

            if (i != playlist.size() - 1) cout << ",\n ";
        }
        cout << "]\n";
        cout << "Total Duration: " << totalDuration << "\n";
    }
};

//  Main Driver
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MusicPlaylistManager manager;

    int Q;
    cin >> Q;

    while (Q--) {
        string cmd;
        cin >> cmd;

        if (cmd == "addTrack") {
            int id, duration;
            string title, artist, album, genre;
            cin >> id >> title >> artist >> album >> duration >> genre;
            manager.addTrack(id, title, artist, album, duration, genre);
        }
        else if (cmd == "removeTrack") {
            int id;
            cin >> id;
            manager.removeTrack(id);
        }
        else if (cmd == "searchTrack") {
            string query, field;
            cin >> query >> field;
            auto res = manager.searchTrack(query, field);

            cout << "[";
            for (int i = 0; i < res.size(); i++) {
                cout << "[" << res[i][0] << ", "
                     << res[i][1] << ", "
                     << res[i][2] << ", "
                     << res[i][3] << ", "
                     << res[i][4] << ", "
                     << res[i][5] << "]";
                if (i != res.size() - 1) cout << ",\n ";
            }
            cout << "]\n";
        }
        else if (cmd == "playNext") {
            auto t = manager.playNext();
            if (t.empty()) {
                cout << "[]\n";
            } else {
                cout << "[" << t[0] << ", " << t[1] << ", " << t[2]
                     << ", " << t[3] << ", " << t[4] << ", " << t[5] << "]\n";
            }
        }
        else if (cmd == "shufflePlaylist") {
            manager.shufflePlaylist();
        }
        else if (cmd == "getPlaylistSummary") {
            manager.getPlaylistSummary();
        }
    }

    return 0;
}
