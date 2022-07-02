CC=g++
CFLAGS=-o -Wall
# BINS=a
# all: $(BINS)

# %: %.cpp
# 	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r generator *.dSYM

generator: generator.cpp
	$(CC) $(CFLAGS) generator.cpp -o generator

run:
	./generator 1
	./generator 2
	./generator 3
	./generator 4
	./generator 5
	./generator 6
	./generator 7
	./generator 8
	./generator 9
