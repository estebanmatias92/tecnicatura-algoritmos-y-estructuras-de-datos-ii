#include <iostream>
#include "Car.h"

const int ACCELERATION_FACTOR = 10;
const int BRAKING_FACTOR = 30;

Car::Car() {
  speed = 10;
  
}

void Car::accelerate(int intensity) {
  speed = speed + (intensity);
}

int Car::brake(int intensity) {
  speed = speed - (intensity);
  return speed;
}

int Car::getSpeed(){
   int velocidad = speed ;
    return velocidad;
    //std::cout << speed << std::endl;
}