#include <iostream>
#include <stdlib.h>
#include "Song.h"
using namespace std;

Song::Song(int songid, string artist, int duration, string title): songid(songid), artist(artist), duration(duration), title(title) { }

Song::Song() {
  songid = -1;
  artist = "";
  duration = 0;
  title = "";
}

void Song::showSong() {
  cout << "song " << songid << " " << title << " by " << artist << endl;
}

int Song::getSongId() const { return songid; }
const string& Song::getArtist() const { return artist; }
int Song::getDuration() const { return duration; }
const string& Song::getTitle() const { return title; }
