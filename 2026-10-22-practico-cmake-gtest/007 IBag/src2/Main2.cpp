#include<iostream>
#include "../library/Myfunctions.h"
#include "../library/Car.h"
using namespace std;


int main(){
cout << "corriendo el Programa Principal Version *** 2 Jose *** " << endl; 
cout << "la suma es: " << sum(10,10) << endl;
cout << "la resta es: " << substract(10,10) << endl;
Car *myCar = new Car();
cout << "La velocidad de Inicio es:" << myCar->getSpeed() << endl ;
myCar->accelerate(30);
cout << "La velocidad despues de Acelerar es:" << myCar->getSpeed() << endl ;
myCar->brake(10);
cout << "La velocidad despues de Frenar es:" << myCar->getSpeed() << endl ;
cout << "Soy la version 2.0" << endl ;
return 0;
}