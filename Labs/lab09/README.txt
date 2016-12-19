Q1: What is a uniform variable for GLSL?
	A uniform variable is used to pass values to the vertex or fragment shader from OpenGL code. Can be used for light, location, color etc.

Q2: What is an attribute variable for GLSL?
	An attribute variable is used to pass per vertex atributes, such as normals, textures coords, etc.
	
Q3: Why do we not need to recompile the C++ code after we modify the GLSL code?
	Because the compilation of the GLSL code is called within functions in the C++ code, we dont need to recompile every time we change the GLSL code.
	We also did not change anything in the C++ code, so we dont need to recompile it.
	
Q4: The colored ball loks the way it does because the coordinates of the vertex are different over the spehere, so the color which is defined by the vertex
	is different when a vertex is in a different position.
	
Q5: Clear up confusion involving GLSL and GLEW?
	Yep.
	
Q6: How fun was this lab?
	10/10
	
Q7: How was the writeup?
	Very good, lots of todos in smaller parts with one or two, lines each, easier to retrace steps to figure out errors.
	
Q8: How long did this lab take?
	1-2 hours.
	
Q10: Any other comments?
	No.