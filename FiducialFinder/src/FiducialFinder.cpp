#include<opencv2/opencv.hpp>
#include "FiducialFinder.h"



using namespace cv;




FiducialFinder::FiducialFinder(Mat image)
{

  this->image = image;

}

/* Getter functions for the tissue and needle images */
Mat FiducialFinder::getImage()
{
  return image;
}

Point2f FiducialFinder::getCentroid()
{
  return centroid;
}

void FiducialFinder::setCentroid(Point2f centroid)
{
  this->centroid = centroid;
}



/** This function performs hsv thresholding.
 * on the image
 * @param None
 */
void FiducialFinder::beginSearch()
{

  Mat frame = getImage(); //Source Image
  Mat gray;  //Destination matrix
  Mat hsv;
  Mat thresh; //Destination matrix

  cvtColor(frame, hsv, CV_BGR2GRAY);  //Convert to gray  
  Scalar lowerBound (100, 240, 240);
  Scalar upperBound (180, 255, 255);
  inRange(hsv, lowerBound, upperBound, hsv);

  //  threshold(gray, thresh, thresholdValue, maxVal, THRESH_TOZERO);


  imshow("Thresholding", hsv);
  waitKey(0);
  searchForContours(hsv); 
  
 
}

/** This function search for contours in the thresholded image
 * @param thresh Mat An image that has gone though thresholding.
 */
void FiducialFinder::searchForContours(Mat thresh)
{
  vector<vector<Point> > contours; //Destination vector for the list of contours in the image
  vector<Vec4i> hierarchy; //Destination vector for hierarchial organization oft he contours
  Mat drawing = Mat::zeros(thresh.size(), CV_8UC3); //Destination matrix for the image contours

  //Find the contours of the image
  findContours( thresh, contours, hierarchy,
                CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );

  //Draw contours
  for( int i = 0; i< contours.size(); i++ )
    {
      Scalar color = Scalar(255,255,255);
      drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }

  cvtColor(drawing, drawing, CV_BGR2GRAY);
  imshow("Contours", drawing);
  waitKey(0);

  
  findBlobs(drawing); 
}

/** Searchs for blobs in an image and returns the farthest left blob fits the size description of a needle
 * @param diff Mat a binary image with contours highlighted
 * @return centroidPoint vector The location of the needle tip's centroid in (x,y) coordinates of the image space.
 */
void FiducialFinder::findBlobs(Mat diff)
{ 
  //Find the blobs in the image
  IplImage diffIpl = diff; //Convert the image Mat into an IPL header                                                     
  IplImage *label = cvCreateImage(cvSize(diffIpl.width,diffIpl.height), IPL_DEPTH_LABEL, 1);


  cvb::CvBlobs blobs;
  unsigned int result = cvb::cvLabel(&diffIpl, label, blobs); //make a label                                               \

  IplImage *blobIplPtr = cvCreateImage(cvSize(diffIpl.width, diffIpl.height),IPL_DEPTH_8U,3);

  cvb::cvFilterByArea(blobs, 180 ,185);
  cvb::cvRenderBlobs(label, blobs, &diffIpl, blobIplPtr);


  vector <double> centroidPoint(2);

  cvb::CvBlobs::const_iterator it = blobs.begin();
  centroidPoint[0] = it->second->centroid.x;
  centroidPoint[1] = it->second->centroid.y;


  for (cvb::CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
    {

      std::cout << "Blob #" << it->second->label << ": Area=" << it->second->area << ", Centroid=(" << it->second->centroid \
	.x << ", " << it->second->centroid.y << ")" << std::endl;
    }
  

  cvNamedWindow("Blobs", CV_WINDOW_AUTOSIZE);
  cvShowImage("Blobs", blobIplPtr);
  cvWaitKey(0);
  

  std::cout << "The values are:";
  for(int i = 0; i < centroidPoint.size(); i++)
    {
      std::cout << " " << centroidPoint[i];
    }
  std::cout << std::endl;

  Point2f centroid(centroidPoint[0], centroidPoint[1]);

  setCentroid(centroid);

}


/** Test the needle detection algorithm using a camera.
 * @param None:
 * @return integer indicating success or failure 
 */
int FiducialFinderTestCamera()
{


  //Start the cameras
  PGRStereoCamera camera("stereo configuration.yml",StereoCameraModel::RECTIFY,false);
  
  stereoImage image;
  Mat left = image[0];
  Mat right = image[1];

  camera.refresh(image);

  FiducialFinder n(image[0]);
  n.beginSearch();
  Point2f centroid0 = n.getCentroid();

  //Find the needle tip in the second image
  FiducialFinder o(image[1]);
  o.beginSearch();
  Point2f centroid1 = o.getCentroid();
  
  //Get 3D Location
  stereoCorrespondence exitPoint2d;
  exitPoint2d.left = centroid0;
  exitPoint2d.right = centroid1;

  StereoCameraModel modelImage;
  Point3f location = modelImage.deproject(exitPoint2d);



  return 0;
}


/** Test the needle detection algorithm using a saved image.
 * @param None:
 * @return integer indicating success or failure 
 */
int FiducialFinderTestImage()
{


  //Load the images
  Mat image0 = imread("fakeLeft.ppm");
  if(!image0.data)
    {
      printf("Could not the first image\n");
      return -1;
    }

  Mat image1 = imread("fakeRight.ppm");
  if(!image1.data)
    {
      printf("Could not the second image\n");
      return -1;
    }



  //Find the needle tip in the first image
  FiducialFinder n(image0);
  n.beginSearch();
  Point2f centroid0 = n.getCentroid();

  //Find the needle tip in the second image
  FiducialFinder o(image0);
  o.beginSearch();
  Point2f centroid1 = o.getCentroid();
  
  //Get 3D Location
  stereoCorrespondence exitPoint2d;
  exitPoint2d.left = centroid0;
  exitPoint2d.right = centroid1;

  StereoCameraModel modelImage;
  Point3f location = modelImage.deproject(exitPoint2d);



  return 0;
}
