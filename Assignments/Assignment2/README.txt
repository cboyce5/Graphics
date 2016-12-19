Name: Cliff Boyce
Hero Name: Vorago
Description: This program demonstrates mouse and keyboard functionality with respect to our hero.

Usage:

	The character's staff is in constant motion, as it rotates around one of the characters hands

	The following keys accomplish the follows tasks:
		2: Move character down
		4: Move character left
		6: Move character right
		8: Move character up
		ESC: Closes the program

	If mouse1 is pressed, the color of the character's eyes change between black and white, 
		depending on if the key is helf down or not.

	The color of the ear-like thing depends on the location of the mouse on the screen. One ear 
		is changed to a non-rock color wherever the cursor is moved to another quadrant.
		
Compilation Instruction: none

How long did this assignment take? ~3-4 hours.
	
How much did the lab help with this assignment? 10/10, very helpful.

How fun was the assignment? 8/10, still taking the tedious time to think out shapes is not fun, but 
	it cant really avoided thus far.
	
Questions:

a.	glPushMatrix();
	glTranslatef(0,0,0);
	glRotatf(theta,0,0,1);
	drawHelmet();
	glTranslatef(x,y,0);
	glPopMatrix();
	
	//By translating to the origin and then rotating, the object rotates around the new origin, and in 
	//this case is (0,0), and then rotating back to its original location, it will have translated around the origin.
	
b.	glPushMatrix();
	glTranslatef(-i,-j,0);
	glRotatf(theta,0,0,1);
	drawHelmet();
	glTranslatef(i,j,0);
	glPopMatrix();
	
	//Same logic as above, just with the arbitrary points (i,j) instead of the origin, and the location back is also (i,j).

c.	//as discussed in class using the matrix
	//	|	cos(theta)	0			0	|
	//	|	0			sin(theta)	0	|
	//	|	0			0			1	|
	
	//performs shear, so multiplying the model matrix by this performs the shear according to andgle theta

	glPushMatrix();
	//multiply by matrix above
	drawHelmet();
	glPopMatrix();