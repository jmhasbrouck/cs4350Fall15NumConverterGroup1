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
bool characteristic(char numString[], int& c)
{
    //replace this code with your function
    return false;
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