//http://paulbourke.net/dataformats/obj/
//https://en.wikipedia.org/wiki/Wavefront_.obj_file

/* Sudo code for generating default tex coords per vertex:
 * Take vertex x y z (assume model space normalized)
 * if x between -1 and 0: U = 0
 * if x greater than 0: U = 1
 * 
 * if y between -1 and 0: V = 0
 * if y greater than 0: V = 1
 */

/* Figure out way to generate normals */

#include "GLEngine/graphics/ModelHandler.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"

namespace GLEngine { namespace graphics {

    GLfloat square_vertices_texcoords_normals[]
    {
        1.0f, 1.0f, 0.0f,    1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top-right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom-right
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top-left
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f  // bottom-left
    };

    GLint square_indices[]
    {
        2, 1, 3, 0, 1, 2
    };

    ModelHandler::ModelHandler()
    {

    }

}}