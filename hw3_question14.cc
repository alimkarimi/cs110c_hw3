#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
using namespace std;

/**
 * @brief The Vlint class is a class to represent very large (> long long) integer numbers 
 using std::string 
 as string has virtually unlimited storage (there is a limit but it is very large).
 Since this is a new integer format, we need to support operators associated like addition.
 */
class Vlint {
private:
  std::string integer;
  int length = 0;
public:
  // constructor
  Vlint(std::string strint){
	this->integer = strint;
    length = integer.length();
  }
 //Destructor
  ~Vlint(){
  }
  // Getters
  int get_length() const{
    return this->length;
  }
 std::string getint() const{ // Need to be a const as we pass them as const at the constructor
    return this->integer;
  }
 // Adition
  Vlint operator+(const Vlint &otherint)const {
  

  if (length < 18 && otherint.length < 18)   // validation to use int addition IF we are confident that it will not result
  	//in a bogus number. I picked 18 digits, since 20 is the max for a long long int. A 19 digit number added to a 19 digit number can
  	//result in a 20 digit number or a number greater than the max theoretical long long int.
  {
  		long long int num1 = stoi(integer);
  		long long int num2 = stoi(otherint.integer);
  		long long int num3 = num1 + num2;
  		std::cout << num3 << std::endl;
  }
  if (length >=18  || otherint.length >= 18)
  {
  		//std::cout << static_cast<int>(otherint.integer[length - 1]) - 48 << "+" << static_cast<int>(integer[length -1]) - 48 << std::endl;
  		int numx;
  		int carryover = 0;
  		bool carryoverFlag = 0;
  		int length1 = otherint.length;
  		int length2 = length;
  		int numPreZerosNeeded;
  		string modifiedInteger;
  		if (length1 > length2) {
  			//cout << "l1 is bigger" << endl;
  			numPreZerosNeeded = length1 - length2;
  			string preZeros = "0";
  			for (int i = 0; i <= numPreZerosNeeded -2; i++)
  			{
  				preZeros = preZeros + "0";
  				//cout << preZeros << endl;
  			}

  			modifiedInteger = preZeros + integer;
  			//cout << modifiedInteger << endl;
  			Vlint tempnum(modifiedInteger);
  			//cout << tempnum.integer << "is the updated int " << endl;
  			//cout << "length will need " << numPreZerosNeeded << " pre zeros" << endl;
  		} 
  		if (length2 > length1){
  			//cout << "in l2" << endl;
  			numPreZerosNeeded = length2 - length1;
  			string preZeros = "0";
  			for (int i = 0; i <= numPreZerosNeeded -2; i++)
  			{
  				preZeros = preZeros + "0";
  				//cout << preZeros << endl;
  			}

  			modifiedInteger = preZeros + otherint.integer;
  			//cout << modifiedInteger << endl;
  			Vlint tempnum(modifiedInteger);
  			//cout << tempnum.integer << "is the updated int " << endl;
  			//cout << "otherint.length will need " << numPreZerosNeeded << " pre zeros" << endl;


  		}
  		int maxLength = std::max(otherint.length, length);
  		std::string sum[maxLength + 1];
  		//std::cout << maxLength << " is the max length of both strings, so the max length of a number from that sum is " << maxLength + 1 << std::endl;
  		for (int i = 0; i <= maxLength -1; i++)
  		{
  			//std::cout << "i is now " << i << std::endl;
  			if (length1 == length2)
  			{
  				numx = (static_cast<int>(otherint.integer[otherint.length - (i +1)]) -48) + static_cast<int>(integer[length-(i + 1)]) - 48 + carryover;
  				//cout << "just added " << (static_cast<int>(otherint.integer[otherint.length - (i +1)]) -48) << " + " << (static_cast<int>(integer[length-(i + 1)]) - 48) << " + " << carryover << endl;
  			}
  			if (length1 > length2)
  			{
  				
  				numx = (static_cast<int>(otherint.integer[otherint.length - (i +1)]) -48) + (static_cast<int>(modifiedInteger[modifiedInteger.length()-(i + 1)]) -48) + carryover;
  				//std::cout << "just added " << (static_cast<int>(otherint.integer[otherint.length - (i +1)]) -48) << " + " << (static_cast<int>(modifiedInteger[modifiedInteger.length()-(i + 1)]) -48) << " + " << carryover << std::endl;
  			}
  			if (length2 > length1)
  			{
  				numx = (static_cast<int>(modifiedInteger[modifiedInteger.length()-(i + 1)]) -48) + (static_cast<int>(integer[length-(i + 1)]) - 48) + carryover;
  				//std::cout << "just added " << (static_cast<int>(modifiedInteger[modifiedInteger.length()-(i + 1)]) -48) << " + " << (static_cast<int>(integer[length-(i + 1)]) - 48) << " + " << carryover << std::endl;
  			}
  			
  			//std::cout << "numx is " << numx << std::endl;

  			//std::cout << "deciding on carryover" << std::endl;
  			string temp = std::to_string(numx);
  			//cout << "temp is " << temp << endl;
  			if (numx > 9)
  			{
  				if (i == std::max(otherint.length, length)-1)
  				{
  					//cout << "in i equality " << endl;
  					//std::cout << "casting to string " << std:: endl;
  					sum[maxLength - (i + 1)] = std::to_string(numx);
  					//std::cout << "parsed out " << sum[maxLength - (i + 1)] << std::endl;
  					carryover = 0;
  					//std::cout << "done casting and displaying that pos in string what" << endl;  
  				}
  				
  				else
  				{
	  				//std::cout << "casting to string " << std:: endl;
	  				carryover = 1;
	  				sum[maxLength - (i + 1)] = temp[1];
	  				//std::cout << "parsed out " << sum[maxLength - (i + 1)] << std::endl;
					//std::cout << "done casting and displaying that pos in string init" << std::endl;
				}
  			}
  			if (numx <=9)
  			{
  				//std::cout << "casting to string " << std:: endl;
  				sum[maxLength - (i + 1)] = std::to_string(numx);
  				//std::cout << "parsed out " << sum[maxLength - (i + 1)] << std::endl;
  				carryover = 0;
  				//std::cout << "done casting and displaying that pos in string what" << std::endl;  			
  			}

  		}
  		

  		for (int i = 0; i <= std::max(otherint.length, length); i++)
  		{
  			std::cout << sum[i];		
  		}
  		cout << endl;
  		
  	}
  	return otherint;
  }
  // check evenness 
  bool is_even(){

  // Your code goes here
  if (integer[length -1] %2 == 0)
  {
  		cout << "the number is even" << endl;
  		return 1;  	
  }

  else
  {
   		cout << "the number is odd" << endl;
  		return 0; 	
  }
 }
};

