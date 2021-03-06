#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>

using namespace cv;
using namespace std;

//function prototype for accumulator matrix calculation
Mat CalcAccumulator(Mat matrix, int r);
//function prototype for finding the global maximum in the matrix, with optional parameters
//xm and ym for the coordinates of the global maximum
int MatGlobalMax(Mat matrix);


int main(int argc, char** argv) {
  Mat img, gray, edge;
  int r_min, r_max;
  int max_el = 0;
  int prev_max_el = 0;
  int det_radius;
  //Read the image and store it in a matrix
  if(argc != 2 || !(img = imread(argv[1], 1)).data)
    return -1;

  //Read the min and max radius from the user input
  cout << "Enter the minimum radius(in pixels) : " << endl;
  cin >> r_min;
  cout << "Enter the maximum radius(in pixels) : " << endl;
  cin >> r_max;

  cvtColor(img, gray, COLOR_BGR2GRAY); //grayscale conversion
  //medianBlur(gray, gray, 5); //blur the image to smooth out edges that create noise
  Canny(gray, edge, 100, 200); //Canny edge detection, store the result in matrix edge

  namedWindow("Edges", 1);
  imshow("Edges", edge);


  //extracting the size of the image
  //e.g. if the image size iz 852x480 then the image has 480 rows and 852 columns
  int height = edge.rows;
  int width = edge.cols;


  cout << "Image size is: " << width << "x" << height << " pixels" << endl;

  //Correct accumulator matrix i.e. the one with the highest maximum element
  Mat correct_acc(height, width, CV_32S);
  Mat acc(height, width, CV_32S);

  //construct an accumulator matrix for every r in range(r_min, r_max)
  for(int r = r_min; r <= r_max; r++) {
    acc = CalcAccumulator(edge, r);
    //find the global maximum of the acc. matrix
    max_el = MatGlobalMax(acc);
    cout << "Max. element of accumulator matrix for r = " << r << " is " << max_el << endl;

    //Compares the previous max. element to the new one
    //This results in the matrix with the highest maximal value, the correct matrix
    //Other matrices are for radii that aren't contained in the image
    //Note: this approach works because we detect cirlces on dice, which have circles with the same radii
    //So one matrix contains all the centers of the circles
    if(prev_max_el < max_el) {
      correct_acc = acc;
      prev_max_el = max_el;
      det_radius = r;
    }
  }

  cout << "--------------------------------------------------------" << endl;
  cout << "BEGINNING CIRCLE DETECTION" << endl;

  int num_circles = 0; //number of detected circles
  int flag = 1; //flag variable for ending the search
  int xm;
  int ym;

  max_el = 0;
  prev_max_el = 0;

  while(flag) {
    max_el = 0;

    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        if(max_el < correct_acc.at<int>(y,x)) {
          max_el = correct_acc.at<int>(y,x);
          xm = x;
          ym = y;
        }
      }
    }
    cout << "max. element = " << max_el << endl;
    cout << "x = " << xm << endl;
    cout << "y = " << ym << endl;
    cout << "*****************" << endl;

    //Put the 5 elements left and right of the center of the peak to 0(to eliminate them from the search)
    for(int y = ym - 5; y < ym + 6; y++) {
      for(int x = xm - 5; x < xm + 6; x++) {
        correct_acc.at<int>(y,x) = 0;
      }
    }
    //if the previous peak deteriorates for 0.65, then it is not a circle, just noise
    //the value was calculated throught experiments, but might be input for the algorithm too
    //signal that the search is over by setting the flag to 0

    if(prev_max_el * 0.65 > max_el) {
      flag = 0;
    }else {
      ++num_circles;
      //Mark the circle on the image
      Point center(xm, ym);
      circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
      circle(img, center, det_radius, Scalar(255, 0 ,0), 3, 8, 0);
    }

    prev_max_el = max_el;

    //End the search if 6 circles are found
    if(num_circles == 6) {
      flag = 0;
      cout << "ENDED DUE TO OVERFLOW" << endl;
    }
  }

  cout << "Number of detected circles: " << num_circles << endl;

  namedWindow("circles", 1);
  imshow("circles", img);

  waitKey(0);


  return 0;
}




int MatGlobalMax(Mat matrix) {
  int global_max = 0;

  for(int y = 0; y < matrix.rows; y++) {
    for(int x = 0; x < matrix.cols; x++) {
      if(global_max < matrix.at<int>(y,x)) {
        global_max = matrix.at<int>(y,x);
      }
    }
  }

  return global_max;
}

Mat CalcAccumulator(Mat matrix, int r) {
  //accumulator matrix, type CV_32S (i.e. int), intialized with zeros
  int height = matrix.rows;
  int width = matrix.cols;
  Mat acc = Mat::zeros(height, width, CV_32S);
  int a,b;

  //For each pixel, draw a circle in the parameter space with the diameter r
  //Increment the pixel in the accumulator matrix where the circle has passed
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      //Check if the pixel is black, to avoid unnecessary computation
      if(matrix.at<uchar>(y,x) != 0) {
        //Draw a circle around the pixel
        for(int theta = 0; theta < 360; theta++) {
          a = cvRound(x - r * cos(theta));
          b = cvRound(y - r * sin(theta));

          //check whether the value of (a,b) is within acc bounds
          if(a < width && b < height)
            acc.at<int>(b,a) += 1;
        }
      }
    }
  }

  cout << "Finished accumulator matrix for r = " << r << endl;
  return acc;
}

