#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    // 1. Defina un vector<int>
    vector<int> v;
    // 2. Inserte dos elementos
    v.push_back(10);
    v.push_back(20);
    // 3. Imprima con bucle basado en rangos
    for (int x : v) cout << x << " ";
    cout << endl;
    // 4. Borra el segundo elemento
    v.erase(v.begin() + 1);
    // 5. Imprima
    for (int x : v) cout << x << " ";
    cout << endl;
    // 6. Borra rango de 3 elementos desde inicio
    v.erase(v.begin(), v.begin() + min(3, (int)v.size()));
    // 7. Imprima
    for (int x : v) cout << x << " ";
    cout << endl;
    // 8. Busque con std::find y elimine si encontrado
    auto it = find(v.begin(), v.end(), 10);
    if (it != v.end()) v.erase(it);
    // 9. Imprima final
    for (int x : v) cout << x << " ";
    cout << endl;
    return 0;
}
