#include "scanner.h"



Scanner::Scanner()
{
    init();
}


void Scanner::init()
{
   /* Init de map dictionary */
   numberDictionary["one"]      = 1;
   numberDictionary["two"]      = 2;
   numberDictionary["three"]    = 3;
   numberDictionary["four"]     = 4;
   numberDictionary["five"]     = 5;
   numberDictionary["six"]      = 6;
   numberDictionary["seven"]    = 7;
   numberDictionary["eight"]    = 8;
   numberDictionary["nine"]     = 9;
   numberDictionary["ten"]      = 10;

   numberDictionary["eleven"]   = 11;
   numberDictionary["twelve"]   = 12;
   numberDictionary["thirteen"] = 13;
   numberDictionary["fourteen"] = 14;
   numberDictionary["fifteen"]  = 15;
   numberDictionary["sixteen"]  = 16;
   numberDictionary["seventeen"]= 17;
   numberDictionary["eighteen"] = 18;
   numberDictionary["ninteen"]  = 19;

   numberDictionary["twenty"]   = 20;
   numberDictionary["thirty"]   = 30;
   numberDictionary["forty"]    = 40;
   numberDictionary["fifty"]    = 50;
   numberDictionary["sixty"]    = 60;
   numberDictionary["seventy"]  = 70;
   numberDictionary["eighty"]   = 80;
   numberDictionary["ninety"]   = 90;

   numberDictionary["hundred"]  = 100;
   numberDictionary["thousand"] = 1000;
   numberDictionary["million"]  = 1000000;
   numberDictionary["billion"]  = 1000000000;

}

vector<string> Scanner::splitStringInWords(string inputString)  // <-- He creado esta función por no usar librerías como Boost o QT donde puedes partir una cadena por un carácter
{
    string::size_type blankPos, stringIterator = 0;
    string subStringAux;
    vector<string> vOutput;

    while(stringIterator < inputString.size())
    {
        /* Comprobamos que el primero no se blanco*/
        if(inputString.at(stringIterator)!=' ')
        {
            /*Buscamos el primer blanco*/
            blankPos = inputString.find(" ", stringIterator);

            if(blankPos == string::npos)
            {
                /* Sino hay blanco cogemmos hasta el final de la cadena */
                blankPos = inputString.size();
            }

            /*Extraemos la cadena*/
            subStringAux = inputString.substr(stringIterator, blankPos - stringIterator);

            /*Almacenamos la subcadena en el vector de resultado*/
            vOutput.push_back(subStringAux);

            /*Actualizamos el contador*/
            stringIterator = blankPos+1;
        }
        else
        {
            /* Pasamos al siguiente*/
            stringIterator++;
        }
    }

    return vOutput;
}

//  Que pasa si no puedo transformar algún número ¿?¿??¿?¿?¿? Lo miro en la siguiente función¿?¿??¿?
vector<int> Scanner::translateToRawNumbers(vector<string>& inputVectorString)
{
    vector<int> vRawNumbersOutput;
    std::map < string, int>::iterator mapIterator;         //Lo hacemos todo así?????????? con el std::  ?????

    for (size_t i=0; i<inputVectorString.size(); i++)
    {
        mapIterator = numberDictionary.find(inputVectorString.at(i));
        /* Si podemos traducirlo a numero lo añadimos, los "and" se saltan*/
        if(mapIterator != numberDictionary.end())
        {
            vRawNumbersOutput.push_back(mapIterator->second);
        }
    }

    return vRawNumbersOutput;
}


double Scanner::extractValue(vector<int> &inputVectorRawNumbers)
{
    double dTempMult       = 0;
    double dAcumulated     = 0;

    int decenaTemp      = 0;
    vector<double>  tempValues;

    vector<int>::size_type i;

    for(i=0; i<inputVectorRawNumbers.size(); i++)
    {
        if(inputVectorRawNumbers.at(i) <= 9 ) // [0,9]
        {
            if(decenaTemp > 0)
            {
                dTempMult += inputVectorRawNumbers.at(i) + decenaTemp;
                decenaTemp = 0;
            }
            else
            {
                dTempMult += inputVectorRawNumbers.at(i);
            }
        }
        else if(inputVectorRawNumbers.at(i) <= 19 ) // [10,19]
        {
            dTempMult += inputVectorRawNumbers.at(i);
        }
        else if (inputVectorRawNumbers.at(i) <= 99 ) //[20,99]
        {
            decenaTemp = inputVectorRawNumbers.at(i);
        }
        else if (inputVectorRawNumbers.at(i) == 100 ) // 100
        {
            dTempMult *= inputVectorRawNumbers.at(i);
        }
        else if (inputVectorRawNumbers.at(i) > 100 ) // 1000
        {
            dTempMult *= inputVectorRawNumbers.at(i);
            tempValues.push_back(dTempMult);
            dTempMult = decenaTemp = 0;
        }
    }

    /* Sumo todas partes que hemos ido calculando*/
    for(vector<double>::size_type j=0; j<tempValues.size();j++)
    {
        dAcumulated += tempValues.at(j);
    }

    /*Sumo las decenas que quedasen por calcular, puede que sea cero*/
    dAcumulated += decenaTemp;

    /* Sumo lo que tenga en el temporal pendiente de multiplicar por millares, millones, etc*/
    dAcumulated += dTempMult;

    return dAcumulated;
}


double Scanner::convertLettersToNumbers(string inputString)
{
    vector<string> vWordsVector;
    vector<int>  vRawNumbers;
    double result;

    vWordsVector = splitStringInWords(inputString);

    vRawNumbers = translateToRawNumbers(vWordsVector);

    result = extractValue(vRawNumbers);

    return result;

}
