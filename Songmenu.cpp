#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "SongCollection.h"
#include "Playlist.h"
#include "PlaylistCollection.h"
#include "Song.h"
#include <regex>
using namespace std;

string durationFormat(int durationSecs) {
    int minutes = durationSecs / 60;
    int seconds = durationSecs % 60;
    if(seconds < 10) {
      return to_string(minutes) + ":0" + to_string(seconds);
    }
    return to_string(minutes) + ":" + to_string(seconds);
}

void printError() {
  cout << "Incorrect number of arguments" << endl;
}

bool isNumber(string& str)
{
  regex re("^[0-9]*$");
  return regex_match(str, re);
}



int main(int argc, char *argv[]) {
  string input, artist, title, name;
  int songid, playlistid, duration;
  string newPlaylistName;
  int newPlaylistId;
  string dummy;
  string rest;
  string songidstr, playlistidstr, durationstr;
  SongCollection* SC = new SongCollection();
  PlaylistCollection* PC = new PlaylistCollection();
  while(true) {
    cout << "Enter [\"song <songid> <artist> <duration> <title>\"" << endl;
    cout << "       \"remove <songid>\"" << endl;
    cout << "       \"playlist <playlistid> <playlistname>\"" << endl;
    cout << "       \"add <songid> <playlistid>\"" << endl;
    cout << "       \"drop <songid> <playlistid>\"" << endl;
    cout << "       \"seesong <songid>\"" << endl;
    cout << "       \"seeplaylist <playlistid>\"" << endl;
    cout << "       \"deleteplaylist <playlistid>\"" << endl;
    cout << "       \"copyplaylist <playlistid> <new playlistid> <new playlistname>\"" << endl;
    cout << "       \"renameplaylist <playlistid> <new playlistname>\"" << endl;
    cout << "       \"quit\"]" << endl;
    cout << ": ";
    getline(cin, input);
    istringstream iss(input);
    string command;
    iss >> command;

    if(command == "quit") { return 0; }

    if(command == "song") { //CREATING SONG
      iss >> songidstr >> ws;
      if(!(iss.rdbuf()->in_avail())) {
	  printError();
	  continue;
	}
      string newstr;
      getline(iss, newstr);
      if(newstr[0] == '"') {
	  stringstream newss(newstr.substr(1));
	  getline(newss, artist, '"');
	  string nextone = newss.str();
	  if(!(newss.rdbuf()->in_avail())) {
	      printError();
	      continue;
	    }
	   newss >> durationstr >> ws;
	   if(!(newss.rdbuf()->in_avail())) {
	      printError();
	      continue;
	    }
	  string nextobj;
	  getline(newss, nextobj);
	  if(nextobj[0] == '"') {
	      stringstream nextss(nextobj.substr(1));
	      getline(nextss, title, '"');
	      string nextstring = nextss.str();
	    }
	}
      if(!(isNumber(songidstr))) {
	  cout << "song id " << songidstr << " is not an integer" << endl;
	  continue;
	}
      songid = stoi(songidstr);
      if(!(isNumber(durationstr))) {
	  cout << "duration " << durationstr << " is not an integer" << endl;
	  continue;
	}
      duration = stoi(durationstr);
      if(SC->addSong(Song(songid, artist, duration, title))) {
      cout << "new song " << songid << " " << title << " by " << artist << " " << durationFormat(duration) << endl;
       }
    } else if(command == "remove") { //REMOVING SONG
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> songid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "song id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      cout << "removing song " << songid << endl;
      PC->removeSongs(songid);
      SC->removeSong(songid);
    } else if(command == "playlist") { //CREATING PLAYLIST
      iss >> playlistidstr >> ws;
      if(!(iss.rdbuf()->in_avail())) {
	printError();
	continue;
      }
      string newstr;
      getline(iss, newstr);
      if(newstr[0] == '"') {
	stringstream newss(newstr.substr(1));
	getline(newss, name, '"');
	string nextStr = newss.str();
      }
      if(!isNumber(playlistidstr)) {
	cout << "playlist id " << playlistidstr << " is not an integer" << endl;
	continue;
      }
      playlistid = stoi(playlistidstr);
      if(PC->addPlaylist(Playlist(playlistid, name))) {
	  cout <<  "new playlist " << playlistid << " called " << name << endl;
      } 
    } else if(command == "add") { //ADD SONG TO PLAYLIST
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> songid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "song id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> playlistid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "playlist id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      cout << "add song " << songid << " to playlist " << playlistid << endl;
      PC->addSong(songid, playlistid, SC->getSong(songid));
    } else if(command == "drop") { //REMOVE SONG FROM PLAYLIST
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> songid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "song id " << songid << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> playlistid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "playlistid " << playlistid << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      cout << "remove song " << songid << " from playlist " << playlistid << endl;
      if((SC->getSong(songid)).getSongId() == -1) continue;
      PC->removeSong(songid, playlistid);
    } else if(command == "seesong") { //SHOW SONG
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> songid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "song id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      SC->showSong(songid);
    } else if(command == "seeplaylist") { //SHOW PLAYLIST
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> playlistid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "playlist id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
        printError();
	continue;
      }
      cout << "Songs in playlist " << playlistid << " ";
      PC->showPlaylist(playlistid);
    } else if(command == "deleteplaylist") { //DELETE PLAYLIST
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> playlistid)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "playlist id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
	printError();
	continue;
      }
      PC->deletePlaylist(playlistid);
    } else if(command == "renameplaylist") { //RENAME PLAYLIST
      iss >> playlistidstr >> ws;
      if(!(iss.rdbuf()->in_avail())) {
	printError();
	continue;
      }
      string newstr;
      getline(iss, newstr);
      if(newstr[0] == '"') {
	stringstream newss(newstr.substr(1));
	getline(newss, newPlaylistName, '"');
	string nextStr = newss.str();
      }
      if(!isNumber(playlistidstr)) {
	cout << "playlist id " << playlistidstr << " is not an integer" << endl;
	continue;
      }
      playlistid = stoi(playlistidstr);
      PC->rename(playlistid, newPlaylistName);
    } else if(command == "copyplaylist") { //COPY PLAYLIST
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> playlistid >> ws)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "playlist id " << playlistid << " is not an integer" << endl;
	  continue;
	}
      } else {
	printError();
	continue;
      }
      if(iss.rdbuf()->in_avail() != 0) {
	if(!(iss >> newPlaylistId >> ws)) {
	  iss.clear();
	  iss >> dummy;
	  cout << "playlist id " << dummy << " is not an integer" << endl;
	  continue;
	}
      } else {
	printError();
	continue;
      }
      if(!(iss.rdbuf()->in_avail())) {
	printError();
	continue;
      }
      string newstr;
      getline(iss, newstr);
      if(newstr[0] == '"') {
	stringstream newss(newstr.substr(1));
	getline(newss, newPlaylistName, '"');
	string nextStr = newss.str();
      }
      PC->copyPlaylist(playlistid, newPlaylistId, newPlaylistName);
    } else {
      cout << "Command not recognized, please try again." << endl;
    }
  }
}
