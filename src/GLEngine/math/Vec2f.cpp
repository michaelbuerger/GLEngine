#include "GLEngine/math/Vec2f.hpp"
#include <cmath>

namespace GLEngine { namespace math {
  Vec2f::Vec2f()
  {
    this->x = 0;
    this->y = 0;
  }
  Vec2f::Vec2f(const float& x, const float& y)
  {
    this->x = x;
    this->y = y;
  }
  Vec2f::Vec2f(const Vec2f& vec)
  {
    this->x = vec.x;
    this->y = vec.y;
  }

  Vec2f Vec2f::add(const Vec2f& vec2) /* Add vec2 to vec1, return result | vec1 += vec2 */
  {
    this->x += vec2.x;
    this->y += vec2.y;

    return *this;
  }
  Vec2f Vec2f::Add(const Vec2f& vec1, const Vec2f& vec2) /* Return addition of vec1 and vec2 | (vec1 + vec2) */
  {
    Vec2f vec(vec1.x + vec2.x, vec1.y + vec2.y);

    return vec;
  }

  Vec2f Vec2f::sub(const Vec2f& vec2) /* Sub vec2 from vec1, return result | vec1 -= vec2 */
  {
    this->x -= vec2.x;
    this->y -= vec2.y;

    return *this;
  }
  Vec2f Vec2f::Sub(const Vec2f& vec1, const Vec2f& vec2) /* Return subtraction of vec2 from vec1 | (vec1 - vec2) */
  {
    Vec2f vec(vec1.x - vec2.x, vec1.y - vec2.y);

    return vec;
  }

  Vec2f Vec2f::mult(const Vec2f& vec2) /* Mult vec1 by vec2, return result | vec1 *= vec2 */
  {
    this->x *= vec2.x;
    this->y *= vec2.y;

    return *this;
  }
  Vec2f Vec2f::Mult(const Vec2f& vec1, const Vec2f& vec2) /* Return product of vec1 and vec2 | (vec1 * vec2) */
  {
    Vec2f vec(vec1.x * vec2.x, vec1.y * vec2.y);

    return vec;
  }
  Vec2f Vec2f::mult(const float& scalar) /* Mult vec1 by scalar, return result | vec1 *= scalar */
  {
    this->x *= scalar;
    this->y *= scalar;

    return *this;
  }
  Vec2f Vec2f::Mult(const Vec2f& vec1, const float& scalar) /* Return product of vec1 and scalar | (vec1 * scalar) */
  {
    Vec2f vec(vec1.x * scalar, vec1.y * scalar);

    return vec;
  }

  Vec2f Vec2f::div(const Vec2f& vec2) /* Div vec1 by vec2, return result | vec1 /= vec2 */
  {
    this->x /= vec2.x;
    this->y /= vec2.y;

    return *this;
  }
  Vec2f Vec2f::Div(const Vec2f& vec1, const Vec2f& vec2) /* Return division of vec1 by vec2 | (vec1 / vec2) */
  {
    Vec2f vec(vec1.x / vec2.x, vec1.y / vec2.y);

    return vec;
  }

  //static float Vec2f::Dot(const Vec2f& forward, const Vec2f& other); /* Dot product of forward to other */

  float Vec2f::getMagnitude() /* Calculate magnititude of vector */
  {
    return std::sqrt((this->x*this->x)+(this->y*this->y));
  }

  void Vec2f::normalize() /* Normalize this */
  {
    this->mult(1/this->getMagnitude()); // Divide each element by magnitude
  }
  Vec2f Vec2f::Normalized() /* Return normalized version of this */
  {
    Vec2f normalizedVector = *this;

    normalizedVector.normalize();

    return normalizedVector;
  }
}}
