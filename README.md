# MonteCarloPi

MonteCarlo simulation can be used to estimate the value of Pi by generating x and y points in a 2-D space. A circle of radius r is included inside a square of side r*2, with the circle centered in the middle of the square. 

Points are randomly generated within the square. By using the ratio of points generated inside the circle and total points generated, an approximation of Pi is obtainted. As more points are generated, the accuracy of the estimation will slowly improve. 

To check if the points generated are within the circle, the following evaluation is made:

x² + y² <= radius²