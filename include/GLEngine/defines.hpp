#ifndef GLE_DEFINES_CPP
#define GLE_DEFINES_CPP

#define GLE_OPENGL_VERSION_MAJOR 3
#define GLE_OPENGL_VERSION_MINOR 3

#define GLE_MATERIAL_DEFAULT_SHININESS 16
#define GLE_MATERIAL_DIFFUSE_TEX_SLOT 0 // default texture slot of diffuse maps
#define GLE_MATERIAL_SPECULAR_TEX_SLOT 1 // default texture slot of specular maps

/* TODO: Figure out a better place for this, so it can be changed if needed */
#ifndef GLE_RESOURCES_PATH
#define GLE_RESOURCES_PATH "./resources/"
#endif

#endif
