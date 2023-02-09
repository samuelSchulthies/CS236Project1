#include "Token.h"
#include "Scanner.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string fileName = argv[1];
    string datalogInput = "";
    Scanner datalogString = Scanner(datalogInput);

    ifstream input(fileName);
    if(!input.is_open()) {
        cout << fileName << " not found or could not be opened" << endl;
        return 1;
    }
    while(!input.eof()){
        string datalogAdder;
        getline(input, datalogAdder);
        datalogInput += datalogAdder + "\n";
    }

    datalogString.scanToken(datalogInput);
    for (unsigned int i = 0; i < datalogString.tokenStorage.size(); ++i) {
        cout << datalogString.tokenStorage.at(i).toString() << endl;
    }
    return 0;
}