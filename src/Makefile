CC=gcc
CFLAGS= -c -Wall -Werror -Wextra
SOURCES=calc.c drawing.c lexemes.c stack.c graph.c
OBJECTS=$(SOURCES:.c=.o)

EXECUTABLE=../build/graph


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf ../build/* *.o

rebuild: clean all