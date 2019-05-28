#include "GLEngine/math/Vec4f.hpp"
#include <cmath>

namespace GLEngine { namespace math {
  Vec4f::Vec4f()
  {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
  }
  Vec4f::Vec4f(const float& x, const float& y, const float& z, const float& w)
  {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
  Vec4f::Vec4f(const Vec4f& vec)
  {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = vec.w;
  }

  Vec4f Vec4f::add(const Vec4f& vec2) /* Add vec2 to vec1, return result | vec1 += vec2 */
  {
    this->x += vec2.x;
    this->y += vec2.y;
    this->z += vec2.z;
    this->w += vec2.w;

    return *this;
  }
  Vec4f Vec4f::Add(const Vec4f& vec1, const Vec4f& vec2) /* Return addition of vec1 and vec2 | (vec1 + vec2) */
  {
    Vec4f vec(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);

    return vec;
  }

  Vec4f Vec4f::sub(const Vec4f& vec2) /* Sub vec2 from vec1, return result | vec1 -= vec2 */
  {
    this->x -= vec2.x;
    this->y -= vec2.y;
    this->z -= vec2.z;
    this->w -= vec2.w;

    return *this;
  }
  Vec4f Vec4f::Sub(const Vec4f& vec1, const Vec4f& vec2) /* Return subtraction of vec2 from vec1 | (vec1 - vec2) */
  {
    Vec4f vec(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);

    return vec;
  }

  Vec4f Vec4f::mult(const Vec4f& vec2) /* Mult vec1 by vec2, return result | vec1 *= vec2 */
  {
    this->x *= vec2.x;
    this->y *= vec2.y;
    this->z *= vec2.z;
    this->w *= vec2.w;

    return *this;
  }
  Vec4f Vec4f::Mult(const Vec4f& vec1, const Vec4f& vec2) /* Return product of vec1 and vec2 | (vec1 * vec2) */
  {
    Vec4f vec(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);

    return vec;
  }
  Vec4f Vec4f::mult(const float& scalar) /* Mult vec1 by scalar, return result | vec1 *= scalar */
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;

    return *this;
  }
  Vec4f Vec4f::Mult(const Vec4f& vec1, const float& scalar) /* Return product of vec1 and scalar | (vec1 * scalar) */
  {
    Vec4f vec(vec1.x * scalar, vec1.y * scalar, vec1.z * scalar, vec1.w * scalar);

    return vec;
  }

  Vec4f Vec4f::div(const Vec4f& vec2) /* Div vec1 by vec2, return result | vec1 /= vec2 */
  {
    this->x /= vec2.x;
    this->y /= vec2.y;
    this->z /= vec2.z;
    this->w /= vec2.w;

    return *this;
  }
  Vec4f Vec4f::Div(const Vec4f& vec1, const Vec4f& vec2) /* Return division of vec1 by vec2 | (vec1 / vec2) */
  {
    Vec4f vec(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);

    return vec;
  }

  //static float Vec4f::Dot(const Vec4f& forward, const Vec4f& other); /* Dot product of forward to other */

  float Vec4f::getMagnitude() /* Calculate magnititude of vector */
  {
    return std::sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z) + (this->w*this->w));
  }

  void Vec4f::normalize() /* Normalize this */
  {
    this->mult(1/this->getMagnitude());
  }
  Vec4f Vec4f::Normalized() /* Return normalized version of this */
  {
    Vec4f normalizedVector = *this;

    normalizedVector.normalize();

    return normalizedVector;
  }
}}
