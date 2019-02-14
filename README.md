# How to test
Download testcases.c and Makefile (or copy the test target in the Makefile to
your own Makefile). Comment out the Main method in your pa3d.c file so that
it does not conflict with testcases.c Main method.

Compile:
    
    make test
    
And then to run:

    ./runTests <test number>
    
 
Note:
Running test 12 will run the program forever (until ieng9 gives an Exceeded max time limit error). This test is
useful for seeing if any crash or deadlock would happen at all. It essentially spawns car randomly with random delay
and just keeps running until you quit the program.

To run all the tests (except test 12) and save your results.

    chmod +x runAll.sh
    ./runAll.sh
    
Program outputs will be saved to <test number>.OUTPUT