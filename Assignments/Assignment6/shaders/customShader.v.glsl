/*
 *   Vertex Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

varying vec4 theColor;
uniform float age;

void main() {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    
    // TODO #14: modify our vertex in object space

	
    // TODO #8: Perform the Vertex Transformation from Object Space to Clip Space
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 


    
    // TODO #12: set our varying variable equal to the Vertex
	theColor = vec4(age,age,age,1);
	
	/*****************************************/
    /********* Texture Calculations  *********/
    /*****************************************/

    // pass the texture coordinate through to the fragment processor
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
