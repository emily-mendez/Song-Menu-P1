#ifndef SONG_H
#define SONG_H

#include <iostream>
using namespace std;

class Song {
 public:
  Song(int songid, string artist, int duration, string title);
  Song();
  void showSong();
  int getSongId() const;
  const string& getArtist() const;
  int getDuration() const;
  const string& getTitle() const;

 private:
  int songid;
  string artist;
  int duration;
  string title;
};

#endif
