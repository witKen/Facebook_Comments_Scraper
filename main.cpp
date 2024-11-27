#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <regex>
#include "functions.h"
using namespace std;

float wpm_float = 300;

int main() {
    string texts;

    texts = getUserInput();
    if(texts.empty()){
        return 0;
    }
    vector<string> scrapedContents = scrapContents(texts);
    // vector<string> scrapedNames = getUserNames(scrapedContents);
    vector<string> scrapedComments = getComments(scrapedContents);

    // Print the extracted texts
    
    // for (const string& text : scrapedContents) {
    //     cout << "Extracted text: " << text << endl;
    // }

    // for (const string& text : scrapedNames) {
    //     cout << "Extracted text: " << text << endl;
    // }

    // for (const string& text : scrapedComments) {
    //     cout << "Extracted text: " << text << endl;
    // }

    // save(scrapedNames, scrapedComments);
    save(scrapedComments);
    
    return 0;
}