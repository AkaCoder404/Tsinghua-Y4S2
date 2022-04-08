# PA2 报告
The purpose of this lab was to implement and become familiar with the queap data structure, which is essentially queue + heap, with refrences to the priority queue data structure.

# Background
Our input is as such:
1. First we entered the number of days that we are going to cover
2. Then we entered the number of confirmed cases in a single days. 
3. Then we entered the number of days are to be traced forward each day.  
4. Then we input the number of threshold queries. 
5. Then we input the thresholds for the upper bound of confirmed low risk, and the upper bound for confirmed high risk cases for the traced days (for each day)

Our output is as such
1. output the number of low risk and medium risk confirmed cases within the traced back maximums. 

## 方法 1: Array + Brute Force
The first attempt, located in a.cpp, was a brute force algorithm which iterated backwards to find the maxmimum infected day. 

We did this for each input of the second row of inputs. It disregarded the current day, as the current day is not included when calculating the maximum infection during the days ranging from $x_{m-i}$ to $x_m$, where $i$ is our input (or the number of days being traced). We also used the fact that the number of low risk days + medium risk days + high risk days are equal to total, so in theory, we just had to find two of the three to be able to exit the loop when querying the the confirmed cases range.

Thus, this gives us a time complexity of O(n^2), which only recieves a score of 20/50 on the 50% test, of which the rest was time limit exceeded. 

## 方法 2: Queap 
The second attempt is located in the file b.cpp. 
### Part 1: Setting up the Que's
Further analysis of the question highlighted two important key points. 
> Each trace query will not trace days earlier than the trace query of the previous day

which means that the daignosis information before the earliest days of this query will be useless for subsequent queries. 
> Each trace query obtains the maximum value in a period of prefixes.

which means that if the maximum value is still within the range of the next query, the number of confirmed cases within this range less than the maximum value are also useless.

Therefore we can maintain two special queues `que_max` and `que_day`. 
- `que_max` stores information about the number of comfirmed cases that are useful for subsequent queries
- `que_day` stores the data of which day the number of confirmed cases in the  `que_max` is stored.

We make it so that the front of theses two queues can only delete elements, and the back end can delete elements and add elements.

The queues are constructed as follows:
1. Traverse the total number of days from the beginning, and subscript $i$ can get the values of the $x_i$ array and the $x_{m}$ array
2. When we have traversed to day $i$, do two checks on the queue:
   1. Check foward from the end of the queue. If the value of the confirmed cases in `que_max` is less than or equal to the value of $x_{i-1}$, that is, within the query range, this value will be replaced by $x_{i-1}$. Then, delete it and the corresponding days in `que_day` are also deleted.
   2. Check backwards from the head of the queue, if the value in `que_day` is less than $i-m_i$, that is, in this and subsequent quries, the confirmed cases with days before $i-m_i$ will not be queried. Then delete these values less than $i-m_i$ from `que_day` and correspondingly delete the number of confirmed people in the `que_max` queue.
   
3. After two checks, insert $x_{i-1}$ at the end of `que_max` and $i-1$ at the `que_day`. 

According to our definition of two queues, it is not difficult to find that `que_max` is monotonically decreasing and `que_day` is monotonically increasing.

After the two checks, values ​​with days too early to be earlier than the earliest days currently queried, and values ​​too small to be covered by larger numbers in the query range have been deleted. Therefore, after the two checks are completed, the value of the first element of the `que_max` queue is the query result $t_i$ we want on the $i$ day,

Thus, the number of days for which the query result is $t_i$ is incremented by one more day, and the value of $value_{t_i}$ can be directly increased by one. Therefore, we only need linear time to get the resulting query array.

### Part 2: Threshold Querying

Before querying, we have to preprocess the `value` array once:
1. Iterate over `value` from the beginning, let $value_{i}=value_{i}+value_{i-1}$.

In this way, the semantics of $value_{i}$ is the total number of days when the query result is less than or equal to $i$.

For the thresholds $p,q$, the low risk days are $value_{p-1}$, and the medium risk days are $value_{q-1}-value_{p-1}$.

We can get the query result in constant time every time, but we have to handle edge cases for $p$ and $q$.

### Time Complexity and Space Complexity
We traverse through **Part 1** in linear time $n$ and we traverse through **Part 2** in linear time $T$. Thus the time complexity is $O(n + T)$

Space complexity is defined by the arrays and queues, which are $n$, so space complexity is $O(n)$

## References 
- queap data structure: https://en.wikipedia.org/wiki/Queap
- prefix sum algorithm: https://en.wikipedia.org/wiki/Prefix_sum


