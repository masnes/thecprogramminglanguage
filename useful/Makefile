CC=clang
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=convertbase.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=convertbase

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
