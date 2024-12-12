#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class ArraySizeException : public exception 
{
public:
    const char* what() const noexcept override 
    {
        return "Array size is not 4x4.";
    }
};

class ArrayDataException : public exception 
{
private:
    string message;
public:
    ArrayDataException(int row, int col) 
    {
        message = "Invalid data at (" + to_string(row) + ", " + to_string(col) + ").";
    }

    const char* what() const noexcept override 
    {
        return message.c_str();
    }
};

class ArrayValueCalculator
{
public:
    int doCalc(string array[4][4]) 
    {
        int sum = 0;
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 4; j++) 
            {
                try {
                    sum += stoi(array[i][j]);
                }
                catch (const invalid_argument&) 
                {
                    throw ArrayDataException(i, j);
                }
            }
        }
        return sum;
    }
};

int main() 
{
    string array[4][4] = 
    {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    ArrayValueCalculator calculator;

    try
    {
        int result = calculator.doCalc(array);
        cout << "Sum of all elements: " << result << endl;
    }
    catch (const ArraySizeException& e) 
    {
        cerr << e.what() << endl;
    }
    catch (const ArrayDataException& e) 
    {
        cerr << e.what() << endl;
    }
}
