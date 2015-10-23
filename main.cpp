#include <iostream>

using namespace std;

bool characteristic(char numString[], int& c);
bool mantissa(char numString[], int& numerator, int& denominator);
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    //some numbers to work with
    char number1[] = "   123.456";
    char number2[] = "-456  ";
    
    //a place for the answer
    char answer[100];
    
    //intermediate values
    int c1, n1, d1;
    int c2, n2, d2;
    
    //if the conversion from C string to integers can take place
    if(characteristic(number1, c1) && mantissa(number1, n1, d1) &&
       characteristic(number2, c2) && mantissa(number2, n2, d2))
    {
        //do some math with the numbers
        if(add(c1, n1, d1, c2, n2, d2, answer, 100))
        {
            //display string with answer -332.544
            cout<<"The sum of the numbers "<<number1<<" and "<<number2<<" is "<<answer<<endl;
        }
        else
        {
            //display error message
            cout<<"Cannot add the numbers: "<<number1<<" and "<<number2<<endl;
        }
        
        if(subtract(c1, n1, d1, c2, n2, d2, answer, 100))
        {
            //display string with answer 579.456
            cout<<"The difference of the numbers "<<number1<<" and "<<number2<<" is "<<answer<<endl;
        }
        else
        {
            //display error message
            cout<<"Cannot subtract the numbers: "<<number1<<" and "<<number2<<endl;
        }
        
        if(multiply(c1, n1, d1, c2, n2, d2, answer, 100))
        {
            //display string with answer -56295.936
            cout<<"The product of the numbers "<<number1<<" and "<<number2<<" is "<<answer<<endl;
        }
        else
        {
            //display error message
            cout<<"Cannot multiply the numbers: "<<number1<<" and "<<number2<<endl;
        }
        
        if(divide(c1, n1, d1, c2, n2, d2, answer, 100))
        {
            //display string with answer -0.27073684210526
            cout<<"The quotient of the numbers "<<number1<<" and "<<number2<<" is "<<answer<<endl;
        }
        else
        {
            //display error message
            cout<<"Cannot divide the numbers: "<<number1<<" and "<<number2<<endl;
        }
    }
    else
    {
        //handle the error on input
        cout<<"Error converting the strings into numbers: "<<number1<<" and "<<number2<<endl;
    }
    
    return 0;
}
//--
bool validateString(char numString[]);
int convertStringToInt(char numString[], int& length);
int lengthOfCharacteristicString(char numString[]);
bool characteristic(char numString[], int& c)
{
    bool retVal = true;
	//validate string
	if (!validateString(numString))
	{
		retVal = false;
	}
	else
	{
		//make new string with only characteristic
		int length = lengthOfCharacteristicString(numString);
		//change new string into an integer
		c = convertStringToInt(numString, length);
		if (length == -1)
			retVal = false;
	}
	
	return retVal;
}
//--
bool mantissa(char numString[], int& numerator, int& denominator)
{
    //replace this code with your function
    return false;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //replace this code with your function
    return false;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //replace this code with your function
    return false;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //replace this code with your function
    return false;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //replace this code with your function
    return false;
}


//-----------Characteristic Helpers------------------
bool validateString(char numString[])
{
	bool retVal = true;
	int numStartIndex = 0;
	//loops through to find the first non-space character
	if (numString[0] == ' ')
	{
		while (numString[numStartIndex] == ' ')
		{
			numStartIndex += 1;
		}
	}
	//if first charcter is not a number make sure it is either a '+' or '-'
	if (numString[numStartIndex] != '+' && numString[numStartIndex] != '-' && (numString[numStartIndex] < '0' || numString[numStartIndex] > '9'))
	{
		retVal = false;
	}
	else
	{
		//make sure there is only one '.' in the string
		//make sure all the characters are numbers besides the '.'
		int dotCounter = 0;
		bool isLetter = false;
		int i = numStartIndex + 1;
		bool isSpace = false;
		while (numString[i] != '\0')
		{
			//while we haven't hit a space yet
			if (!isSpace)
			{
				//keeps track of the number of decimal points in the number
				if (numString[i] == '.')
				{
					dotCounter += 1;
					if(dotCounter > 1)
						break;
				}
				//when we hit a space switch the boolean to true
				else if (numString[i] == ' ')
				{
					isSpace = true;
				}
				//if we hit a letter or other symbol
				else if (numString[i] < '0' || numString[i] > '9')
				{
					isLetter = true;
					break;
				}
			}
			else //here we have hit a space and we want to make sure there isn't any numbers after the space(s) and before the \0
			{
				if (numString[i] != ' ')
				{
					//only switch to false if we get to something other than a space or \0 after the first space
					retVal = false;
					break;
				}
			}
			i += 1;
		}
		if (dotCounter > 1 || isLetter)
		{
			retVal = false;
		}
	}

	return retVal;
}

int convertStringToInt(char numString[], int& length)
{
	bool isNegative = false;
	int finalNum = 0;
	int powerOfTen = 1;
	for (int i = length - 1; i >= 0; i--)
	{
		if (numString[i] == '-')
		{
			isNegative = true;
		}
		else if (numString[i] != ' ' && numString[i] != '+')
		{
			//convert char digit into integer
			int valOfDigit = numString[i] - '0';
			int overflowCheck = finalNum + (valOfDigit * powerOfTen);
			if (overflowCheck < finalNum)
			{
				//overflow
				length = -1; //just a flag to signify an overflow
			}
			else
			{
				//multiply the digit by the power of ten and add it to the final answer
				finalNum += (valOfDigit * powerOfTen);
				//move to the next power of 10
				powerOfTen *= 10;
			}
		}
	}

	return (isNegative ? -finalNum : finalNum);
}

int lengthOfCharacteristicString(char numString[])
{
	int numCharacters = 0;
	//this finds the number of characters in the characteristic, this will be used later to control a loop
	while (numString[numCharacters] != '.' && numString[numCharacters] != '\0')
	{
		numCharacters += 1;
	}

	return numCharacters;
}