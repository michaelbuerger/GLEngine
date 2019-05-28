#ifndef VEC3F_HPP
#define VEC3F_HPP

#include <iostream>

namespace GLEngine { namespace math {
  class Vec3f
  {
  public:
    Vec3f();
    Vec3f(const float& x, const float& y, const float& z);
    Vec3f(const Vec3f& vec);

    float x, y, z;

    Vec3f add(const Vec3f& vec2); /* Add vec2 to vec1, return result | vec1 += vec2 */
    static Vec3f Add(const Vec3f& vec1, const Vec3f& vec2); /* Return addition of vec1 and vec2 | (vec1 + vec2) */

    Vec3f sub(const Vec3f& vec2); /* Sub vec2 from vec1, return result | vec1 -= vec2 */
    static Vec3f Sub(const Vec3f& vec1, const Vec3f& vec2); /* Return subtraction of vec2 from vec1 | (vec1 - vec2) */

    Vec3f mult(const Vec3f& vec2); /* Mult vec1 by vec2, return result | vec1 *= vec2 */
    static Vec3f Mult(const Vec3f& vec1, const Vec3f& vec2); /* Return product of vec1 and vec2 | (vec1 * vec2) */
    Vec3f mult(const float& scalar); /* Mult vec1 by scalar, return result | vec1 *= scalar */
    static Vec3f Mult(const Vec3f& vec1, const float& scalar); /* Return product of vec1 and scalar | (vec1 * scalar) */

    Vec3f div(const Vec3f& vec2); /* Div vec1 by vec2, return result | vec1 /= vec2 */
    static Vec3f Div(const Vec3f& vec1, const Vec3f& vec2); /* Return division of vec1 by vec2 | (vec1 / vec2) */

    //static float Dot(const Vec3f& forward, const Vec3f& other); /* Dot product of forward to other */

    float getMagnitude(); /* Calculate magnititude of vector */

    void normalize(); /* Normalize this */
    Vec3f Normalized(); /* Return normalized version of this */
  };

  inline std::ostream& operator<<(std::ostream& os, const Vec3f& vec) /* Converts Vec3f to output stream (cout-able) */
  {
    return (os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]");
  }
}}

#endif
