CC=g++
CFLAGS=-Wall -std=c++11
BINS=binarySearch
all: clean binarySearch

binarySearch: binarySearch.cpp
	$(CC) $(CFLAGS) -o binaryS binarySearch.cpp

clean:
	@echo "[CLN] Removing binary files"
	@rm -f $(BINS)
