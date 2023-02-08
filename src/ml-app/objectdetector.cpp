#include "objectdetector.h"

ObjectDetector::ObjectDetector()
{

    // Load YOLO model.
    QString modelConfiguration = QDir::currentPath() +"/data/models/yolov3-tiny.cfg" ;
    QString modelBinary = QDir::currentPath() +"/data/models/yolov3-tiny.weights" ;
    QString classNames = QDir::currentPath() +"/data/models/coco.names" ;

//    QString modelConfiguration = "D:/data/models/yolov3-tiny.cfg" ;
//    QString modelBinary = "D:/data/models/yolov3-tiny.weights" ;
//    QString classNames = "D:/data/models/coco.names" ;

    net = readNetFromDarknet(modelConfiguration.toStdString(), modelBinary.toStdString());

    // Open file with classes names.
    string file = classNames.toStdString();
    std::ifstream ifs(file.c_str());
    if (!ifs.is_open())
        CV_Error(Error::StsError, "File " + file + " not found");
    std::string line;
    while (std::getline(ifs, line))
    {
        classes.push_back(line);
    }

}
void ObjectDetector::SetClassName (ClassName class_name) {
    this->class_name = class_name ;

}

QImage ObjectDetector::detect(QString image_path) {

    cv::Mat frame = cv::imread(image_path.toStdString()) ;
    Mat inputBlob = blobFromImage(frame, 1 / 255.F , Size(416, 416), Scalar(), true, false); //Convert Mat to batch of images
    net.setInput(inputBlob, "data");                   //set the network input
    std::vector<Mat> outs;
    net.forward(outs, getOutputsNames(net));  //compute output
    postprocess(frame, outs,0.3);

    QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    return image.rgbSwapped();
}

ObjectDetector::~ObjectDetector(){
    net.~Net();
}

void ObjectDetector::drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame,Scalar color )
{
    rectangle(frame, Point(left, top), Point(right, bottom), color,2);

        std::string label = format("%.2f", conf);
        if (!classes.empty())
        {
            CV_Assert(classId < (int)classes.size());
            label = classes[classId] + ": " + label;
        }

        int baseLine;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

        top = max(top, labelSize.height);
        rectangle(frame, Point(left, top - labelSize.height),Point(left + labelSize.width, top + baseLine), Scalar::all(255) , FILLED);
        putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.5, Scalar());
}

std::vector<String> ObjectDetector::getOutputsNames(const Net& net)
{
    static std::vector<String> names;
    if (names.empty())
    {
        std::vector<int> outLayers = net.getUnconnectedOutLayers();
        std::vector<String> layersNames = net.getLayerNames();
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}


void ObjectDetector::postprocess(Mat& frame, const std::vector<Mat>& outs,float confThreshold)
{
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<Rect> boxes;
    for (size_t i = 0; i < outs.size(); ++i)
    {
        // Network produces output blob with a shape NxC where N is a number of
        // detected objects and C is a number of classes + 4 where the first 4
        // numbers are [center_x, center_y, width, height]
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold )
            {
                switch (this->class_name) {
                case Human:
                    if(classIdPoint.x!=0)
                        continue ;
                    break;
                case Bicycle:
                    if(classIdPoint.x!=1)
                        continue ;
                    break;
                case Cat:
                    if(classIdPoint.x!=15)
                        continue ;
                    break;
                case Dog:
                    if(classIdPoint.x!=16)
                        continue ;
                    break;
                case Car:
                    if(classIdPoint.x!=2 && classIdPoint.x!=5)
                        continue ;
                    break;
                case Vehicle:
                    if(classIdPoint.x!=2 && classIdPoint.x!=5 && classIdPoint.x!=7)
                        continue ;
                    break;
                case Apple:
                    if(classIdPoint.x!=47)
                        continue ;
                    break;
                default:
                    continue ;
                    break;
                }
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
    }
    std::vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, 0.4f, indices);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame , Scalar(0,255,0));
    }


}
