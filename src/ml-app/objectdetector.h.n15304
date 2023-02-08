#ifndef HUMANDETECTOR_H
#define HUMANDETECTOR_H

#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <fstream>
#include <iostream>
#include <QDir>

#include "detector.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

enum ClassName {Human,Bicycle,Cat,Dog,Car,Vehicle,Apple};

class ObjectDetector : public Detector
{
public:
    ObjectDetector();
    ~ObjectDetector() ;
    QImage detect(QString image_path) ;
    void SetClassName (ClassName class_name) ;

private:
    void postprocess(Mat& frame, const std::vector<Mat>& outs,float confThreshold) ;
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame,Scalar color ) ;
    std::vector<String> getOutputsNames(const Net& net) ;
    ClassName class_name;
    Net net ;
    std::vector<std::string> classes;


};

#endif // HUMANDETECTOR_H
