CC = gcc
CFLAGS = -Wall -lm
NAME = console_calculator
PREFIX = /usr/local

all:
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

.PHONY: clean

clean:
	rm -f $(NAME)

.PHONY: install

install:
	cp $(NAME) $(PREFIX)/bin/

.PHONY: uninstall
	
uninstall:
	rm -f $(PREFIX)/bin/$(NAME)
