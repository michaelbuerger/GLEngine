#ifndef GLE_DEFINES_CPP
#define GLE_DEFINES_CPP

#define GLE_OPENGL_VERSION_MAJOR 3
#define GLE_OPENGL_VERSION_MINOR 3

#define GLE_MATERIAL_DEFAULT_SHININESS 16

#define GLE_MATERIAL_DIFFUSE_TEX_SLOT GL_TEXTURE0 // default texture slot of diffuse maps, uniform binding ->
#define GLE_MATERIAL_DIFFUSE_UNIFORM_ID 0

#define GLE_MATERIAL_SPECULAR_TEX_SLOT GL_TEXTURE1 // default texture slot of specular maps, uniform binding ->
#define GLE_MATERIAL_SPECULAR_UNIFORM_ID 1

#define GLE_SHADOWMAP_TEX_SLOT GL_TEXTURE4 // default texture slot of shadow maps, uniform binding ->
#define GLE_SHADOWMAP_UNIFORM_ID 4

/* TODO: Figure out a better place for this, so it can be changed if needed */
#ifndef GLE_RESOURCES_PATH
#define GLE_RESOURCES_PATH "./resources/"
#endif

#endif