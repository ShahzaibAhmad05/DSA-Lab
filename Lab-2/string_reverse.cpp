#include <iostream>
#include <cstring>      // for strlen

using namespace std;

int main()
{
    // Take the max size of the string as input
    string maxSizeStr;
    cout << "Enter the maximum length of the string: ";
    cin >> maxSizeStr;

    // Check if the input is a number
    for (int i = 0; i < maxSizeStr.length(); i++)
    {
        if (!isdigit(maxSizeStr[i]))
        {
            cout << "Invalid input. Please enter a number." << endl;
            return 0;
        }
    }
    int maxSize = stoi(maxSizeStr);

    // Clear the input buffer (or the next inputs will take it)
    cin.ignore();

    // Declare the string dynamically
    char* inputStr = new char[maxSize + 1];

    // Get the string as input using getline
    cout << "Enter the string: ";
    cin.getline(inputStr, maxSize + 1);

    // Calculate the length of the string
    int lenStr = strlen(inputStr);  // Can also be done using a while loop

    // Use a loop to reverse the string
    for (int i = 0; i < lenStr / 2; i++)
    {
        char temp = inputStr[i];    // Store the ith value
        inputStr[i] = inputStr[lenStr - i - 1];     // Assign the last - i value to ith
        inputStr[lenStr - i - 1] = temp;    // Assign temp to the last - i value
    }

    cout << "The reversed string is: " << inputStr << endl;

    delete[] inputStr;      // Free UP THE MEMORY AGAIN!
    return 0;
}
