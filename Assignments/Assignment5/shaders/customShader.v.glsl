/*
 *   Vertex Shader
 *
 *   CSCI 441, Computer Graphics, Colorado School of Mines
 */

#version 120

varying vec4 theColor;

void main() {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    
    // TODO #14: modify our vertex in object space

	
    // TODO #8: Perform the Vertex Transformation from Object Space to Clip Space
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 


    
    // TODO #12: set our varying variable equal to the Vertex
	theColor = gl_Vertex;
}
