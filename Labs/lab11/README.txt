Q1: How do they roll?
	They roll in their direction, but do not stay on the grid, as there appears to be no boynding box for the movement of the ball.

Q2: Do the balls stay contained within the ground plane?
	Yes. Normals: (groundSize,0,z) ~ (-1, 0, 0)
				  (-groundSize,0,z) ~ (1, 0, 0)
				  (x,0,groundSize) ~ (0, 0, -1)
				  (x,0,-groundSize) ~ (0, 0, 1)

Q3: How do we compute the normals? What equation gives us our two normals?
	Since the normals are just the collision point to the center of each ball, we subtract the locations, just in different order.
	N1 = L2 - L1
	N2 = L1 - L2

Q4: Success?
	Yep.

Q5: How fun was this lab?
	9/10.

Q6: How was the writeup for the lab?
	Fine. Vector math was very helpful. Only confusing part was descibing the normals for ball to ball collision, but it is hard to explain in readable english, so it was fine.

Q7: How long did this lab take?
	2 hours.

Q8: Comments?
	Nope.