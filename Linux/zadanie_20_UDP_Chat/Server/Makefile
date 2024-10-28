# make -f Makefile1
# make clean
 #all:
	#g++ main.cpp user.h user.cpp message.h message.cpp sha1.h sha1.cpp chat.h chat.cpp TrieNode.h TrieNode.cpp -o main
#$@ — имя .o-файла
#$< — имя .cpp-файла



CC=g++
CFLAGS=-c -Wall# -g2
LDFLAGS=
SOURCES= main.cpp chat.cpp ServerManager.cpp sha1.cpp message.cpp#user.cpp message.cpp sha1.cpp chat.cpp TrieNode.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Server

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

cleanexe:
	rm $(EXECUTABLE)

kill:
	killall -9 ./Server
