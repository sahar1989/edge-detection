/*
 * Fichier source pour le projet d'unité
 *  INF-4101C
 *---------------------------------------------------------------------------------------------------
 * Pour compiler : g++ `pkg-config --cflags opencv` projet_base_imc.cpp `pkg-config --libs opencv` -o projet
 *---------------------------------------------------------------------------------------------------
 * auteur : Eva Dokladalova 09/2015
 * modification : Eva Dokladalova 10/2017
 * modificaiton : Eva Dokladalova 10/2018
 */


/* 
 * Libraries stantards 
 *
 */ 
#include <stdio.h>
#include <stdlib.h>

/* 
 * Libraries OpenCV "obligatoires" 
 *
 */ 
#include "highgui.h"
#include "cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
/* 
 * Définition des "namespace" pour évite cv::, std::, ou autre
 *
 */  
using namespace std;
using namespace cv;
using std::cout;
/*
 * Some usefull defines
 * (comment if not used)
 */
#define PROFILE
#define VAR_KERNEL
#define N_ITER 100

#ifdef PROFILE
#include <time.h>
#include <sys/time.h>
#endif
// Computes the x component of the gradient vector
// at a given point in a image.
// returns gradient in the x direction
int xGradient(Mat image, int x, int y)
{
	return image.at<uchar>(y - 1, x - 1) +
		2 * image.at<uchar>(y, x - 1) +
		image.at<uchar>(y + 1, x - 1) -
		image.at<uchar>(y - 1, x + 1) -
		2 * image.at<uchar>(y, x + 1) -
		image.at<uchar>(y + 1, x + 1);
}

// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction

int yGradient(Mat image, int x, int y)
{
	return image.at<uchar>(y - 1, x - 1) +
		2 * image.at<uchar>(y - 1, x) +
		image.at<uchar>(y - 1, x + 1) -
		image.at<uchar>(y + 1, x - 1) -
		2 * image.at<uchar>(y + 1, x) -
		image.at<uchar>(y + 1, x + 1);
}
/*
 *
 *--------------- MAIN FUNCTION ---------------
 *
 */
int main()
{
//----------------------------------------------
// Video acquisition - opening
//----------------------------------------------
          VideoCapture cap(0); // le numéro 0 indique le point d'accès à la caméra 0 => /dev/video0
	  if(!cap.isOpened()){
	    cout << "Errore"; return -1;
	  }
	//----------------------------------------------
	// Déclaration des variables - imagesize
	// Mat - structure contenant l'image 2D niveau de gris
	// Mat3b - structure contenant l'image 2D en couleur (trois cannaux)
	// Some examples of Mat copy :
	//      Mat F = A.clone();
	//      Mat G;
	//      A.copyTo(G);
	// Some usefum examples :
	//      int ni = G.cols; // columns number
	//      int nj = G.rows; // rows number
	//      int pixel =  A.at<int>(i, j)); // access to one element of a matrix 
	 int f = 0;
	 Mat src, dst,gray,median;
	 int gx, gy, sum;
         unsigned char key = '0';
	 //change the size
  
	#define PROFILE
	#ifdef PROFILE
	// profiling / instrumentation libraries
	#include <time.h>
	#include <sys/time.h>
	#endif
	  
	//----------------------------------------------------
	// Création des fenêtres pour affichage des résultats
	// vous pouvez ne pas les utiliser ou ajouter selon ces exemple
	// 
	  cvNamedWindow("Video input", WINDOW_AUTOSIZE);
	  cvNamedWindow("Video gray levels", WINDOW_AUTOSIZE);
	  cvNamedWindow("Video Mediane", WINDOW_AUTOSIZE);
	  cvNamedWindow("Video Edge detection", WINDOW_AUTOSIZE);
	// placement arbitraire des  fenêtre sur écran 
	// sinon les fenêtres sont superposée l'une sur l'autre
	  cvMoveWindow("Video input", 10, 30);
	  cvMoveWindow("Video gray levels", 800, 30);
	  cvMoveWindow("Video Mediane", 10, 500);
	  cvMoveWindow("Video Edge detection", 800, 500);
          FILE * fp;
	  while(key!='q')
	  {
	      
	    // acquisition d'une trame video - librairie OpenCV
	    cap.read(src);
	    //conversion en niveau de gris - librairie OpenCV
	    cvtColor(src, gray, CV_BGR2GRAY);
            dst = gray.clone();
	    int k = 5;   
	    medianBlur(gray, median, k);
	 
	   if (!median.data)
	   {
	      return -1;
	   }
 
           #ifdef PROFILE
	      struct timeval start, end;
	     gettimeofday(&start, NULL);
	  #endif 
          // ----------------REPLACE START------------------------------
	for (int y = 0; y < median.rows; y++)
	for (int x = 0; x < median.cols; x++)
		dst.at<uchar>(y, x) = 0.0;

	for (int y = 1; y < median.rows - 1; y++)
	{
	        for (int x = 1; x < median.cols - 1; x++)
		{
			gx = xGradient(median, x, y);
			gy = yGradient(median, x, y);
			sum = abs(gx) + abs(gy);
			sum = sum > 255 ? 255 : sum;
			sum = sum < 0 ? 0 : sum;
			dst.at<uchar>(y, x) = sum;
		}
	}
       // ----------------REPLACE END--------------------------------
	//imwrite("testsobel.jpg",dst);
	    #ifdef PROFILE
	    gettimeofday(&end, NULL);
	    double e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);
	    double s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
	    printf("frame %d : sobel exec time : %lf us\n", f, (e - s));
	    #endif
	    
	    fp = fopen ("frist_naive_v.txt", "a");
	    fprintf(fp, "frame %d : sobel exec time : %lf us\n", f, (e - s));
	    imshow("Video Edge detection",dst);    
	    imshow("Video gray levels",gray);
	    imshow("Video input",src);
	    imshow("Video Mediane",median);    
            f++;
            key=waitKey(5);
       }
       fclose(fp);
       return 0;
}
