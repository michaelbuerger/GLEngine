/* Options to pass to GLEngine Standard Shader
 * Color (bool) (true = add color multiplier to whatever follows, false = use vec4(1.0, 1.0, 1.0, 1.0))
 * Texture (bool) (true = assume that a texture will be passed, false = use vec4(1.0, 1.0, 1.0, 1.0))
 * Lighting (bool) (true = use properties below, false = unlit)
 *     Shininess (float) (higher = more shiny/less rough)
 *     Per light (passed as an array of structs or an array of each property)
 *         Light strength (float)
 *         Light color (vec3)
 *         Ambient strength (float) (0 = off)
 *         Diffuse strength (float) (0 = off)
 *         Specular strength (float) (0 = off)
 */