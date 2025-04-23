/*
Author: Steven Gobran
Date: 04/23/2025
Lab Purpose: converts a number between three numbering systems: binary, decimal, and hexadecimal.

A.I. Disclaimer: All work for this assignment was completed by myself 
and entirely without the use of artificial intelligence tools such as ChatGPT, MS Copilot, other LLMs, etc.
*/

#include <iostream>
#include <string>
#include <limits>
#include <bitset>
#include <iomanip>

using namespace std;

// Function prototypes
int binaryToDecimal(const string& binary);
string decimalToBinary(int decimal);
string decimalToHexadecimal(int decimal);
bool isValidBinary(const string& binary);
bool isValidHexadecimal(const string& hex);
bool isValidDecimal(const string& decimal);

int main() {
    int choice;
    string input;
    char continueConversion;
    
    // Main program loop
    do {
        // Display menu
        cout << "--------------------------------\n";
        cout << "Number System Converter\n";
        cout << "--------------------------------\n";
        cout << "Choose input format:\n";
        cout << "1. Binary\n";
        cout << "2. Decimal\n";
        cout << "3. Hexadecimal\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        // Process user choice
        if (choice == 1) {
            cout << "Please enter binary number: ";
            cin >> input;
            
            // Validate binary input
            while (!isValidBinary(input)) {
                cout << "Invalid binary input. Please enter a valid binary number: ";
                cin >> input;
            }
            
            // Convert and display results
            int decimal = binaryToDecimal(input);
            string hex = decimalToHexadecimal(decimal);
            cout << "\nConversion Results:\n";
            cout << "--------------------------------\n";
            cout << "Binary:      " << input << endl;
            cout << "Decimal:     " << decimal << endl;
            cout << "Hexadecimal: " << hex << endl;
        } 
        else if (choice == 2) {
            // Handle decimal input
            cout << "Please enter decimal number: ";
            cin >> input;
            
            // Check for negative numbers and validate
            bool isNegative = false;
            string checkInput = input;
            
            if (!input.empty() && input[0] == '-') {
                isNegative = true;
                checkInput = input.substr(1); // Remove the negative sign for validation
            }
            
            // Validate decimal input
            while (!isValidDecimal(checkInput)) {
                cout << "Invalid decimal input. Please enter a valid decimal number: ";
                cin >> input;
                isNegative = false;
                checkInput = input;
                if (!input.empty() && input[0] == '-') {
                    isNegative = true;
                    checkInput = input.substr(1);
                }
            }
            
            // Convert decimal input
            int decimal = stoi(input);
            
            // Use 8-bit representation for negative numbers
            string binary, hex;
            
            if (decimal < 0) {
                // For negative numbers, use two's complement representation (8-bit)
                bitset<8> bits(decimal);
                binary = bits.to_string();
                
                // For hexadecimal, use the convention that negative numbers appear as 8-bit two's complement
                unsigned int unsignedVal = static_cast<unsigned char>(decimal); // Cast to 8-bit
                stringstream ss;
                ss << uppercase << std::hex << unsignedVal;
                hex = ss.str();
            } else {
                // Convert positive numbers normally
                binary = decimalToBinary(decimal);
                hex = decimalToHexadecimal(decimal);
            }
            
            // Display results
            cout << "\nConversion Results:\n";
            cout << "--------------------------------\n";
            cout << "Binary:      " << binary << endl;
            cout << "Decimal:     " << decimal << endl;
            cout << "Hexadecimal: " << hex << endl;
        } 
        else if (choice == 3) {
            // Handle hexadecimal input
            cout << "Please enter hexadecimal number: ";
            cin >> input;
            
            // Convert hex input to uppercase 
            string originalInput = input;
            for (char& c : input) {
                c = (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
            }
            
            // Check for negative hexadecimal input
            bool isNegative = false;
            string checkInput = input;
            
            if (!input.empty() && input[0] == '-') {
                isNegative = true;
                checkInput = input.substr(1); // Remove the negative sign for validation
                originalInput = originalInput.substr(1); 
            }
            
            // Validate hexadecimal input
            while (!isValidHexadecimal(checkInput)) {
                cout << "Invalid hexadecimal input. Please enter a valid hexadecimal number: ";
                cin >> input;
                originalInput = input;
                isNegative = false;
                checkInput = input;
                if (!input.empty() && input[0] == '-') {
                    isNegative = true;
                    checkInput = input.substr(1);
                    originalInput = originalInput.substr(1);
                }
                for (char& c : checkInput) {
                    c = (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
                }
                for (char& c : originalInput) {
                    c = (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
                }
            }
            
            // Convert hexadecimal to decimal
            int decimal;
            if (isNegative) {
                // For negative hex input, interpret as positive, then negate
                decimal = -stoi(checkInput, nullptr, 16);
            } else {
                decimal = stoi(checkInput, nullptr, 16);
            }
            
            // Convert decimal to binary
            string binary;
            if (decimal < 0) {
                // For negative values, use 8-bit two's complement
                bitset<8> bits(decimal);
                binary = bits.to_string();
            } else {
                binary = decimalToBinary(decimal);
            }
            
            // Display results
            cout << "\nConversion Results:\n";
            cout << "--------------------------------\n";
            cout << "Binary:      " << binary << endl;
            cout << "Decimal:     " << decimal << endl;
            cout << "Hexadecimal: " << (isNegative ? "-" : "") << originalInput << endl;
        }
        else {
            // Handle invalid choice
            cout << "Invalid choice, please try again.\n";
            continue;
        }
        
        // Prompt user to continue or exit
        cout << "\nDo you want to convert another number? (y/n): ";
        cin >> continueConversion;
        continueConversion = tolower(continueConversion);
        
    } while (continueConversion == 'y'); // Loop continues if user enters 'y'
    
    // Display goodbye message
    cout << "\nThank you for using the converter!\n";
    cout << "--------------------------------\n";

    return 0;
}

// Function to convert Binary to Decimal
int binaryToDecimal(const string& binary) {
    int decimal = 0;
    int base = 1;
    
    // Process each binary digit from right to left
    for (int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

// Function to convert Decimal to Binary
string decimalToBinary(int decimal) {
    string binary = "";
    
    // Handle special case for 0
    if (decimal == 0) {
        return "0";
    }
    
    // Convert decimal to binary by repeatedly dividing by 2
    while (decimal > 0) {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal /= 2;
    }
    return binary;
}

// Function to convert Decimal to Hexadecimal
string decimalToHexadecimal(int decimal) {
    string hex = "";
    const string hexChars = "0123456789ABCDEF";
    
    // Handle special case for 0
    if (decimal == 0) {
        return "0";
    }
    
    // Convert decimal to hexadecimal by repeatedly dividing by 16
    while (decimal > 0) {
        hex = hexChars[decimal % 16] + hex;
        decimal /= 16;
    }
    return hex;
}

// Function to check if the input is a valid binary number
bool isValidBinary(const string& binary) {
    // Check each character to ensure it's either 0 or 1
    for (char c : binary) {
        if (c != '0' && c != '1') {
            return false;
        }
    }
    return true;
}

// Function to check if the input is a valid hexadecimal number
bool isValidHexadecimal(const string& hex) {
    // Check each character to ensure it's a valid hex digit (0-9, A-F)
    for (char c : hex) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
            return false;
        }
    }
    return true;
}

// Function to check if the input is a valid decimal number
bool isValidDecimal(const string& decimal) {
    // Check each character to ensure it's a digit (0-9)
    for (char c : decimal) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}