#ifndef VEC4F_HPP
#define VEC4F_HPP

#include <iostream>

namespace GLEngine { namespace math {
  class Vec4f
  {
  public:
    Vec4f();
    Vec4f(const float& x, const float& y, const float& z, const float& w);
    Vec4f(const Vec4f& vec);

    float x, y, z, w;

    Vec4f add(const Vec4f& vec2); /* Add vec2 to vec1, return result | vec1 += vec2 */
    static Vec4f Add(const Vec4f& vec1, const Vec4f& vec2); /* Return addition of vec1 and vec2 | (vec1 + vec2) */

    Vec4f sub(const Vec4f& vec2); /* Sub vec2 from vec1, return result | vec1 -= vec2 */
    static Vec4f Sub(const Vec4f& vec1, const Vec4f& vec2); /* Return subtraction of vec2 from vec1 | (vec1 - vec2) */

    Vec4f mult(const Vec4f& vec2); /* Mult vec1 by vec2, return result | vec1 *= vec2 */
    static Vec4f Mult(const Vec4f& vec1, const Vec4f& vec2); /* Return product of vec1 and vec2 | (vec1 * vec2) */
    Vec4f mult(const float& scalar); /* Mult vec1 by scalar, return result | vec1 *= scalar */
    static Vec4f Mult(const Vec4f& vec1, const float& scalar); /* Return product of vec1 and scalar | (vec1 * scalar) */

    Vec4f div(const Vec4f& vec2); /* Div vec1 by vec2, return result | vec1 /= vec2 */
    static Vec4f Div(const Vec4f& vec1, const Vec4f& vec2); /* Return division of vec1 by vec2 | (vec1 / vec2) */

    //static float Dot(const Vec4f& forward, const Vec4f& other); /* Dot product of forward to other */

    float getMagnitude(); /* Calculate magnititude of vector */

    void normalize(); /* Normalize this */
    Vec4f Normalized(); /* Return normalized version of this */
  };

  inline std::ostream& operator<<(std::ostream& os, const Vec4f& vec) /* Converts Vec4f to output stream (cout-able) */
  {
    return (os << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]");
  }
}}

#endif
