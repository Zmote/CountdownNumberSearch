# CountdownNumberSearch
Console application with which it will be able to find out with what series of
operations a certain target number can be reached, using only addition, subtraction, multiplication and division. 
No fractions are allowed, no higher mathematical operations are allowed, neither. Rules of Countdown. 

# Dependencies
Uses simple Math expression evaluator libray CMathParser: https://github.com/NTDLS/CMathParser

# Note
Preliminary target of this exercise was to refresh C++ knowledge. So some approaches might be less than optimal.
Nonetheless the current implementation manages to calculate relatively accurate results within 20s by
bruteforcing through ~84 Million variations.