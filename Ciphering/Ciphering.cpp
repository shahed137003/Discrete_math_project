#include <iostream>
#include <string>
#define count_of_alphabet 19 //set variable count_of_alphabet to 19
using namespace std;
//function for Ciphering for Scottish Gaelic Alphabet
void Ciphering(string s,int a,int b)
{
    string capital_letters=" ABCDEFGHILMNOPRSTU"; //string of capital letters in the alphabet
    int x; //x is the index of the letter in alphabet
    string ciphered_msg="";//string that has the final ciphered message
    for(int i=0;i<s.length();i++)
    {
              for(int j=0;j<count_of_alphabet;j++)
             {
                 x=-1; //set x to -1 which is not a valid index
                if(s[i]==capital_letters[j]) //if letter belongs to Scottish Gaelic Alphabet
                {
                    x=j; //set x to the index of that letter in the Scottish Gaelic Alphabet
                    break;
                }

             }
                ciphered_msg+=capital_letters[(a*x+b)%count_of_alphabet];
    }
    cout << "Ciphered Message:" << ciphered_msg;
}
//function to check if a is coprime with the count of alphabet
void check_coprime(int a)
{
    int gcd = count_of_alphabet; //count_of_alphabet is set to 19
    int temp_a = a; //set temp_a to the value of a
    while (temp_a != 0)
    {
        int temp = temp_a;
        temp_a = gcd % temp_a;
        gcd = temp;
    }
    if (gcd != 1)
    {
        cout << "Invalid "<< a << ", a must be coprime with the alphabet size";
        exit(0);
    }
}
int main()
{
    string message;
    int a,b;
    cout << "Enter the message to be ciphered:" ;
    getline(cin,message);
    cout << "Enter a: ";
    cin >> a;
    check_coprime(a); //to check if a is coprime of alphabet size or not to be able to decipher it later
    cout << "Enter b: ";
    cin >> b;
    Ciphering(message,a,b);

}
