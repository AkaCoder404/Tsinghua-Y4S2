# CST 3-7 History

The goal of this experiment to use the idea of hashing to keep track of past events. 

## Method 1
This method used an array `hash` to keep track of all the students, where `hash[student]` represents the answer to the last query regarding that studennt. 

Thus, whenever a new student is makes a submission, we simply store the current submission record count into the hash table, and the `newAnswer` (answer used for the next query is also set) is also st to the current submission record count. Otherwise, if the student already exists, the `newAnswer` is simply the current value of `hash[student]`, which stores the answer to the previous query of the student, and then `hash[student]` is updated.

This method received a 90/90 on the test, and thus did not need to be improved 

### Time Complexity and Space Complexity
Since there is only one for loop for each input, the time complexity is O(n), where n is the number of submissions. 

The space complexity is only comprised of the the space necessary for the hash table. Thus the space complexity is also O(n)


## References
No references used