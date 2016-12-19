Name: Cliff Boyce
Hero Name: Vorago
Email: cboyce@mines.edu
Assignment/Project: Assignment4

1.	Description

		This program extends on both assignment3 and lab03, by taking the world and character we created
		lab03, and adding a bezier curve and a sprite that collows the bezier curve, all focused around
		the character.

2.	Usage

	Keys:
		w - moves the character forwards
		a - turns the character left
		s - moves the character backwards
		d - turns the character right
		q/ESC - quit program
		
	Mouse:
		left-click and dra - moves the camera around the character.
		left-click and drag and hold CTRL - zoom in and out by moving mouse up or down.
		right-click - menu that allows the user to toggle the bezier curve and the control points, as well as
			an option to quit.

3.	Compilation

		Make sure the makefile is set up appropriately.
		
4. Implementation Details/Bugs
	
	The writeup (and lack of posts on piazza) was not clear on if the sprite/pet thing should be animated on 
	its own (as in rotating head/spinning arms) so my follower is a present for the holidays, with no animation
	other than moving along the bezier curve. Also, depending on the 'number' of bezier curves, you will have 
	equally many objects/sprites rotating around the character. This is because my function allows for any number 
	of bezier curves to be read in and rendered, but the way the object/sprite/pet is shown is by checking inside 
	the render loop if some certain counters are equal, and then drawing the object. Because this function is called 
	for each curve, there will be as many boxes as there are curves. I did not have time to implement a way to draw 
	one sprite/object/pet for any number of input curves.

5. How long did the assignment take?

	3-4 hours.

6. How helpful was the corresponding lab (1-10 scale)?
	
	10/10. Gave the basic code for bezier curves and such.
	
7. How fun was the assignment (1-10 scale)?
	
	9/10.
	
8. Requirements

	-Control points are read in correctly, even with more than 4 points.
	-Bezier curve is evaluated and drawn correctly.
	-Control points and control cage are draw correctly.
	-Pet/sprite is drawn hierarchically
	-Pet moves along curve, jumps back to start of curve, still revolves around hero
	-Bezier curve is centered around hero, curve is still centered if hero moves/rotates.
	-Camera class is defined and implemented correctly.
	-Arcball camera, zooms correctly.
	-Pop up menu is attached to right mouse button. Options to toggle cage/line, toggle curve and quit.