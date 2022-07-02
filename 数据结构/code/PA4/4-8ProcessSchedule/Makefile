CC=g++
CFLAGS=-o -Wall
# BINS=a
# all: $(BINS)

# %: %.cpp
# 	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r a b c *.dSYM

a: a.cpp
	$(CC) $(CFLAGS) a.cpp -o a

b: b.cpp
	$(CC) $(CFLAGS) b.cpp -o b

c: c.cpp
	$(CC) $(CFLAGS) c.cpp -o c