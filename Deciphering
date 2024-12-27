#include <iostream>
#include <string>
using namespace std;

char arr[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// Function to find the modular inverse of 'a' under mod 27
int modInverse(int a) {
    for (int x = 1; x < 27; x++) {
        if ((a * x) % 27 == 1) {
            return x;
        }
    }
    return -1; // Return -1 if no modular inverse exists
}

// Function to decipher the text
string Affine_Decipher(string s, int a, int b) {
    string original_text = "";
    int a_inv = modInverse(a); // Find the modular inverse of 'a'

    if (a_inv == -1) {
        return "Error: Key 'a' is not coprime with 27";
    }

    for (int i = 0; i < s.size(); i++) {
        // Find the position of the current character in the array
        int y = -1;
        for (int j = 0; j < 27; j++) {
            if (s[i] == arr[j]) {
                y = j;
                break;
            }
        }

        // If character is found, decipher it
        if (y != -1) {
            int new_position = (a_inv * (y - b + 27)) % 27;
            original_text += arr[new_position];
        }
    }

    return original_text;
}

int main() {
    string s;
    cout << "Enter text to decrypt: ";
    getline(cin, s);

    int a, b;
    cout << "Enter keys: ";
    cin >> a >> b;

    string result = Affine_Decipher(s, a, b);
    cout << "original text: " << result << endl;

    return 0;
}
