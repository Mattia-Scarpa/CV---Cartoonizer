#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat cartoonify(Mat image, int arguments=0){

    Mat cartoonImage, greyImg, preserveImg, detailImg, edgeImg;

    edgePreservingFilter(image, cartoonImage, NORMCONV_FILTER, 60, 0.14);
    cvtColor(cartoonImage, greyImg, COLOR_BGR2GRAY);

    Laplacian(greyImg, edgeImg, CV_8U, 5);
    threshold(edgeImg, edgeImg, 70, 255, THRESH_BINARY);
    cartoonImage.setTo(0, edgeImg);

    waitKey(0);

    return cartoonImage;
}

Mat pencilSketch(Mat image, int arguments=0) {

    Mat pencilSketchImage, greyImg, preserveImg, detailImg, edgeImg;

    edgePreservingFilter(image, pencilSketchImage, NORMCONV_FILTER, 60, 0.14);
    cvtColor(pencilSketchImage, greyImg, COLOR_BGR2GRAY);

    Laplacian(greyImg, edgeImg, CV_8U, 5);
    threshold(edgeImg, edgeImg, 70, 255, THRESH_BINARY);

    bitwise_not(edgeImg, pencilSketchImage);
    return pencilSketchImage;
}


int main(int argc, char const *argv[]) {

  string imagePath = "./trump.jpg";
  Mat image = imread(imagePath);
  //imshow("test", image);
  //waitKey();


  Mat cartoonImage = cartoonify(image);
  Mat pencilSketchImage = pencilSketch(image);

  imshow("cartoonImage", cartoonImage);
  imshow("pencilSketchImage", pencilSketchImage);
  waitKey();
  return 0;
}
