#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "GLEngine/math/Vec2f.hpp"
#include "GLEngine/testing/testing.hpp" // Accidently deleted all the testing stuff lol

/* Return types: Return by reference, standard return */
void AdditionReturnByRef(const float& a, const float& b, float& ret)
{
  ret = a + b;
}

float AdditionReturn(const float& a, const float& b)
{
  return a + b;
}

using namespace GLEngine;
using namespace math;
using namespace testing;

int main()
{
  std::vector<Vec2f> in1{Vec2f(0, 1), Vec2f(2, 3), Vec2f(4, 5)};
  std::vector<Vec2f> in2{Vec2f(1, 2), Vec2f(3, 4), Vec2f(5, 6)};
  std::vector<Vec2f> out1{Vec2f(1, 3), Vec2f(5, 7), Vec2f(9, 11)};

  TestResult testResult = TestFunc_3Axis_StandardReturn(&Vec2f::Add, in1, in2, out1, false);

  std::cout << "Result of test: " << testResult.passed << std::endl;
  std::cout << "Failure indices: " << testResult.failureIndicesStr << std::endl;

  return 0;
}
