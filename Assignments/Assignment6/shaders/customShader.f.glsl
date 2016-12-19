/*
 *   Fragment Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

varying vec4 theColor;
uniform sampler2D tex;

void main() {

	/*****************************************/
    /********* Texture Calculations  *********/
    /*****************************************/

    // get the texel corresponding to the interpolated texture coordinates
    vec4 texel = texture2D( tex, gl_TexCoord[0].st );

    /*****************************************/
    /******* Final Color Calculations ********/
    /*****************************************/
    vec3 ct = texel.rgb;
    vec3 cf = theColor.rgb;

    float at = texel.a;
    float af = theColor.a;
    
	gl_FragColor = vec4( cf * ct, at);
}
