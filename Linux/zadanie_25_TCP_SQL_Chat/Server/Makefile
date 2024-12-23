# make -f Makefile1
# make clean
 #all:
	#g++ main.cpp user.h user.cpp message.h message.cpp sha1.h sha1.cpp chat.h chat.cpp TrieNode.h TrieNode.cpp -o main
#$@ — имя .o-файла
#$< — имя .cpp-файла
#*******************************************************************
#g++ -c -Wall -g2 main.cpp -o main.o
#g++ -c -Wall -g2 chat.cpp -o chat.o
#g++ -c -Wall -g2 TCP.cpp -o TCP.o
#g++ -c -Wall -g2 sha1.cpp -o sha1.o
#g++ -c -Wall -g2 message.cpp -o message.o
#g++ -c -Wall -g2 db.cpp -o db.o
#g++  main.o chat.o TCP.o sha1.o message.o db.o -lmysqlclient -o Server
#rm -rf *.o
#*******************************************************************


CC=g++
CFLAGS=-c -Wall -g2 -O0 -std=c++17 #-g2 -O0 - флаги для gdb
LDFLAGS=
SOURCES= main.cpp chat.cpp TCP.cpp sha1.cpp message.cpp db.cpp config.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Server
MYSQL = -lmysqlclient

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(MYSQL) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

cleanexe:
	rm $(EXECUTABLE)

kill:
	killall -9 ./Server

gdb:
	gdb --silent -tui ./Server

