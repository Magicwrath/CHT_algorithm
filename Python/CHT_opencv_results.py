import cv2 as cv
import numpy as np

img = cv.imread("Red-Dice-PNG-Clipart-Background.png", 0)
img = cv.medianBlur(img, 5)
#cv.imshow('grayscale blur', img)
cimg = cv.cvtColor(img, cv.COLOR_GRAY2BGR)

circles = cv.HoughCircles(img, cv.HOUGH_GRADIENT, 1, 65, param1=50, param2=45, minRadius=0, maxRadius=0)
rounded_circles = np.uint16(np.around(circles, decimals=0))
print(rounded_circles)

for i in rounded_circles[0, :]:
    cv.circle(cimg, (i[0], i[1]), i[2], (0, 255, 0), 2)
    cv.circle(cimg, (i[0], i[1]), 2, (0, 0, 255), 3)

cv.imshow('results', cimg)
cv.waitKey(0)
cv.destroyAllWindows()