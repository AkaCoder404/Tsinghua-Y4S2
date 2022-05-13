CC=g++
CFLAGS=-o -Wall
BINS=b
all: $(BINS)

%: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(BINS) *.dSYM

