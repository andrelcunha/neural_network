/*
 *  my_random.h
 *  My_project
 *
 *  Modificated by Andre Luis da Cunha on 17/03/09.
 *
 *
 */

/**********************************************
 /*   A Basic Linear Congruential Generator
 /*  ---------------------------------------
 /*  Program By: NickDMax for Dreamincode.net
 /*  02/23/2007
 /*
 /*  You may use this code as you see fit
 /**********************************************/
#include <iostream>
#include <ctime>

//This class will give satisfy basic
// random number considerations for
// games an general apps.
// WARNING: Not for Cryprographic use
//   Not for statistical methods.
class BasicLCG {

private:
	unsigned long iCurrent;
public:
	BasicLCG();
	BasicLCG(unsigned long);
	~BasicLCG(){};
	void seed(unsigned long iSeed);
	unsigned long nextNumber(); //get the next random number
	unsigned short int nextInt();
	unsigned char nextChar();
	int nextBit();
	double nextDouble();
	int inRange(int min, int max);
};



