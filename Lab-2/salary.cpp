#include <iostream>
using namespace std;

int main()
{
    const int size = 20;
    int *salArray = new int[size];

    // Input salaries
    for (int i = 0; i < size; i++)
    {
        cout << "Enter Salary for employee " << (i + 1) << ": ";

        string temp;
        cin >> temp;

        // Check if input is a number
        bool isNumber = true;
        for (int j = 0; j < temp.length(); j++)
        {
            if (!isdigit(temp[j]))
            {
                isNumber = false;
                break;
            }
        }
        if (isNumber)
        {
            salArray[i] = stoi(temp);
        }
        else
        {
            cout << "Invalid input. Please enter a number." << endl;
            i--;
        }
    }

    // Apply increment formula
    for (int i = 0; i < size; i++)
    {
        salArray[i] = salArray[i] + salArray[i] / (i + 1);
    }

    // Display updated salaries
    cout << "\nUpdated Salaries: ";
    for (int i = 0; i < size; i++)
    {
        cout << salArray[i] << " ";
    }
    cout << endl;

    delete[] salArray;

    return 0;
}
