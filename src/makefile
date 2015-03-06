CC= gcc
CCFLAGS= -Wall -Werror -std=c99 -pedantic -g -o

all: indexer

indexer:
	$(CC) $(CCFLAGS) indexer indexer.c hashmap.c hashmap.h


clean:
	rm indexer
