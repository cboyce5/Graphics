Name: Cliff Boyce
Hero Name: Vorago
Email: cboyce@mymail.mines.edu
Assignment: Assignment6

1.	Description
		A program that uses particle systems and shaders to mimic rain.
		
2.	Usage
		wasd - move hero around screen
		mouse - pan camera around
		countrol+mouse - zoom

3.	Compilation instructions
		Pass in a control file as an argument. 2 provided files are control1.txt and control2.txt
		
4.	Bugs/implementations details
		It appears as if the particles die after they reach the depth specified in the file, but in fact they just get a new x and z value, and a reset y value.
		The actual dying of particles could be done with sets, but much of the reused code from pervious labs was set up with vectors, and this version of
		c++ is not compatible with range based for loops, so vectors were used. Also, the only particle system is the rain system, as I did not have time to
		implement other systems, or make the file be able to make different systems.
		
5.	Assignment length
		3-4 hours.
		
6.	Was the lab helpful?
		Yes. 10/10.
	
7.	How fun was this assignment?
		9/10.

8.	Control file structure of particle system
		<x of system> <y of system> <z of system> <width> <depth> <min velocity> <max velocity> <count/rate>
		Note: there is no way to make different systems, as only the rain system was implemented.