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

bool isdigit(char c) {
    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        return true;
    else
        return false;
}
bool isValidCharacter(char c) {
    if((c =='+'|| c =='-'|| c=='\0'|| c =='.' || c ==' ')|| isdigit(c)) {
        return true;
    }
    return false;
}

int mantissaDenominatorHelper(int numerator){
    int denominator = 10;
    //if it is less than 10 you know it will be x/10
    if(numerator < 10){
        return denominator;
    }
    
    while(numerator >= 10){
        numerator /= 10;
        denominator *= 10;
    }
    
    return denominator;
}
int mantissaNumeratorHelper(char numString[])
{
    int decimalPos = -1;
    int val = 0;
    
    //Find decimal point index
    for(int i = 0; numString[i] !='\0'; i++)
    {
        if(numString[i] == '.')
        {
            decimalPos = i;
            break;
        }
    }
    
    //0/10 if no decimal point
    if(decimalPos >= 0){
        
        for(int i = decimalPos + 1; numString[i] != '\0'; i++){
            if(!isValidCharacter(numString[i])) {
                return -1;
            }
            if((numString[i] == '+' || numString[i] == '-') && i != 0){
                if(numString[i-1] != ' ') {
                    //this means that the + or - sign was not at the beginning of number
                    return -1;
                }
            }
            if(numString[i] == '.' && i != decimalPos) {
                // there is a second decimal point
                return -1;
            }
            //Check for trailing spaces
            if(numString[i] == ' '){
                if(numString[i + 1] != '\0' && numString[i + 1] != ' '){
                    if(i >= decimalPos + 1) {
                        return -1;
                    }
                }
            }
            //Don't overflow
            //Shaves off the last digit and accounts for whehter the digit is anything 0-9
            if(val >= 0 && (val < ((INT_MAX - 9)/10)))
                val = (val * 10) + (numString[i] - '0');
            else
            {
                cout << "THERE IS AN OVERFLOW IN THE NUMERATOR!" << endl;
                break;
            }
        }
    }
    
    return val;
}

bool mantissa(char numString[], int& numerator, int& denominator){
    //Set numerator and denominator
    numerator = mantissaNumeratorHelper(numString);
    if(numerator == -1){
        return false;
    }
    denominator = mantissaDenominatorHelper(numerator);
    
    return true;
}

//--
void add_reverseArrays(char* result, char* reverse, int result_length)
{
	//reverses the reverse array and stores the values in result
	for (int i = 0; i < result_length; i++)
	{
		result[i] = reverse[result_length - 1 - i];
	}
	result[result_length + 1] = '\0';
}
bool add_equalizeDenominators(int& n1, int& d1, int& n2, int& d2, int len)
{
	//Function to change both the numerator and denominator so that
	//both denominators are the same and we can add the numerators together
	//to get the decimal result
	if (d1 % 10 == 0 && d2 % 10 == 0)
	{
		//test for which numerator and denominator we should change
		bool d1IsBigger = d1 > d2 ? true : false; //ternary operator
		bool d2IsBigger = d2 > d1 ? true : false;
		while (d1IsBigger)
		{
			//change d2
			d2 *= 10;
			n2 *= 10;
			//see if theyre the same size
			d1IsBigger = d1 > d2 ? true : false;
		}
		while (d2IsBigger)
		{
			//change d1
			d1 *= 10;
			n1 *= 10;
			//see if they are same size
			d2IsBigger = d2 > d1 ? true : false;
		}
		return true;
	}
	else
	{
		//if d1 and d2 are not divisible by 10, return false
		return false;
	}
}
void add_putNumbersIntoResultArray(int & characteristic, int& numerator, int& denominator, char result[], int& len)
{
	char* reverse = new char[len];
	int temp_characteristic_for_finding_characteristic_length = characteristic;
	int result_length = 0;
	int numerator_holder = 0;
	//First we put our decimals into the reverse array
	while (denominator >= 10)
	{
		denominator /= 10;
		numerator_holder = numerator % 10;
		numerator /= 10;
		//were using reverse b/c numerator % 10 gives us the last digit

		reverse[result_length] = numerator_holder + 48;
		result_length++;

		if (result_length > len - 1)
		{
			//if we overstep the char array's limits, then we store what we can and truncate
			//the rest
			add_reverseArrays(result, reverse, result_length);
			return;
		}
	}
	//inputs the decimal point
	reverse[result_length] = '.';
	result_length++;

	if (result_length > len - 1)
	{
		add_reverseArrays(result, reverse, result_length);
		return;
	}
	//inputs the characteritic to the result array
	while (characteristic > 0)
	{
		reverse[result_length] = 48 + characteristic % 10;
		result_length++;
		if (result_length > len - 1)
		{
			add_reverseArrays(result, reverse, result_length);
			return;
		}
		characteristic /= 10;
	}
	add_reverseArrays(result, reverse, result_length);
	delete[] reverse;
}
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	int characteristic = c1 + c2;

	bool return_from_parse_fractions = add_equalizeDenominators(n1, d1, n2, d2, len);
	//if something was messed up, return false for the function
	if (!return_from_parse_fractions)
		return false;

	int numerator = n1 + n2;
	//if the numerators when added together are greater than the denominator, then
	//we can add one to characteristic
	if (numerator / d1 > 0)
	{
		characteristic++;
		numerator -= d1;
	}
	add_putNumbersIntoResultArray(characteristic, numerator, d1, result, len);
	return true;
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