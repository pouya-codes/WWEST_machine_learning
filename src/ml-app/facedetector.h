#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QDir"

#include "detector.h"

using namespace std;
using namespace cv;

class FaceDetector : public Detector
{
public:
    FaceDetector();
    ~FaceDetector();
    QImage detect(QString image_path);
private:
    CascadeClassifier face_cascade;
};

#endif // FACEDETECTOR_H
