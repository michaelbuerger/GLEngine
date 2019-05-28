#ifndef VEC2F_HPP
#define VEC2F_HPP

#include <iostream>

namespace GLEngine { namespace math {
  class Vec2f
  {
  public:
    Vec2f();
    Vec2f(const float& x, const float& y);
    Vec2f(const Vec2f& vec);

    float x, y;

    Vec2f add(const Vec2f& vec2); /* Add vec2 to vec1, return result | vec1 += vec2 */
    static Vec2f Add(const Vec2f& vec1, const Vec2f& vec2); /* Return addition of vec1 and vec2 | (vec1 + vec2) */

    Vec2f sub(const Vec2f& vec2); /* Sub vec2 from vec1, return result | vec1 -= vec2 */
    static Vec2f Sub(const Vec2f& vec1, const Vec2f& vec2); /* Return subtraction of vec2 from vec1 | (vec1 - vec2) */

    Vec2f mult(const Vec2f& vec2); /* Mult vec1 by vec2, return result | vec1 *= vec2 */
    static Vec2f Mult(const Vec2f& vec1, const Vec2f& vec2); /* Return product of vec1 and vec2 | (vec1 * vec2) */
    Vec2f mult(const float& scalar); /* Mult vec1 by scalar, return result | vec1 *= scalar */
    static Vec2f Mult(const Vec2f& vec1, const float& scalar); /* Return product of vec1 and scalar | (vec1 * scalar) */

    Vec2f div(const Vec2f& vec2); /* Div vec1 by vec2, return result | vec1 /= vec2 */
    static Vec2f Div(const Vec2f& vec1, const Vec2f& vec2); /* Return division of vec1 by vec2 | (vec1 / vec2) */

    //static float Dot(const Vec2f& forward, const Vec2f& other); /* Dot product of forward to other */

    float getMagnitude(); /* Calculate magnititude of vector */

    void normalize(); /* Normalize this */
    Vec2f Normalized(); /* Return normalized version of this */
  };

  inline std::ostream& operator<<(std::ostream& os, const Vec2f& vec) /* Converts Vec2f to output stream (cout-able) */
  {
    return (os << "[" << vec.x << ", " << vec.y << "]");
  }
}}

#endif
