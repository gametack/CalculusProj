#include <cassert>  // assert()
#include <ctime>	// time()
#include <iomanip>	// setw(), setprecision(), setfill() etc.
#include <iostream>	// cin, cout, etc.
#include <string>	// string class
#include <vector>
#include <stack>
#include <Windows.h>
#include <queue>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;


ofstream derivativesteps;
ofstream integralsteps;
ofstream graphout("outputs\\graphoutput.txt");

//convert between variables
//T can contain different variable types to be converted to specified variable using boost rational or lexical cast
template <class T>
int toInt (T a) 
{
	return boost::lexical_cast<int>(a);
}

template <class T>
string toString (T a) 
{
	return boost::lexical_cast<string>(a);
}

template <class T>
string toDouble (T a) 
{
	return boost::rational_cast<double>(a);
}

template <class T>
string toLongDouble (T a) 
{
	return boost::rational_cast<long double>(a);
}

template <class T>
string toRationalInt (T a) 
{
	return boost::lexical_cast<rational<int>>(a);
}

