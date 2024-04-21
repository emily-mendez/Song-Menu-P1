#include <iostream>
#include "SongCollection.h"
using namespace std;

SongCollection::SongCollection(): songs(nullptr), capacity(1), size(0) {
  songs = new Song[capacity];
}

SongCollection::~SongCollection() {
  delete[] songs;
}

SongCollection::SongCollection(const SongCollection &origSongs) {
  capacity = origSongs.capacity;
  size = origSongs.size;
  songs = new Song[capacity];
  for(int i = 0; i < size; i++) {
    songs[i] = origSongs.songs[i];
  }
}

SongCollection& SongCollection::operator=(const SongCollection& other) {
  if(this != &other) {
    delete[] songs;
    capacity = other.capacity;
    size = other.size;
    songs = new Song[capacity];
    for(int i = 0; i < size; i++) {
      songs[i] = other.songs[i];
    }
  }
  return *this;
}
    

bool SongCollection::addSong(const Song& song) {
  for(int i = 0; i < size; i++) {
    if(songs[i].getSongId() == song.getSongId()) {
      cout << "song id " << song.getSongId() << " already used for " << songs[i].getTitle() << " by " << songs[i].getArtist() << endl;
      return false;
    }
  }
  if(size >= capacity) {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    Song* updatedSongs = new Song[capacity];
    for(int i = 0; i < size; i++) {
      updatedSongs[i] = songs[i];
    }
    delete[] songs;
    songs = updatedSongs;
  }
  int insert = 0; //index of song to be inserted into array
  while(insert < size && songs[insert].getSongId() < song.getSongId()) {
    insert++;
  }
  for(int i = size; i > insert; i--) {
    songs[i] = songs[i - 1];
  }
  songs[insert] = song;
  size++;
  return true;
}

void SongCollection::removeSong(int songId) {
  int removeIndex = -1;
  for(int i = 0; i < size; i++) {
    if(songs[i].getSongId() == songId) {
      removeIndex = i;
      break;
    }
  }
  if(removeIndex != -1) {
    cout << "song " << songId << ", " << songs[removeIndex].getTitle() << " by " << songs[removeIndex].getArtist() << ", removed" << endl;
    for(int i = removeIndex; i < size - 1; i++) {
      songs[i] = songs[i + 1];
    }
    size--;
  } else {
    cout << "song " << songId << " not found" << endl;
  }
}

void SongCollection::showSong(int songId) {
  int index = -1;
  for(int i = 0; i < size; i++) {
    if(songs[i].getSongId() == songId) {
      index = i;
      break;
    }
  }
  if(index != -1) {
    cout << "song " << songId << " " << songs[index].getTitle() << " by " << songs[index].getArtist() << endl;
  } else {
    cout << "song " << songId << " does not exist" << endl;
  }
}
  
Song SongCollection::getSong(int songId) const {
  for(int i = 0; i < size; i++) {
    if(songs[i].getSongId() == songId) {
      return songs[i];
    }
  }
  cout << "song " << songId << " does not exist" << endl;
  return Song();
}
  
