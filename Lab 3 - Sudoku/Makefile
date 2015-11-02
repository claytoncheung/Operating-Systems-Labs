CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LFLAGS = 
LIBS = -lm
SOURCES = sudoku.c validator.c solver.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = sudoku.exe
.PHONY: clean help

sudoku.exe : sudoku.o validator.o solver.o 
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and .exe files"
