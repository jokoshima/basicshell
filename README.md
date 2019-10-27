## COSC 301 Homework 3

See lab instructions posted on Moodle.

## Your feedback

 * How long did you spend on this homework? 4 days

 * What did you think about it?  What was good?  What could be improved?
 It was a challenging homework. But it was very interesting.

## Grade and my feedback

94/100

Good work.  Lots of things work very well -- basic shell operation and both sequential and background processes work nicely.  List code all looks good.  Built-in commands look good.

Just one bug that I saw:

 - In the `for` loop starting on line 201, there's a problem in that if you remove a process from the list, your `for` loop update (`curr = curr -> next`) will reference the recently freed node which gives a "use after free" error.  Sometimes this will be a segfault and other times not, but it needs to be fixed.

Also, `main` is still rather long and could/should be broken down into some smaller functions.
