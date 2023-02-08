#ifndef DETECTIONWINDOW_H
#define DETECTIONWINDOW_H

#include <QMainWindow>
#include "detectortype.h"
#include "facedetector.h"
#include "objectdetector.h"
#include "language.h"

namespace Ui {
class DetectionWindow;
}

class DetectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    DetectionWindow();
    void set_language(language* lang) ;
    ~DetectionWindow();

private:
    Ui::DetectionWindow *ui;
    language* lang ;

    QStringList text_titles, text_functions;

    int current_image_index = -1;
    QStringList *images_paths;

    DetectorType current_detector_type;
    Detector * current_detector;

    FaceDetector * face_detector;
    ObjectDetector * object_detector;

    void loadNewDirectory();
    QString openChooseDirDialog();
    void loadImagesPaths(QString input_directory);

    void displayNextImage();
    void displayPreviousImage();
    void displayCurrentImage();
    void displayImage(QPixmap processed_image);

    void updateUI();
    void updateDetectionButtons();
    void updateNavigationButtons();
    void updateImageDisplayWidgets();
    void set_contain();

private slots:
    void handleLoadDirButton();
    void handleHomeButton();

    void handleFaceDetectionButton();
    void handleHumanDetectionButton();
    void handleBicycleDetectionButton();
    void handleCatDetectionButton();
    void handleDogDetectionButton();
    void handleAppleDetectionButton();
    void handleCarDetectionButton();
    void handleVehicleDetectionButton();

    void handleNextButton();
    void handleBackButton();
    void on_btn_home_3_clicked();
    void on_btn_open_dir_2_clicked();
};
#endif // DETECTIONWINDOW_H
