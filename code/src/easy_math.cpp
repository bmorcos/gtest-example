#include "code/inc/easy_math.h"

// Define class methods
float EasyMaths::add() { return a + b; }

float EasyMaths::mult() { return a * b; }

float EasyMaths::sub() { return a - b; }

float EasyMaths::div() { return a / b; }

EasyMaths::EasyMaths(float _a, float _b, int* _counter) {
  a = _a;
  b = _b;
  counter = _counter;
  *counter += 1;  // Increment external instance counter
}

EasyMaths::~EasyMaths() {
  *counter -= 1;  // Decrement external instance counter
}
