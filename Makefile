all: songmenu

songmenu: Songmenu.o SongCollection.o Song.o Playlist.o PlaylistCollection.o
	g++ Songmenu.o Song.o SongCollection.o Playlist.o PlaylistCollection.o -o songmenu

Songmenu.o: Songmenu.cpp Song.h Playlist.h PlaylistCollection.h SongCollection.h
	g++ -c Songmenu.cpp

Song.o: Song.cpp Song.h
	g++ -c Song.cpp

SongCollection.o: SongCollection.cpp SongCollection.h
	g++ -c SongCollection.cpp

Playlist.o: Playlist.cpp Playlist.h
	g++ -c Playlist.cpp

PlaylistCollection.o: PlaylistCollection.cpp PlaylistCollection.h
	g++ -c PlaylistCollection.cpp

clean:
	rm -f *.o songmenu
