#include <iostream>
#include "Playlist.h"
using namespace std;

Playlist::Playlist(int id, string name): capacity(1), size(0) {
  playlistId = id;
  this->name = name;
  songs = new Song[capacity];
}

Playlist::Playlist(): capacity(0), size(0) {
  playlistId = -1;
  name = "";
  songs = new Song[0];
}

Playlist::~Playlist() {
  delete[] songs;
}

void Playlist::addSong(const Song& song) {
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
}

void Playlist::removeSong(int songId) {
  int removeIndex = -1;
  for(int i = 0; i < size; i++) {
    if(songs[i].getSongId() == songId) {
      removeIndex = i;
      break;
    }
  }
  if(removeIndex != -1) {
    for(int i = removeIndex; i < size - 1; i++) {
      songs[i] = songs[i + 1];
    }
    size--;
  } else {
    cout << "song " << songId << " does not exist" << endl;
  }
}

Playlist::Playlist(const Playlist& orig) {
    capacity = orig.capacity;
    size = orig.size;
    name = orig.name;
    playlistId = orig.playlistId;
    songs = new Song[capacity];
    for(int i = 0; i < size; i++) {
      songs[i] = orig.songs[i];
    }
}

Playlist& Playlist::operator=(const Playlist &other) {
  if(this != &other) {
    delete[] songs;
    capacity = other.capacity;
    size = other.size;
    name = other.name;
    playlistId = other.playlistId;
    songs = new Song[capacity];
    for(int i = 0; i < size; i++) {
      songs[i] = other.songs[i];
    }
  }
  return *this;
}

Song Playlist::getSong(int index) {
  return songs[index];
}

int Playlist::getPlaylistId() const { return playlistId; }
const string& Playlist::getName() const { return name; }
int Playlist::getCapacity() const { return capacity; }
int Playlist::getSize() const { return size; }
void Playlist::setName(string newName) { name = newName; }
void Playlist::setPlaylistId(int newId) { playlistId = newId; }

