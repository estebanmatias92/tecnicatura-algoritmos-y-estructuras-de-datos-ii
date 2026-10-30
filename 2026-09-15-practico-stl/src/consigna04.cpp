#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
using namespace std;

string clean_word(string w) {
    string r;
    for (char c : w) {
        if (isalpha(c) || isdigit(c)) r += tolower(c);
    }
    return r;
}

int main() {
    unordered_map<string, int> freq;
    string frase = "Existen dos tipos de lenguajes de programación: por un lado, aquellos de los que la gente se queja todo el rato; por otro, los que nadie utiliza.";
    // Reemplazar signos de puntuación por espacios para tokenizar fácilmente
    for (char& c : frase) {
        if (ispunct(c) && c != '\'') c = ' ';
    }
    istringstream iss(frase);
    string word;
    while (iss >> word) {
        string w = clean_word(word);
        if (!w.empty()) freq[w]++;
    }
    for (auto p : freq) {
        cout << p.first << ":" << p.second << " ";
    }
    cout << endl;
    return 0;
}
