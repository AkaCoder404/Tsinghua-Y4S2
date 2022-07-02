CC=g++
CFLAGS=-o -Wall
# BINS=a
# all: $(BINS)

# %: %.cpp
# 	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r avl splay rb *.dSYM

avl: avl.cpp
	$(CC) $(CFLAGS) avl.cpp -o avl

splay: splay.cpp
	$(CC) $(CFLAGS) splay.cpp -o splay

rb: rb.cpp
	$(CC) $(CFLAGS) rb.cpp -o rb

runavl:
	./avl testcase1.txt
	./avl testcase2.txt
	./avl testcase3.txt
	./avl testcase4.txt
	./avl testcase5.txt
	./avl testcase6.txt
	./avl testcase7.txt
	./avl testcase8.txt
	./avl testcase9.txt

runsplay:
	./splay testcase1.txt
	./splay testcase2.txt
	./splay testcase3.txt
	./splay testcase4.txt
	./splay testcase5.txt
	./splay testcase6.txt
	./splay testcase7.txt
	./splay testcase8.txt
	./splay testcase9.txt

runavl2:
	./avl tc1.txt
	./avl tc2.txt
	./avl tc3.txt
	./avl tc4.txt
	./avl tc5.txt
	./avl tc6.txt
	
runsplay2:
	./splay tc1.txt
	./splay tc2.txt
	./splay tc3.txt
	./splay tc4.txt
	./splay tc5.txt
	./splay tc6.txt

