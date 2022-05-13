CC=g++
CFLAGS=-o -Wall
BINS=e
all: $(BINS)

%: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(BINS) *.dSYM

