#ifndef CODE_INC_EASY_MATH_H
#define CODE_INC_EASY_MATH_H

// Simple class to hold values and do basic maths
template <typename T>
class EasyMaths {
 public:
  // Class method prototypes
  T add();
  T mult();
  T sub();
  T div();

  EasyMaths(T _a, T _b, int* _counter);  // Constructor
  ~EasyMaths();  // Destructor

 private:
  T a;
  T b;
  int* counter;  // External counter (tracking num class isntances)
};

// Define class methods
template <typename T>
T EasyMaths<T>::add() {
  return a + b;
}

template <typename T>
T EasyMaths<T>::mult() {
  return a * b;
}

template <typename T>
T EasyMaths<T>::sub() {
  return a - b;
}

template <typename T>
T EasyMaths<T>::div() {
  return a / b;
}

template <typename T>
EasyMaths<T>::EasyMaths(T _a, T _b, int* _counter) {
  a = _a;
  b = _b;
  counter = _counter;
  *counter += 1;  // Increment external instance counter
}

template <typename T>
EasyMaths<T>::~EasyMaths() {
  *counter -= 1;  // Decrement external instance counter
}

#endif  // CODE_INC_EASY_MATH_H
