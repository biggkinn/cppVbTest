#ifndef SCANNER_H
#define SCANNER_H

#include <bits/stdc++.h>

using namespace std;

class Scanner
{
public:
    Scanner();

    double convertLettersToNumbers(string inputString);


private:
    map < string, int> numberDictionary;

    void init();
    double extractValue(vector<int>& inputVectorRawNumbers);

    vector<string> splitStringInWords(string inputString); // <<-- Privada o publica!!!
    vector<int> translateToRawNumbers(vector<string>& inputVectorString); // <<-- Privada o publica!!!


};

#endif // SCANNER_H
