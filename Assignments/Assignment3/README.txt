Name: Cliff Boyce
Hero Name: Vorago
Email: cboyce@mines.edu
Assignment/Project: Assignment3

1. Description
	
	This program creates a 3-D world, and using the wasd keys, can move a car object around the world.

2. Usage

	Keys:
		w - moves the character forwards
		a - turns the character left
		s - moves the character backwards
		d - turns the character right
		q/ESC - quit program
		
	Mouse:
		left-click and dra - moves the camera around the character
		left-click and drag and hold CTRL - zoom in and out by moving mouse up or down
		
3. Compilation

	Change makefile to correct locations of folders, whether in the lab or not.

4. Implementation Details/Bugs
	
	Due to time constraints, and the vague nature of the writeup, you are not able to turn and move at the same time,
	unless the two keys are pressed at the exact time.

5. How long did the assignment take?

	3-4 hours.

6. How helpful was the corresponding lab (1-10 scale)?
	
	10/10. Very helpful learning the basics of 3-D space and how to use callbacks with it.
	
7. How fun was the assignment (1-10 scale)?
	
	9/10. Fun to design the world and caracter, but hard to troubleshoot certain bugs without scouring internet for help.
	
8. Requirements

	-Character is created in a hierarchical fashion. There are calls for parts of the car, and the body.
	-The wheels spin when moving, changing rotation direction if the car is moving forward or backward.
	-Pressing w and s move the car forward and backward.
	-Pressing a and d change the character's heading.
	-Character rotates when heading is changed.
	-Scenery is found within the scene. There are torches (if you will) around the grid, with a fence around the outside.
	-Character is made of several colors.
	-Character is comprised of primitives.
	-Camera uses arcball movement. If the character moves, so does the camera.
	-Angle of view can be changed with left-mouse press and drag around screen.
	-Zooming in and out is achieved by pressing left-mouse and dragging while holding CTRL.