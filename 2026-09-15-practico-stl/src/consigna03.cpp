#include <map>
#include <iostream>
using namespace std;

int main() {
    // 1. Contenedor vacío
    map<int, string> Map1, Map2;
    // 2. Insertar elementos en orden aleatorio
    Map1.insert({3, "tres"});
    Map1.insert({5, "cinco"});
    // 3. Imprimir Map1
    for (auto p : Map1) cout << p.first << ":" << p.second << " ";
    cout << endl;
    // 4. Asignar a Map2
    Map2 = Map1;
    // 5. Imprimir Map2
    for (auto p : Map2) cout << p.first << ":" << p.second << " ";
    cout << endl;
    // 6. Eliminar todos hasta clave = 3 en Map2
    Map2.erase(Map2.begin(), Map2.find(3));
    // 7. Eliminar clave = 4 (si existe)
    Map2.erase(4);
    // 8. lower_bound / upper_bound para clave = 5 en Map1
    auto lb = Map1.lower_bound(5);
    auto ub = Map1.upper_bound(5);
    if (lb != Map1.end()) cout << "lb=" << lb->first << endl;
    if (ub != Map1.end()) cout << "ub=" << ub->first << endl;
    return 0;
}
