#pragma once
#include "Token.h"
#include <iostream>
#include <cctype>
#include <vector>
#include <iostream>


using namespace std;

class Scanner {

private:
    string input;
public:
    Scanner(const string& input) : input(input) { }
    vector<Token> tokenStorage;

    void scanToken(string input) {

        int lineVal = 1;
        while(input.size() > 0){
            while (isspace(input.at(0))) {
                if (input.at(0) == '\n'){
                    lineVal += 1;
                }
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
//                input.erase(0, 1);
//                if (input.empty()){
//                    Token e = Token(EOF_TYPE, "", lineVal);
//                    tokenStorage.push_back(e);
//                    return;
//                }
            }

            //Identifies the character and creates the appropriate token
            if (input.at(0) == ','){
                Token t = Token(COMMA, ",", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == '.'){
                Token t = Token(PERIOD, ".", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == '?'){
                Token t = Token(Q_MARK, "?", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == '('){
                Token t = Token(LEFT_PAREN, "(", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == ')'){
                Token t = Token(RIGHT_PAREN, ")", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if ((input.at(0) == ':') && (input.at(1) != '-')){
                Token t = Token(COLON, ":", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == '*'){
                Token t = Token(MULTIPLY, "*", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == '+'){
                Token t = Token(ADD, "+", lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if ((input.at(0) == ':') && (input.at(1) == '-')){
                Token t = Token(COLON_DASH, ":-", lineVal);
                input.erase(0, 2);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
            else if (isalpha(input.at(0))){
                string multiChar;
                while(isalnum(input.at(0))){
                    multiChar += input.at(0);
                    input.erase(0, 1);
                    if (input.empty()){
                        Token e = Token(EOF_TYPE, "", lineVal);
                        tokenStorage.push_back(e);
                        return;
                    }
                }
                if (multiChar == "Schemes"){
                    Token t = Token(SCHEMES, "Schemes", lineVal);
                    tokenStorage.push_back(t);
                }
                else if (multiChar == "Facts"){
                    Token t = Token(FACTS, "Facts", lineVal);
                    tokenStorage.push_back(t);
                }
                else if (multiChar == "Rules"){
                    Token t = Token(RULES, "Rules", lineVal);
                    tokenStorage.push_back(t);
                }
                else if (multiChar == "Queries"){
                    Token t = Token(QUERIES, "Queries", lineVal);
                    tokenStorage.push_back(t);
                }
                else{
                    Token t = Token(ID, multiChar, lineVal);
                    tokenStorage.push_back(t);
                }
            }
            else if (input.at(0) == '#') {
                string multiChar;
                while (input.at(0) != '\n') {
                    multiChar += input.at(0);
                    input.erase(0, 1);
                    if (input.empty()) {
                        Token e = Token(EOF_TYPE, "", lineVal);
                        tokenStorage.push_back(e);
                        return;
                    }
                }
                Token t = Token(COMMENT, multiChar, lineVal);
                tokenStorage.push_back(t);
            }
            else if (input.at(0) == '\'') {
                string multiChar;
                multiChar += input.at(0);
                input.erase(0, 1);
                if (input.empty()) {
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                int stringNewLineCounter = 0;
                while (input.at(0) != '\'') {
                    if (input.at(0) == '\n') {
                        lineVal += 1;
                        stringNewLineCounter += 1; //By subtracting the number of new lines inside the loops, we can attain the starting line of a string
                    }
                    multiChar += input.at(0);
                    input.erase(0, 1);
                    if (input.empty()) {
                        if (multiChar.back() != '\''){
                            Token t = Token(UNDEFINED, multiChar, lineVal - stringNewLineCounter);
                            tokenStorage.push_back(t);
                        }
                        Token e = Token(EOF_TYPE, "", lineVal);
                        tokenStorage.push_back(e);
                        return;
                    }
                }
                multiChar += input.at(0);
                input.erase(0, 1);
                if (input.empty()) {
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                Token t = Token(STRING, multiChar, lineVal - stringNewLineCounter);
                tokenStorage.push_back(t);
            }
            else{
                string undefToken;
                undefToken += input.at(0);
                Token t = Token(UNDEFINED, undefToken, lineVal);
                input.erase(0, 1);
                if (input.empty()){
                    Token e = Token(EOF_TYPE, "", lineVal);
                    tokenStorage.push_back(e);
                    return;
                }
                tokenStorage.push_back(t);
            }
        }
    
    }

};





