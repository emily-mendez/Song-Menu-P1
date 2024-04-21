#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include "Song.h"
using namespace std;

class Playlist {
 public:
  Playlist(int playlistId, string playlistName);
  Playlist();
  ~Playlist();
  Playlist(const Playlist& orig);
  Playlist& operator=(const Playlist &other);
  void addSong(const Song& song);
  void removeSong(int songId);
  int getPlaylistId() const;
  const string& getName() const;
  int getCapacity() const;
  int getSize() const;
  Song getSong(int index);
  void setPlaylistId(int newId);
  void setName(string newName);
  
 private:
  int playlistId;
  string name;
  Song* songs;
  int capacity;
  int size;
};

#endif
