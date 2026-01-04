### *Music Playlist Manager*

*Problem Statement:*  
Design a simplified Music Playlist Manager that supports common playlist operations for users. Implement the following features:
- *Add Track*: Add a new track with attributes such as title, artist, album, duration, and optional genre.
- *Remove Track*: Remove a track using its unique identifier (e.g., track ID or title + artist combination).
- *Search Track*: Search tracks by title, artist, or genre (support partial matches).
- *Play Next Track*: Retrieve and play the next track in the playlist queue.
- *Shuffle Playlist*: Randomize the order of the playlist while keeping track of playback history.
- *View Playlist Summary*: Display all tracks with key details and total duration.

*Request for Elaboration:*  
When you work on this problem, document your approach thoroughly. Include detailed explanations of chosen data structures, any helper utilities, and how you handle edge cases (e.g., duplicate tracks, empty playlist). Support your explanation with concrete examples of user interactions and how the system responds.

*Example Workflow:*  
1. Add Track: `"Blinding Lights"`, Artist: `"The Weeknd"`, Duration: `3:20`, Genre: `"Pop"`  
2. Add Track: `"Levitating"`, Artist: `"Dua Lipa"`, Duration: `3:23`, Genre: `"Pop"`  
3. View Playlist Summary → Lists both tracks and reports total duration `6:43`  
4. Shuffle Playlist → Returns randomized order `[ "Levitating", "Blinding Lights" ]`  
5. Play Next Track → `"Levitating"` is played and moved to playback history  
6. Remove Track → Delete `"Blinding Lights"`; summary now shows remaining tracks  
7. Search Track: Query `"Pop"` → Returns all pop tracks currently in the playlist

*Concepts Used:*  
Hash maps or dictionaries (for fast lookups), arrays or lists (for playlist ordering), stacks/queues or deques (for playback history), randomization techniques.

*Boilerplate Code (Python):*
```python
class MusicPlaylistManager:
    def __init__(self):
        self.tracks = {}            # track_id -> track metadata
        self.playlist_order = []    # ordered list of track_ids
        self.play_history = []      # stack of played track_ids

    def add_track(self, track_id, title, artist, album, duration, genre=None):
        """Add a new track to the manager."""
        raise NotImplementedError("Implement add_track logic.")

    def remove_track(self, track_id):
        """Remove an existing track."""
        raise NotImplementedError("Implement remove_track logic.")

    def search_tracks(self, query, field="title"):
        """Return tracks that match the query on the specified field."""
        raise NotImplementedError("Implement search_tracks logic.")

    def play_next(self):
        """Play the next track in the playlist queue."""
        raise NotImplementedError("Implement play_next logic.")

    def shuffle_playlist(self):
        """Shuffle the current playlist order."""
        raise NotImplementedError("Implement shuffle_playlist logic.")

    def get_summary(self):
        """Return a summary of tracks and total duration."""
        raise NotImplementedError("Implement get_summary logic.")


def main():
    manager = MusicPlaylistManager()
    # TODO: Add interactive loop or tests demonstrating the features.


if __name__ == "__main__":
    main()
```