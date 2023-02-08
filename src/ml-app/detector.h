#ifndef DETECTOR_H
#define DETECTOR_H

#include "QImage"

class Detector
{
public:
    virtual QImage detect(QString image_path) = 0;
    virtual ~Detector() {}
};

#endif // DETECTOR_H
