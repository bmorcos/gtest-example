#ifndef CODE_INC_EASY_MATH_H_
#define CODE_INC_EASY_MATH_H_

// Simple class to hold values and do basic maths
class EasyMaths {
 public:
  // Class method prototypes
  float add();
  float mult();
  float sub();
  float div();

  EasyMaths(float _a, float _b, int* _counter);  // Constructor
  ~EasyMaths();                                  // Destructor

 private:
  float a;
  float b;
  int* counter;  // External counter (tracking num class isntances)
};

#endif  // CODE_INC_EASY_MATH_H_
