#pragma once
#include <iostream>

class Animal {
   private:
    float hunger;

   public:
    Animal(float initial_hunger);
    void Eat(float sustenance);
    float GetHunger();
    void Move();
    virtual void Speak() = 0;
};
