# 🎵 Music Playlist Manager

## Problem Statement

Design and implement a data structure for a **Music Playlist Manager** that supports adding tracks, removing tracks, searching tracks, playing music sequentially, shuffling the playlist, and viewing playlist details efficiently.

Each track has:
- a unique `trackId`
- `title`
- `artist`
- `album`
- `duration` (in seconds)
- `genre`

The system should manage playlist order correctly and handle all operations efficiently.

---

## Operations

Implement the following functions:

### 1. `addTrack(trackId, title, artist, album, duration, genre)`
- Adds a new track to the playlist.
- If the track already exists, update its details.

### 2. `removeTrack(trackId)`
- Removes the track completely from the playlist.
- If the track does not exist, do nothing.

### 3. `searchTrack(query, field)`
- Searches tracks by `title`, `artist`, or `genre`.
- Supports partial and case-insensitive matches.
- Returns a list of matching tracks in the format:
  [trackId, title, artist, album, duration, genre]

### 4. `playNext()`
- Plays the next track from the playlist queue.
- Removes the track from the front of the playlist.
- If the playlist is empty, return:
  []

### 5. `shufflePlaylist()`
- Randomizes the order of tracks in the playlist.
- Track metadata remains unchanged.

### 6. `getPlaylistSummary()`
- Returns all tracks in current playlist order.
- Also returns total playlist duration.

---

## Input Format

- The first line contains an integer `Q`, the number of operations.
- The next `Q` lines contain one of the following commands:

addTrack trackId title artist album duration genre  
removeTrack trackId  
searchTrack query field  
playNext  
shufflePlaylist  
getPlaylistSummary  

---

## Output Format

- For `searchTrack`, output a list of matching tracks.
- For `playNext`, output the played track or `[]`.
- For `getPlaylistSummary`, output all tracks and total duration.

---

## Examples

### Example 1

#### INPUT
10  
addTrack 1 BlindingLights TheWeeknd AfterHours 200 Pop  
addTrack 2 Levitating DuaLipa FutureNostalgia 203 Pop  
addTrack 3 Believer ImagineDragons Evolve 204 Rock  
searchTrack Pop genre  
playNext  
shufflePlaylist  
removeTrack 1  
getPlaylistSummary  

#### OUTPUT
[[1, BlindingLights, TheWeeknd, AfterHours, 200, Pop],  
 [2, Levitating, DuaLipa, FutureNostalgia, 203, Pop]]

[1, BlindingLights, TheWeeknd, AfterHours, 200, Pop]

Playlist Shuffled

[[2, Levitating, DuaLipa, FutureNostalgia, 203, Pop],  
 [3, Believer, ImagineDragons, Evolve, 204, Rock]]  
Total Duration: 407

---

## Constraints

- `1 ≤ Q ≤ 10^5`
- `1 ≤ trackId ≤ 10^9`
- `1 ≤ duration ≤ 10^5`
- All string fields are valid non-empty strings
- All operations should be handled efficiently

---

## Key Takeaways

- Tests understanding of **arrays, hash maps, and queues**
- Emphasizes **state management**
- Models a **real-world playlist system**
- Suitable for **coding interviews and DSA practice**
