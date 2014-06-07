CFLAGS=-Wall -g -c -lm
CC=clang
LDFLAGS=
SOURCES=reversepolishcalc.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=reversepolishcalc

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCES:.c=)
