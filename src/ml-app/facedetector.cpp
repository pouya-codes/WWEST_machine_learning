#include "facedetector.h"
#include "qdebug.h"

FaceDetector::FaceDetector()
{
    QString cascade_path = QDir::currentPath() +"/data/models/haarcascade_frontalface_alt.xml";
    qDebug() << cascade_path ;
    if(!face_cascade.load(cascade_path.toStdString()))
    {
        printf("Error loading face cascade!\n");
        throw new Exception();
    }
}

QImage FaceDetector::detect(QString image_path)
{
    std::vector<Rect> faces;
    Mat frame_gray, frame;

    // Load and normalize image
    frame = cv::imread(image_path.toStdString()) ;
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect Faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

    // Draw Rectangles around faces
    for(size_t i = 0; i < faces.size(); i++)
    {
        rectangle(frame, faces[i], Scalar(255, 0, 255), 2);
    }

    QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    return image.rgbSwapped();
}

FaceDetector::~FaceDetector()
{
    face_cascade.~CascadeClassifier();
}

