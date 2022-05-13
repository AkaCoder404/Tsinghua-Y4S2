# CST 3-6 Hacker Report

The hacker Y reads the databse of a certain website and began to crack the user's password.


For password plaintext string M, it is stored in the database as 

$$hash(M) = CRC32(M + salt)$$

where 
- CRC32 is a function that converts a string of arbitary length into a 32-bit integer 
- salt is a string
- '+' represents the cconcatenation of strings

This site states that every character of passwords and salts must be one of the 18 characters below

`0123456789tsinghua`

Due to a design error, the site took the same salt for every user.

Little Y's task is to hash the password for each record in the database, hash(M), try to inverse and crack its plaintext M

Because there are infinitely man inverse results of a hash value, we give some restrictions on the answer.

During the $i$th time inversing, ($i$ starts at 1), we only consider M in the plantext set Di.
If it is possible to find a unique plaintext in the set plaintext set Di, output this plaintext, if there isn't, output `No`. If there are many matches, output `Duplicate`

The set $D_i$ is defined as
1. $D_i$ = {1~5 bit plaintext passowrd}, a plaintext password with length 1 to 5 and contains only the charcters above
2. $D_{i+1 } = D_i \cup A_i$, where $A_i$ is the first $i$ ciphertexts, the first letters of the last successfully cracked plaintext are connected in sequence
