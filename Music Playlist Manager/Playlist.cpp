#include <bits/stdc++.h>
using namespace std;

class MusicPlaylistManager {
private:
    unordered_map<int, vector<string>> tracks;
    vector<int> playlistOrder;

public:
    void addTrack(int trackId, string title, string artist,
                  string album, int duration, string genre) {

        if (tracks.count(trackId)) {
            cout << "Track already exists.\n";
            return;
        }

        tracks[trackId] = {title, artist, album, to_string(duration), genre};
        playlistOrder.push_back(trackId);

        cout << "Track added successfully.\n";
    }

    void removeTrack(int trackId) {

        if (!tracks.count(trackId)) {
            cout << "Track not found.\n";
            return;
        }

        tracks.erase(trackId);

        playlistOrder.erase(
            remove(playlistOrder.begin(), playlistOrder.end(), trackId),
            playlistOrder.end()
        );

        cout << "Track removed successfully.\n";
    }

    void playNext() {

        if (playlistOrder.empty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        int trackId = playlistOrder.front();
        playlistOrder.erase(playlistOrder.begin());

        vector<string> track = tracks[trackId];

        cout << "Now Playing:\n";
        cout << "Title: " << track[0] << "\n";
        cout << "Artist: " << track[1] << "\n";
        cout << "Album: " << track[2] << "\n";
        cout << "Duration: " << track[3] << "\n";
        cout << "Genre: " << track[4] << "\n\n";
    }

    void shufflePlaylist() {
        random_shuffle(playlistOrder.begin(), playlistOrder.end());
        cout << "Playlist shuffled.\n";
    }

    void showPlaylist() {

        if (playlistOrder.empty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\n--- Playlist ---\n";
        for (int id : playlistOrder) {
            cout << tracks[id][0] << " by " << tracks[id][1] << "\n";
        }
        cout << "----------------\n";
    }
};

int main() {

    MusicPlaylistManager manager;

    manager.addTrack(1, "SongA", "Artist1", "AlbumX", 200, "Pop");
    manager.addTrack(2, "SongB", "Artist2", "AlbumY", 180, "Rock");
    manager.addTrack(3, "SongC", "Artist1", "AlbumZ", 210, "Jazz");

    manager.showPlaylist();

    manager.playNext();

    manager.shufflePlaylist();

    manager.showPlaylist();

    manager.removeTrack(2);

    manager.showPlaylist();

    return 0;
}
