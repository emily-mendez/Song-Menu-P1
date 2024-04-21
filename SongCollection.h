#ifndef SONGCOLLECTION_H
#define SONGCOLLECTION_H

#include <iostream>
#include "Song.h"
using namespace std;

class SongCollection {
 public:
  SongCollection();
  ~SongCollection();
  SongCollection(const SongCollection &other);
  SongCollection& operator=(const SongCollection &other);
  bool addSong(const Song& song);
  Song getSong(int songId) const;
  void removeSong(int songId);
  void showSong(int songId);

 private:
  Song* songs;
  int capacity;
  int size;
};

#endif
