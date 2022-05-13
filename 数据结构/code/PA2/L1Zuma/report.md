# Lab 1 Zuma

The purpose of this lab is analyze algorithms for a certain task and try to determine which of the following states the code will run into, such as `Accepted`, `Wrong Answer`, `Time Limit Exceeded`, `Memory Limit Exceeded`, `Runtime Error` and so on. We have to determine the most severe type of error the code will have given the hiearchy `Wrong Answer > Runtime Error > Time Limit Exceeded = Memory Limit Exceeded` by creating testcases that would do so.

The testcases are located in the input folder

## Summary
1. Runtime Error
2. Runtime Error
3. Time Limit Exceeded
4. Wrong Answer
5. Wrong Answer
6. Time Limit Exceeded
7. Wrong Answer
8. Wrong Answer
9. 【没有做出来】
10. Wrong Answer

## 01.cpp

### Runtime Error
During the recursive call of the `play` function, the value of rank might iterate to become zero, so when `play` is called for the next iteration, the rank will be -1, which will result in an out of bounds access. 

For example, the test case 
```
AABB
1
0 A
```

will try to access the string with rank of -1, the exact error when compiling with `g++` is 

```
terminate called after throwing an instance of 'std::out_of_range'
   what():  basic_string::at: __n (which is 18446744073709551615) >= this->size() (which is 2)
```

### Time Limit Exceeded 
The efficiency of this program is also not high enough. The complexity of each insertion and delition of a string linear structure is $O(n)$, so when the input size is large, it will result in a TLE.

Therefore, in order to create the largest data size, so that both `n` and `m `are 500000, insert the char at the position where the rank is 0 each time.

### Result
However, like explained above, this will result in Runtime Error first because it has a higher severity than time limit exceeded or memory limit exceeded

## 02.cpp

### Runtime Error
Compared to 01.cpp, this code adds a judgement before call `play` to prevent string access with rank being -1. However, it does not prevent the access of the empty string `a` when rank is zero. So the program may result in an out of bounds access, creating a runtime another runtime error.

This exact error that I have when compiling with `g++` is 
```
terminate called after throwing an instance of 'std::out_of_range'
  what():  basic_string::at: __n (which is 18446744073709551615) >= this->size() (which is 0)
```

For example, the test case 
```
ACCBA
4
1 B
0 A
2 B
4 C
```
would break the code when trying to call a `play` with a rank of zero when the string is already empty. 

### Time Limit Exceeded
The efficiency of this algorithm is the same as 01.cpp, and so to construct the test case that results in such will also be the same

### Result
This has a runtime error, with higher severity than time limit exceeded, thus the test case given will produce run time error.


## 03.cpp
There is no long a runtime error as the codes above. Thus, accessing the string with rank as -1 and accessing of empty string when rank is zero no longer occurs. Instead, it is judged whether `left` is within the range of `a.size(),` which can also avoid crossing the boundary, and the correctness is guaranteed.

### Time Limit Exceeded
The efficiency of this algorithm is the same as 01.cpp and 02.cpp, so the exact same test case can be used to create time limit exceeded. 

### Result
Thus, this will produce a time limit exceeded error. 

## 04.cpp

### Wrong Answer
There is a serious logic error in this code. In the `play` function, `left` is decremented to the first position where the character is different. However, `left` is not then incremented by 1, to get the position of the first same character. This is a key difference between this program and the other programs. The `right` value is incremented to the first character positon where it is different.

For example, if `play(3)` is called for AABBCC, we would get `left` = 1, and `right` = 4

Thus, in the following judgment is that if $right-left\ge3$, the the `erase` performs the deletion operation, but the the boundary conditions are not correct, and the substring of length 2 may be deleted, which is not the case. 

So we can simply use this to construct the erronous case.
```
AABCC
1
3 B
```
results in ACC, which is not the correct answer. 

### Result
The most serious error is wrong answer, thus it will produce wrong answer

## 05.cpp

### Wrong Answer 
The difference between this and 03.cpp is the method of input. The way to read the input data is not robust enough, `cin` will automatically skip whitespace characters. Thus if the inital string is empty, the program will read `m` into the initial string value, and thus produce a wrong answer.

Thus, we can simply construct an example where the first line of input is simply empty, such as 

```

1 
0 A
```
which will produce wrong answer

### Result
This will produce wrong answer error


## 06.cpp
### Time Limit Exceeded
The problem with this code is that after the inital bead sequence is read and segmented, the number of elements in each segmented is no longer monitored and reassigned. Thus causes the number of elements in each segment to follow the insertion and removal operations, which gradually becomes zero or exceeds the bounds.

Thus this case is equivalent to the efficiency of 03.cpp because there is no segmentation, as every element inserted after an element has to shifted back one place, thus the time complexity is $O(n)$ and the overall time limited is $O(n^2)$, which will result in time limit exceeded.

Thus, we have to construct test cases where every bead is pushed shifted back one place


### Result
The error is time limit exceeded


## 7.cpp
Unlike 06.cpp, the number of elements in each segment is monitored dand reassigned.

### Wrong Answer
The problem with this code is that when calculating the left (open) boundary that needs to be elimanted, the code does not consider the length of the last continuous space of l is empty, that is 
```
plen[l.first- 1]==0
```
directly moves l to this continuous space, so that it is impossible to continue to search for the previous positon, resulting in errors where elimination is sometimes possible but always performed. 

Thus, we have to construct test cases where the code divides the inital bead sequence into a group of 2048 (the length of a segment) and divides it into different groups to form a 2D array, so that the inital sequence can be divided into three groups of 0, 1, and 2, such that the last element of `p[0]` is the same as the first element of `p[2]`, and the beads of `p[1]` are all eleminated by inserting beads to make it an empty array. 
That is, `plen[1] == 0`. 

In this way, if a bead with the same element at the beginning of p[2] is inserted, the 3 beads that should have been eliminated. Since p[1] is empty, the left boundary l cannot reach the end of p[0], which is the end index, so the three beads cannot be eliminated,

## 8.cpp
### Wrong Answer
The problem with this code is that simply does not consider consecutive eliminations.

Thus, we just have to create a short continuous elimination test case

### Result,

## 9.cpp
【没有做出来】

## 10.cpp
### Wrong Answer
The problem with this code is that when it performs the elimination operation, if the left and right boundaries that are going to be eliminated are not in the same segment, the entire length of the segment where the left boundary is located will be set to 0. This is equivalent to clearing them all, which will result in an error.

Thus, we simply have to construct a sequence so that it can be divided into two segments. After inserting the next bead, if the left and right boundaries of the sequence to be eliminated are in different segments, there will be a problem with elimination

