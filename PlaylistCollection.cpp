#include <iostream>
#include "PlaylistCollection.h"
using namespace std;

PlaylistCollection::PlaylistCollection() { }

void PlaylistCollection::addSong(int songId, int playlistId, const Song& song) {
  if(song.getSongId() == -1) {
    return;
  }
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) { //finds playlist at playlistid
      for(int j = 0; j < playlists.at(i).getSize(); j++) { //checks each song in playlist at playlistid
	if(playlists.at(i).getSong(j).getSongId() == songId) {
	  cout << "song " << songId << " is already in " << playlistId << endl;
	  return;
	}
      }
      playlists.at(i).addSong(song);
      cout << "song " << songId << " successfully added to playlist " << playlistId << endl;
      return;
    }
  }
  cout << "playlist " << playlistId << " does not exist" << endl;
}

void PlaylistCollection::removeSong(int songId, int playlistId) {
  for(int i = 0; i < playlists.size(); i++) { 
    if(playlists.at(i).getPlaylistId() == playlistId) {
      for(int j = 0; j < playlists.at(i).getSize(); j++) {
	if(playlists.at(i).getSong(j).getSongId() == songId) {
	  playlists.at(i).removeSong(songId);
	  cout << "song " << songId << " successfully dropped from playlist " << playlistId << endl;
	  return;
	}
      }
      cout << "song " << songId << " is not in playlist " << playlistId << endl;
      return;
    }
  }
  cout << "playlist " << playlistId << " does not exist" << endl;
}

bool PlaylistCollection::addPlaylist(const Playlist& playlist) {
  if(playlists.size() == 0) {
    playlists.push_back(playlist);
    return true;
  }
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlist.getPlaylistId()) {
      cout << "playlist id " << playlists.at(i).getPlaylistId() << " already used for " << playlists.at(i).getName() << endl;
      return false;
    }
  }
  int insert = 0;
  while(insert < playlists.size() && playlists.at(insert).getPlaylistId() < playlist.getPlaylistId()) {
    insert++;
  }
  playlists.insert(playlists.begin() + insert, playlist);
  return true;
}

void PlaylistCollection::deletePlaylist(int playlistId) {
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) {
      playlists.erase(playlists.begin() + i);
      cout << "playlist " << playlistId << " successfully deleted" << endl;
      return;
    }
  }
  cout << "playlist " << playlistId << " does not exist" << endl;    
}

void PlaylistCollection::showPlaylist(int playlistId) {
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) {
      cout << playlists.at(i).getName() << endl;
      for(int j = 0; j < playlists.at(i).getSize(); j++) {
      (playlists.at(i)).getSong(j).showSong();
      }
      return;
    }
  }
  cout << "\nplaylist " << playlistId << " does not exist" << endl;
}

void PlaylistCollection::rename(int playlistId, string newName) {
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) {
      (playlists.at(i)).setName(newName);
      cout << "playlist " << playlistId << " name successfully changed to " << newName << endl;
      return;
    }
  }
  cout << "playlist " << playlistId << " does not exist" << endl;
}

void PlaylistCollection::copyPlaylist(int playlistId, int newPlaylistId, string newPlaylistName) {
  bool origExists = false;
  bool newExists = false;
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) {
      origExists = true;
      continue;
    }
    if((playlists.at(i).getPlaylistId() == newPlaylistId)) {
      newExists = true;
    }
  }
   if(!origExists) {
    cout << "original playlist " << playlistId << " does not exist" << endl;
    return;
  }
  if(newExists) {
    cout << "new playlist " << newPlaylistId << " already exists" << endl;
    return;
  }
  Playlist copied;
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) {
      copied = playlists.at(i);
      copied.setPlaylistId(newPlaylistId);
      copied.setName(newPlaylistName);
      break;
    }
  }
  int insert = 0;
  while(insert < playlists.size() && playlists.at(insert).getPlaylistId() < newPlaylistId) {
    insert++;
  }
  playlists.insert(playlists.begin() + insert, copied);
  cout << "playlist " << playlistId << " successfully copied to playlist " << newPlaylistId << " " << newPlaylistName << endl;
}

Playlist PlaylistCollection::getPlaylist(int playlistId) {
  for(int i = 0; i < playlists.size(); i++) {
    if(playlists.at(i).getPlaylistId() == playlistId) {
      return playlists.at(i);
    }
  }
  cout << "playlist " << playlistId << " does not exist" << endl;
  return Playlist();
}

void PlaylistCollection::removeSongs(int songid) {
  for(int i = 0; i < playlists.size(); i++) { //looping through playlist vector to find playlist
    for(int j = 0; j < (playlists.at(i)).getSize(); j++) { //looping through the songs in that playlist
      if((playlists.at(i)).getSong(j).getSongId() == songid) {
	(playlists.at(i)).removeSong(songid);
	break;
      }
    }
  }
}


