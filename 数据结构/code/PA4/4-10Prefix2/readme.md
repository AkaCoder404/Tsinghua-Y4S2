# 4-10 Prefix2

## Background 
The goal of this algorithm was to implemenOt the Z algorithm for pattern matching. The Z algorithm: Z[K] is the largest prefix of substring starting at K which is also a prefix of the string. The goal is to find the sum of all the elements in Z[K]

## Method 1: Brute Force
The brute force method simply compares all prefix characters of the suffix substrings and the string itself for all the suffix substrings S[i, n - 1], where i = 0, 1, 2, ..., n-1. The brute force method of pattern matching is about O(n^2). Where the n is the length of the string,

The brute force method only received a 15/50. 

## Method 2: Z algorithm
The Z algorithm utilizes the fact that part of the longest common prefixes for each substring and the string itself have already been calculated before. So instead of recomparing the whole substring, we can partially use information that we have gathered before. The Z algorithm is explained in the problem so I used that as my main reference when completing this problem. 

The algorithm received a 90/90.

## References
https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
https://en.wikipedia.org/wiki/Category:String_matching_algorithms



