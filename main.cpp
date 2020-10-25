#include <iostream>

#include "scanner.h"

using namespace std;


int main()
{
    Scanner* numericScanner = new Scanner;

    double finalValue;
    string inputValue;

     cout << "Introduce el  número que deseas traducir" << "\n";

     getline(cin, inputValue);

     finalValue = numericScanner->convertLettersToNumbers(inputValue);

     cout << "Final Value " << finalValue << endl;


    return 0;
}

