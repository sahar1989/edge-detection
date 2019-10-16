# edge-detection with sobel filter in c++

#Objective:
The objective of this project is to experiment an image processing embedded on the board SABER IMX6 (ARM_Cortex-A9, quad-core):
  
#Tools: 
Linux OS, Raspberry OS, board SABER IMX6, OpenCV library with C language

The  Sobel operator performs a 2-D spatial gradient measurement on an image and so emphasizes regions of high spatial frequency that correspond to edges. Typically it is used to find the approximate absolute gradient magnitude at each point in an input grayscale image.

It computes the values of gradient pixel by pixel in direction of x and y with two functions, xGradient and yGradient. After reading the frame from camera and convert the BGR image to grayscale then applied median filter. By xGradient function we have computed the x component of the gradient vector at a given point in an image then returns gradient in the x direction and by yGradient function we have computed the y component of the gradient vector at a given point in an image returns gradient in the y direction.
