CC=g++
CFLAGS=-o -Wall

hashtable: 
	$(CC) $(CFLAGS) hashtable.cpp -o hashtable.o -c
main: hashtable
	$(CC) $(CFLAGS) main.cpp hashtable.o -o main

# make all testcases
generator:
	$(CC) $(CFLAGS) -o generate.o generator.cpp  

I1=20000
Q1=15000
I2=100000
Q2=200000
I3=200000
Q3=250000
I4=20000
Q4=15000
I5=100000
Q5=200000
I6=200000
Q6=250000

POJ=poj
HDU=hdu

generate: generatePOJ generateHDU

generatePOJ: generate.o
	./generate.o $(POJ) $(I1) $(Q1) I$(I1)_Q$(Q1)_poj
	./generate.o $(POJ) $(I2) $(Q2) I$(I2)_Q$(Q2)_poj
	./generate.o $(POJ) $(I3) $(Q3) I$(I3)_Q$(Q3)_poj
generateHDU: generate.o
	./generate.o $(HDU) $(I4) $(Q4) I$(I4)_Q$(Q4)_hdu
	./generate.o $(HDU) $(I5) $(Q5) I$(I5)_Q$(Q5)_hdu
	./generate.o $(HDU) $(I6) $(Q6) I$(I6)_Q$(Q6)_hdu
	
# hashing strategies
NAIVE=0
ASCII=1
UTF-8=2
# probing strategies
LINEAR=0
QUADRATIC=1
OVERFLOW=2

TESTCASE1=I$(I1)_Q$(Q1)_poj
TESTCASE2=I$(I2)_Q$(Q2)_poj
TESTCASE3=I$(I3)_Q$(Q3)_poj
TESTCASE4=I$(I4)_Q$(Q4)_hdu
TESTCASE5=I$(I5)_Q$(Q5)_hdu
TESTCASE6=I$(I6)_Q$(Q6)_hdu

run1: main
	./main $(NAIVE) $(LINEAR) $(TESTCASE1)
	./main $(NAIVE) $(QUADRATIC) $(TESTCASE1)
	./main $(NAIVE) $(OVERFLOW) $(TESTCASE1)
	./main $(ASCII) $(LINEAR) $(TESTCASE1)
	./main $(ASCII) $(QUADRATIC) $(TESTCASE1)
	./main $(ASCII) $(OVERFLOW) $(TESTCASE1)
	./main $(UTF-8) $(LINEAR) $(TESTCASE1)
	./main $(UTF-8) $(QUADRATIC) $(TESTCASE1)
	./main $(UTF-8) $(OVERFLOW) $(TESTCASE1)
run2: main
	./main $(NAIVE) $(LINEAR) $(TESTCASE2)
	./main $(NAIVE) $(QUADRATIC) $(TESTCASE2)
	./main $(NAIVE) $(OVERFLOW) $(TESTCASE2)
	./main $(ASCII) $(LINEAR) $(TESTCASE2)
	./main $(ASCII) $(QUADRATIC) $(TESTCASE2)
	./main $(ASCII) $(OVERFLOW) $(TESTCASE2)
	./main $(UTF-8) $(LINEAR) $(TESTCASE2)
	./main $(UTF-8) $(QUADRATIC) $(TESTCASE2)
	./main $(UTF-8) $(OVERFLOW) $(TESTCASE2)
run3: main
	./main $(NAIVE) $(LINEAR) $(TESTCASE3)
	./main $(NAIVE) $(QUADRATIC) $(TESTCASE3)
	./main $(NAIVE) $(OVERFLOW) $(TESTCASE3)
	./main $(ASCII) $(LINEAR) $(TESTCASE3)
	./main $(ASCII) $(QUADRATIC) $(TESTCASE3)
	./main $(ASCII) $(OVERFLOW) $(TESTCASE3)
	./main $(UTF-8) $(LINEAR) $(TESTCASE3)
	./main $(UTF-8) $(QUADRATIC) $(TESTCASE3)
	./main $(UTF-8) $(OVERFLOW) $(TESTCASE3)
run4: main
	./main $(NAIVE) $(LINEAR) $(TESTCASE4)
	./main $(NAIVE) $(QUADRATIC) $(TESTCASE4)
	./main $(NAIVE) $(OVERFLOW) $(TESTCASE4)
	./main $(ASCII) $(LINEAR) $(TESTCASE4)
	./main $(ASCII) $(QUADRATIC) $(TESTCASE4)
	./main $(ASCII) $(OVERFLOW) $(TESTCASE4)
	./main $(UTF-8) $(LINEAR) $(TESTCASE4)
	./main $(UTF-8) $(QUADRATIC) $(TESTCASE4)
	./main $(UTF-8) $(OVERFLOW) $(TESTCASE4)
run5: main
	./main $(NAIVE) $(LINEAR) $(TESTCASE5)
	./main $(NAIVE) $(QUADRATIC) $(TESTCASE5)
	./main $(NAIVE) $(OVERFLOW) $(TESTCASE5)
	./main $(ASCII) $(LINEAR) $(TESTCASE5)
	./main $(ASCII) $(QUADRATIC) $(TESTCASE5)
	./main $(ASCII) $(OVERFLOW) $(TESTCASE5)
	./main $(UTF-8) $(LINEAR) $(TESTCASE5)
	./main $(UTF-8) $(QUADRATIC) $(TESTCASE5)
	./main $(UTF-8) $(OVERFLOW) $(TESTCASE5)
run6: main
	./main $(NAIVE) $(LINEAR) $(TESTCASE6)
	./main $(NAIVE) $(QUADRATIC) $(TESTCASE6)
	./main $(NAIVE) $(OVERFLOW) $(TESTCASE6)
	./main $(ASCII) $(LINEAR) $(TESTCASE6)
	./main $(ASCII) $(QUADRATIC) $(TESTCASE6)
	./main $(ASCII) $(OVERFLOW) $(TESTCASE6)
	./main $(UTF-8) $(LINEAR) $(TESTCASE6)
	./main $(UTF-8) $(QUADRATIC) $(TESTCASE6)
	./main $(UTF-8) $(OVERFLOW) $(TESTCASE6)

clean:
	$(RM) -r hashtable.o main generator.o *.dSYM

cleantests:
	$(RM) -r testsets/*.in