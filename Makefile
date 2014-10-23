CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lcgicc -lhamsterdb -Wl,-rpath -Wl,/usr/local/lib
SOURCES=main.cpp template.cpp urlhandlerstartpage.cpp urlhandlercontact.cpp datamanager.cpp urlhandlerhighscore.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=index.bla

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ${OBJECTS}
	rm ${EXECUTABLE}

deploy: $(EXECUTABLE)
	cp index.bla ../www/index.bla
