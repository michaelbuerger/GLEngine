#include "GLEngine/math/Vec3f.hpp"

namespace GLEngine { namespace math {
  Vec3f::Vec3f()
  {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }
  Vec3f::Vec3f(const float& x, const float& y, const float& z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Vec3f::Vec3f(const Vec3f& vec)
  {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }

  Vec3f Vec3f::add(const Vec3f& vec2) /* Add vec2 to vec1, return result | vec1 += vec2 */
  {
    this->x += vec2.x;
    this->y += vec2.y;
    this->z += vec2.z;

    return *this;
  }
  Vec3f Vec3f::Add(const Vec3f& vec1, const Vec3f& vec2) /* Return addition of vec1 and vec2 | (vec1 + vec2) */
  {
    Vec3f vec(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);

    return vec;
  }

  Vec3f Vec3f::sub(const Vec3f& vec2) /* Sub vec2 from vec1, return result | vec1 -= vec2 */
  {
    this->x -= vec2.x;
    this->y -= vec2.y;
    this->z -= vec2.z;

    return *this;
  }
  Vec3f Vec3f::Sub(const Vec3f& vec1, const Vec3f& vec2) /* Return subtraction of vec2 from vec1 | (vec1 - vec2) */
  {
    Vec3f vec(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);

    return vec;
  }

  Vec3f Vec3f::mult(const Vec3f& vec2) /* Mult vec1 by vec2, return result | vec1 *= vec2 */
  {
    this->x *= vec2.x;
    this->y *= vec2.y;
    this->z *= vec2.z;

    return *this;
  }
  Vec3f Vec3f::Mult(const Vec3f& vec1, const Vec3f& vec2) /* Return product of vec1 and vec2 | (vec1 * vec2) */
  {
    Vec3f vec(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);

    return vec;
  }
  Vec3f Vec3f::mult(const float& scalar) /* Mult vec1 by scalar, return result | vec1 *= scalar */
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
  }
  Vec3f Vec3f::Mult(const Vec3f& vec1, const float& scalar) /* Return product of vec1 and scalar | (vec1 * scalar) */
  {
    Vec3f vec(vec1.x * scalar, vec1.y * scalar, vec1.z * scalar);

    return vec;
  }

  Vec3f Vec3f::div(const Vec3f& vec2) /* Div vec1 by vec2, return result | vec1 /= vec2 */
  {
    this->x /= vec2.x;
    this->y /= vec2.y;
    this->z /= vec2.z;

    return *this;
  }
  Vec3f Vec3f::Div(const Vec3f& vec1, const Vec3f& vec2) /* Return division of vec1 by vec2 | (vec1 / vec2) */
  {
    Vec3f vec(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);

    return vec;
  }
}}
