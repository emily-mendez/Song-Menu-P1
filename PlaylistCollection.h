#ifndef PLAYLISTCOLLECTION_H
#define PLAYLISTCOLLECTION_H

#include <iostream>
#include <vector>
#include "Playlist.h"
#include "Song.h"
#include "SongCollection.h"
using namespace std;

class PlaylistCollection {
 public:
  PlaylistCollection();
  void addSong(int songId, int playlistId, const Song& song);
  void removeSong(int songId, int playlistId);
  void removeSongs(int songid);
  bool addPlaylist(const Playlist& playlist);
  void deletePlaylist(int playlistId);
  void showPlaylist(int playlistId);
  void rename(int playlistId, string newName);
  void copyPlaylist(int playlistId, int newPlaylistId, string newPlaylistName);
  Playlist getPlaylist(int playlistId);
 private:
  vector<Playlist> playlists;
};

#endif
  
  
