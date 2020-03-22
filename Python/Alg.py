import numpy as np
import cv2 as cv
import math

#Read the image, use flag 0 to convert it to grayscale
image = cv.imread('Red-Dice-PNG-Clipart-Background.png', 0)
imageBlur = cv.medianBlur(image,5) #Might be an extra step, we will see
edge = cv.Canny(imageBlur, 100, 200) #Use Canny edge detection algorithm for edge extraction
cimg = cv.cvtColor(image, cv.COLOR_GRAY2BGR) #an array used just to show the results on the picture


#The edge is an array of arrays
#It is made up of y arrays, all containing x elements
#Therefore, the dimensions of the image are x*y

#The dimensions:
height = len(edge)
width = len(edge[1])

#Search parameters, minimal and maximal radius of possible circles
#These parameters will be inputs for the algorithm
r_min = 28
r_max = 30

max_el = 0
prev_max_el = 0
for r in range(r_min, r_max +1):
    acc = np.zeros((height, width)) #The accumulator matrix, dimensions x*y i.e. the picture dim.
    for y in range(0, height):
        for x in range(0, width):
            if edge[y, x] != 0: #checks if the pixel is black, to avoid unnecessary computation
                #Draws a circle around the pixel
                for theta in range(0, 360):
                    a = np.uint16(x - r * math.cos(theta * math.pi / 180)) #x value of the circle point
                    b = np.uint16(y - r * math.sin(theta * math.pi / 180)) #y value of the circle point
                    if a < width - 1 and b < height -1: #checks if the value is in the picture dimensions
                        #Increments the pixel in the accumulator matrix where the circle has passed
                        acc[b, a] += 1

    print("gotova matrica akumulacije")

    #Finds the maximal element in the accumulator matrix
    for y in range(0, height):
        for x in range(0, width):
            if max_el < acc[y, x]:
                max_el = acc[y, x]

    #Compares the previous max. element to the new one
    #This results in the matrix with the highest maximal value, the correct matrix
    #Other matrices are for radii that aren't contained in the image
    #Note: this approach works because we detect cirlces on dice, which have circles with the same radii
    #So one matrix contains all the centers of the circles
    if prev_max_el < max_el:
        correct_acc = acc
        prev_max_el = max_el #correction, the prev_max_el should be updated here
        det_radius = r #the detected radius

    print("max_el= ",max_el)


print("---------------------------------------------------------------------")

num_circles = 0 #number of detected circles
flag = 1 #flag for ending the search
prev_max_el = 0


while flag:
    num_circles += 1
    max_el = 0
    #Find the first peak, i.e. the first circle center
    #Memorize the x and y coordinates of the peak in the matrix i.e. the center of the circle
    for y in range(0, height):
        for x in range(0, width):
            if max_el < correct_acc[y, x]:
                max_el = correct_acc[y, x]
                ym = y
                xm = x

    print("najveci el: ",max_el)
    print("y=", ym)
    print("x=", xm)

    #Put the 5 elements left and right of the center of the peak to 0(to eliminate them from the search)
    for y in range(ym - 5, ym + 6):
        for x in range(xm - 5, xm + 6 ):
            if x < width - 1 and y < height -1: #check if the values are within picture bounds
                correct_acc[y, x] = 0

    #if the previous peak deteriorates for 0.65, then it is not a circle, just noise
    #the value was calculated throught experiments, but might be input for the algorithm too
    #signal that the search is over by setting the flag to 0
    if prev_max_el * 0.65 > max_el:
        flag = 0
        num_circles -= 1
    else:
        #draw circles on the image, just for visual results
        cv.circle(cimg, (xm, ym), det_radius, (0, 255, 0), 2)
        cv.circle(cimg, (xm, ym), 2, (0, 0, 255), 3)

    #Memorize the cirlce parameters
    prev_max_el = max_el

print("Broj krugova na kocki je: ", num_circles)



#show the picture with the results
cv.imshow('results', cimg)
cv.waitKey(0)
cv.destroyAllWindows()