int main(int argc, char *argv[])
{


	cout << "//sum of 1 + 1" << endl;
	Vlint num1("1");
	Vlint num2("1");
	num1 + num2; 

	cout << "//sum of 18446744073708551618 and 11111111111111111111" << endl;
	Vlint num3("18446744073708551618");
	Vlint num4("11111111111111111111");
	num3 + num4;

	cout << "//sum of 18446744073708551618 and 111111111111111111111" << endl;
	Vlint num5("18446744073708551618");
	Vlint num6("111111111111111111111");
	num5 + num6;

	cout << "//sum of 18446744073708551618 and 22222222222222222222" << endl;
	Vlint num7("18446744073708551618");
	Vlint num8("22222222222222222222");
	num7 + num8;

	cout << "//sum of sum of 99999999999999999999 and  999999999999999999999999" << endl;
	Vlint num9("99999999999999999999");
	Vlint num10("999999999999999999999999");
	num9 + num10;

	cout << "//showing that 99999999999999999999 is odd" << endl;
	Vlint num11("99999999999999999999");
	cout << num11.is_even() << endl;

	//RUNTIME ANALYSIS
	/*
		the direct long long int addition is 3 operations - converting the first "number" to an int and then the second 
		"number" to an int, followed by actually adding them. This is a constant time operation for any strings that pass the 
		validation step

		The runtime for adding numbers with more than 18 digits is significantly longer. I will focus on the most expensive 
		part of the addition: the for loop that starts with for (int i = 0; i <= maxLength -1; i++) (found on line 94). In this loop,
		we have to cast an element in each string, calculate the sum, and then figure out if that sum is more than 9 so that a value of 1
		needs to get carried over to the next elements that are added. From there, the calculated sum is assigned to a corresponding
		element in the string called "sum". The number of times this set of operations will run is dependent on the length of the longest string.
		Therefore, we can call this runtime n, where n is the length of the longest string. This obviously, is a lot longer than the 3 operations for integer addition, which is why
		the loop is only called if both "numbers" that need to be added are more than 18 characters.

	*/



  return 0;
}
