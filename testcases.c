#include "pa3d.c"
#include <stdlib.h>


// Car 1 enters EAST, car 3 comes to the EAST before car 1 exits, so car 3
// enters the road. Car 4 waits at WEST until car 3 finishes. Car 2 enters
// WEST later along with car 4
void test1() {
	if (Fork () == 0) {
		Delay (1200);			// car 2
		driveRoad (WEST, 60);
		Exit ();
	}

	if (Fork () == 0) {
		Delay (800);			// car 3
		driveRoad (EAST, 50);
		Exit ();
	}

	if (Fork () == 0) {
		Delay (900);			// car 4
		driveRoad (WEST, 30);
		Exit ();
	}

	driveRoad (EAST, 30);			// car 1
}


// 5 cars at each gate (entered approximately at the same time)
// Should alternate on the road
void test2() {
	int i;
	for (i = 0; i < 5; i++) {
		if (Fork() == 0) {
			driveRoad(WEST, 40);
			Exit();
		}
		if (Fork() == 0 && i != 4) {
			driveRoad(EAST, 40);
			Exit();
		}
	}

	driveRoad (EAST, 40);			// car 1
}


// Car 1 comes in from the EAST, then car 2 comes in from the WEST. And then
// car 3 comes in from the WEST. And then car 4 comes in from the EAST.
// Once car 1 finishes, car 2 should be allowed to enter. Car 3 now cannot
// enter from the WEST even though it is going in the same direction as car 2
// and that it arrived before car 4 because car 4 has come in and is waiting on
// the EAST side
// Piazza @353
void test3() {
	if (Fork () == 0) {
		Delay (50);			// car 2
		driveRoad (WEST, 60);
		Exit ();
	}

	if (Fork () == 0) {
		Delay (100);			// car 3
		driveRoad (WEST, 50);
		Exit ();
	}

	if (Fork () == 0) {
		Delay (150);			// car 4
		driveRoad (EAST, 50);
		Exit ();
	}

	driveRoad (EAST, 80);			// car 1
}

// Rule B)
// 10 cars coming from the same side (WEST), with the one that comes later going
// faster than the ones that came before
// Cars should come in the same order 1 2 ... 10 and they should be allowed
// on the road at the same time as soon as an empty spot is present in front
// of them
void test4() {	
	int i = 0;
	for (i = 1; i <= 10; i++) {
		if (Fork() == 0) {
			Delay(i * 75);
			driveRoad(WEST, 10 + i * 10);
			Exit();
		}
	}
	driveRoad (WEST, 10);			// car 1
}

// Rule B)
// 10 cars coming from the same side (EAST), with the one that comes later going
// faster than the ones that came before
// Cars should come in the same order 1 2 ... 10 and they should be allowed
// on the road at the same time as soon as an empty spot is present in front
// of them
void test5() {	
	int i = 0;
	for (i = 1; i <= 10; i++) {
		if (Fork() == 0) {
			Delay(i * 75);
			driveRoad(EAST, 10 + i * 10);
			Exit();
		}
	}
	driveRoad (EAST, 10);			// car 1
}

// Tests Rule C1, car 2 should not enter when car 1 is in spot 1
// Car 1 and 2 come in from the WEST at the same time (Car 1 will enter first). 
// Car 3 then comes in a moment later from the EAST (should be before car 1 
// exits the road). Car 4 comes from the WEST after car 3.
// Output: Car 1 should go first, then car 2 will follow right after. Car 3
// will go once car 2 exits the road then car 4 will go once car 3 exits the
// road
void test6() {
	if (Fork () == 0) {
		// car 2
		driveRoad (WEST, 60);
		Exit ();
	}

	if (Fork () == 0) {
		Delay (200);			// car 3
		driveRoad (EAST, 50);
		Exit ();
	}

	if (Fork () == 0) {
		Delay (400);			// car 4
		driveRoad (WEST, 50);
		Exit ();
	}

	driveRoad (WEST, 10);			// car 1
}

// Tests Rule C2 (also D).
// Car 1 enters from the WEST. Car 3 comes from EAST. Car 2 shows up at WEST
// but has to wait because car 3 is waiting at EAST.
void test7() {
	if (Fork () == 0) {
		// car 2
		Delay(100);
		driveRoad (WEST, 60);
		Exit ();
	}

	if (Fork () == 0) {
		// car 3
		driveRoad (EAST, 50);
		Exit ();
	}

	driveRoad (WEST, 40);			// car 1
}

// Cars 1 through 6 come to WEST. Before all 6 cars get to enter road, 
// Car 7 will come to EAST (couple cars might enter before car 7 come and
// stop the rest from entering).
// For example, car 1-3 come. 2 has to wait for 1 to clear the first spot
// before it enters. Then 3 has to wait for 2 to clear the first spot so it
// could enter. Now 7 enters the EAST. 4-6 have to wait even though it came
// first but because it hasn't gotten on the road, it still has to assess
// whether the otherside has any car that came.
void test8() {
	if (Fork () == 0) {
		// car 2
		driveRoad (WEST, 60);
		Exit ();
	}

	if (Fork () == 0) {
		// car 3
		driveRoad (WEST, 50);
		Exit ();
	}

	if (Fork () == 0) {
		// car 4
		driveRoad (WEST, 50);
		Exit ();
	}

	if (Fork () == 0) {
		// car 5
		driveRoad (WEST, 60);
		Exit ();
	}

	if (Fork () == 0) {
		// car 6
		driveRoad (WEST, 50);
		Exit ();
	}

	if (Fork () == 0) {
		// car 7
		Delay(150);
		driveRoad (EAST, 50);
		Exit ();
	}

	driveRoad (WEST, 40);			// car 1
}

// Tests Rule F. If road is free, any car should be able to enter
// Car 1 and 3 enter WEST. Car 2 and 4 enter EAST. A while later (after 
// cars 1-4 all exit the road), car 5 enters.
void test9() {
	if (Fork () == 0) {
		// car 2
		driveRoad (EAST, 100);
		Exit ();
	}

	if (Fork () == 0) {
		// car 3
		driveRoad (WEST, 100);
		Exit ();
	}

	if (Fork () == 0) {
		// car 4
		driveRoad (EAST, 100);
		Exit ();
	}

	if (Fork () == 0) {
		// car 5
		Delay(3000);
		driveRoad (WEST, 50);
		Exit ();
	}

	driveRoad (WEST, 100);			// car 1
}

// 2 cars different direction. Car 1 (WEST) first then car 2 (EAST)
void test10() {
	if (Fork() == 0) {
		Delay(100);
		driveRoad(EAST, 50);
		Exit();
	}
	driveRoad(WEST, 50);
}

// 2 cars different direction. Car 1 (EAST) first then car 2 (WEST)
void test11() {
	if (Fork() == 0) {
		Delay(100);
		driveRoad(WEST, 50);
		Exit();
	}
	driveRoad(EAST, 50);
}


#define NUMTESTS 11
void (*tests[])() = {test1, test2, test3, test4, test5, test6, test7, test8,
test9, test10, test11};

void Main(int argc, char* argv[]) {
	if (argc < 2) {
		Printf("Must specify which test case to run as an argument (1,2,3,...)");
		Exit();
	}

	char* endptr;
	int index = strtol(argv[1], &endptr, 10);
	if (*endptr != NULL) {
		Printf("Argument must be a number\n");
		Exit();
	}

	if (index < 1 || index > NUMTESTS) {
		Printf("Test case number must be between 1 and %d\n", NUMTESTS);
		Exit();
	}

	InitRoad();

	Printf("Running test %d\n\n", index);
	tests[index-1]();

	Exit();
}
