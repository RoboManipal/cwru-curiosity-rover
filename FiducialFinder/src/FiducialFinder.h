/*FiducialFinder.h

 *Author: Eddie E. Massey III
 *A class to determine the location of a fiducial
 *This class finds a fiducial in a single image
 *FiducialFinder f(inputImage);
 *f.beginSearch();
 *
 */

#include <opencv2/core/core.hpp>


using namespace cv;

class FiducialFinder {
 public:

  FiducialFinder(Mat image);         // constructor; initialize with a Mat
  Mat getImage();              // return the original image
  Point2f getCentroid(); //Centroid of the needle exit
  void setCentroid(Point2f centroid);
  void beginSearch(); //find the location of the needle
  void searchForContours(Mat thresh);
  void findBlobs(Mat diff);


 private:
  Mat image;
  Point2f centroid;

  

};





int FiducialFinderTestCamera();
int FiducialFinderTestImage();

