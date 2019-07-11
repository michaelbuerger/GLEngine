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

namespace GLEngine { namespace graphics {


}}