#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <windows.h> 

using namespace std;

string cleanWord(string word) {
    string cleaned = "";
    for (char c : word) {
        if (ispunct((unsigned char)c) && c != '.') continue;
        cleaned += c;
    }
    return cleaned;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input.txt!" << endl;
        return 1;
    }

    string sentence;
    while (getline(inputFile, sentence)) {
        if (sentence.empty()) continue;

        bool hasDot = (!sentence.empty() && sentence.back() == '.');
        if (hasDot) sentence.pop_back();

        stringstream ss(sentence);
        string word;
        vector<string> words;

        while (ss >> word) {
            words.push_back(cleanWord(word));
        }

        sort(words.begin(), words.end());

        for (size_t i = 0; i < words.size(); ++i) {
            outputFile << words[i] << (i == words.size() - 1 ? "" : " ");
        }

        if (hasDot) outputFile << ".";
        outputFile << endl;
    }

    cout << "Обробка завершена. Результат збережено в output.txt" << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}