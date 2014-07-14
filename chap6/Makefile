CFLAGS=-Wall -lm -g
CC=clang
LDFLAGS=
SOURCES=distinct_words.c getch.c getword_handling.c hashing.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=distinct_words

all: distinct_words

distinct_words: objects
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

objects:
	$(CC) -c $(LDFLAGS) $(SOURCES)

$@:
	$(CC) $(CFLAGS) $@ -o $@

# .c.o:
	# $(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCES:.c=) $(OBJECTS)
