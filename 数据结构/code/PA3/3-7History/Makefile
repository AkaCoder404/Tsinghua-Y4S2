CC=g++
CFLAGS=-o -Wall
BINS=a
all: $(BINS)

%: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(BINS) *.dSYM

