CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lcgicc 
SOURCES=main.cpp template.cpp
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
