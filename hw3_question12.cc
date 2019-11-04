#include <iostream>
#include <cmath>
using namespace std;

double altSeries(int n);

int main()
{
	cout << altSeries(100) << endl;
	/*	
		One will see that when the input is 100, the function call results in 
		0.688172 as the answer. The actual value of ln2 is 0.69314718056. If the input were 1,000,
		the answer would get closer to the value of ln2 (0.69314718056). 
	*/
}

double altSeries(int n)
{
	static double value = 0;
	if (n == 1) //this is the basecase
		return value + 1;
	else		
		value = value + pow(-1, n -1) / n;
		return altSeries(n-1); //this is the recurrence relation - every time that the input isn't 1, 
		//decrement by 1 until the numerator divided by the denominator is == 1. 
}