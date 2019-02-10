# How to test
Download testcases.c and Makefile (or copy the test target in the Makefile to
your own Makefile). Comment out the Main method in your pa3d.c file so that
it does not conflict with testcases.c Main method.

Compile:
    
    make test
    
And then to run:

    ./runTests <test number>