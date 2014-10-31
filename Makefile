CC=g++
CFLAGS=-c -Wall -std=c++11 -g
LDFLAGS=-lcgicc -lhamsterdb -Wl,-rpath -Wl,/usr/local/lib -lfcgi -lfcgi++
SOURCES=main.cpp template.cpp urlhandlerstartpage.cpp urlhandlercontact.cpp datamanager.cpp urlhandlerhighscore.cpp urlhandleradd.cpp urlhandlervote.cpp FCgiIO.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=index.bla
DEPLOY_PATH=/var/www/

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ${OBJECTS}
	rm ${EXECUTABLE}

deploy: $(EXECUTABLE)
	su -c "killall -9 $(EXECUTABLE)"
	cp index.bla $(DEPLOY_PATH)index.bla
	strip $(DEPLOY_PATH)index.bla
