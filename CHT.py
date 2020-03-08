import numpy as np
import cv2 as cv
import math

#Read the image and convert it to grayscale
image = cv.imread('Red-Dice-PNG-Clipart-Background.png', 0)

#Use Canny edge detection algorithm for the edge extraction
edge = cv.Canny(image, 50, 70)
print(edge[0])
print(len(edge))
print(len(edge[0]))
#edge is an array of 480 elements, and the elements are arrays of 852 elements
#852x480 size of the image


#CHT ALGORITHM:
#results from opencv CHT function found circles with radius approx 30
#we will test the algorithm from radius 25 to 35

#accumulator 2D matrix, r = 29
accumulator = np.zeros((480, 852))

#iterate through every pixel
for x in range(0, 479):
    for y in range(0, 851):
        if edge[x, y] != 0:
            #if the pixel isn't black
            #calculate the circle points (a,b) with radius r = 29 around the pixel
            for theta in range(0, 360):
                a = np.uint16(x - 29*math.cos(theta * math.pi / 180))
                b = np.uint16(y - 29*math.sin(theta * math.pi / 180))
                accumulator[a, b] += 1


print(accumulator[300])
#cv.imshow('Original grayscale image', image)
#cv.imshow('Edge detection result', edge)
#cv.waitKey(0)
#cv.destroyAllWindows()