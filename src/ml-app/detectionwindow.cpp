#include "detectionwindow.h"
#include "ui_detectionwindow.h"
#include "QDirIterator"
#include "QFileDialog"
#include "QtDebug"

DetectionWindow::DetectionWindow() :
    QMainWindow(nullptr),
    ui(new Ui::DetectionWindow)
{
    ui->setupUi(this);
    this->images_paths = new QStringList();

    this->current_detector = nullptr;
    this->current_detector_type = DetectorType::none;

    this->face_detector = new FaceDetector();
    this->object_detector = new ObjectDetector();

    connect(ui->btn_back , SIGNAL (released()), this, SLOT (handleBackButton()));
    connect(ui->btn_next , SIGNAL (released()), this, SLOT (handleNextButton()));
    connect(ui->btn_open_dir , SIGNAL (released()), this, SLOT (handleLoadDirButton()));
    connect(ui->btn_home , SIGNAL (released()), this, SLOT (handleHomeButton()));

    connect(ui->btn_face_detection , SIGNAL (released()), this, SLOT (handleFaceDetectionButton()));
    connect(ui->btn_human_detection , SIGNAL (released()), this, SLOT (handleHumanDetectionButton()));
    connect(ui->btn_bicycle_detection , SIGNAL (released()), this, SLOT (handleBicycleDetectionButton()));

    connect(ui->btn_cat , SIGNAL (released()), this, SLOT (handleCatDetectionButton()));
    connect(ui->btn_dog , SIGNAL (released()), this, SLOT (handleDogDetectionButton()));
    connect(ui->btn_car , SIGNAL (released()), this, SLOT (handleCarDetectionButton()));
    connect(ui->btn_vehicle , SIGNAL (released()), this, SLOT (handleVehicleDetectionButton()));
    connect(ui->btn_apple , SIGNAL (released()), this, SLOT (handleAppleDetectionButton()));
}

void DetectionWindow::loadNewDirectory()
{
    QString input_directory = openChooseDirDialog();
    if ( input_directory.size() > 0 )
    {
        this->current_image_index = -1;
        loadImagesPaths(input_directory);
        this->displayNextImage();
    }
}

QString DetectionWindow::openChooseDirDialog()
{
    QString input_directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 QDir::currentPath(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    return input_directory;
}

void DetectionWindow::loadImagesPaths(QString input_directory)
{
    this->images_paths = new QStringList();
    QStringList image_file_extensions = { "*.jpg", "*.jpeg", "*.png" };
    QDirIterator images_paths_iterator(input_directory, image_file_extensions, QDir::Files, QDirIterator::Subdirectories);
    while (images_paths_iterator.hasNext())
        this->images_paths->append(images_paths_iterator.next());
}

void DetectionWindow::displayNextImage()
{
    this->current_image_index++;
    this->updateUI();
}

void DetectionWindow::displayPreviousImage()
{
    this->current_image_index--;
    this->updateUI();
}

void DetectionWindow::displayCurrentImage()
{
    if (this->current_image_index >= 0 && this->current_image_index < this->images_paths->size())
    {
        QString image_path = this->images_paths->at(this->current_image_index);
        QPixmap processed_image;
        if (this->current_detector_type == DetectorType::none)
        {
            QImage  *image = new QImage();
            image->load(image_path);
            processed_image = QPixmap::fromImage(*image);
        }
        else
        {
            processed_image = QPixmap::fromImage(this->current_detector->detect(image_path));
        }
        displayImage(processed_image);
    }
}

void DetectionWindow::displayImage(QPixmap processed_image)
{
    processed_image = processed_image.scaled(ui->graphics_view->width()-5, ui->graphics_view->height()-5, Qt::KeepAspectRatio);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(processed_image);
    scene->setSceneRect(processed_image.rect());

    ui->graphics_view->setScene(scene);
}

void DetectionWindow::updateUI()
{
    this->current_detector_type = DetectorType::none;
    this->displayCurrentImage();
    this->updateDetectionButtons();
    this->updateNavigationButtons();
    this->updateImageDisplayWidgets();

    ui->central_widget->repaint();
}

void DetectionWindow::updateDetectionButtons()
{
    bool is_images_loaded = (this->images_paths->size() > 0) ? true : false;
    ui->btn_face_detection->setEnabled(is_images_loaded);
    ui->btn_human_detection->setEnabled(is_images_loaded);
    ui->btn_bicycle_detection->setEnabled(is_images_loaded);

    ui->btn_apple->setEnabled(is_images_loaded);
    ui->btn_car->setEnabled(is_images_loaded);
    ui->btn_cat->setEnabled(is_images_loaded);
    ui->btn_vehicle->setEnabled(is_images_loaded);
    ui->btn_dog->setEnabled(is_images_loaded);
}

void DetectionWindow::updateNavigationButtons()
{
    ui->btn_next->setEnabled((this->current_image_index + 1 < this->images_paths->size()) ? true : false);
    ui->btn_back->setEnabled((this->current_image_index - 1 >= 0) ? true : false);
}

void DetectionWindow::updateImageDisplayWidgets()
{
    bool is_images_loaded = (this->images_paths->size() > 0) ? true : false;

    if (!is_images_loaded)
    {
        ui->graphics_view->setScene(nullptr);
    }
}

void DetectionWindow::handleLoadDirButton()
{
    this->loadNewDirectory();
}

void DetectionWindow::handleHomeButton()
{
    this->close();
}

void DetectionWindow::handleFaceDetectionButton()
{
    this->current_detector_type = DetectorType::face;
    this->current_detector = this->face_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleHumanDetectionButton()
{
    this->current_detector_type = DetectorType::human;
    this->object_detector->SetClassName(Human);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleBicycleDetectionButton()
{
    this->current_detector_type = DetectorType::bicycle;
    this->object_detector->SetClassName(Bicycle);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleCatDetectionButton()
{
    this->current_detector_type = DetectorType::cat;
    this->object_detector->SetClassName(Cat);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleDogDetectionButton()
{
    this->current_detector_type = DetectorType::dog;
    this->object_detector->SetClassName(Dog);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleAppleDetectionButton()
{
    this->current_detector_type = DetectorType::apple;
    this->object_detector->SetClassName(Apple);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleCarDetectionButton()
{
    this->current_detector_type = DetectorType::car;
    this->object_detector->SetClassName(Car);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}

void DetectionWindow::handleVehicleDetectionButton()
{
    this->current_detector_type = DetectorType::vehicle;
    this->object_detector->SetClassName(Vehicle);
    this->current_detector = this->object_detector;
    displayCurrentImage();
    ui->central_widget->repaint();
}


void DetectionWindow::handleNextButton()
{
    this->displayNextImage();
}

void DetectionWindow::handleBackButton()
{
    this->displayPreviousImage();
}

DetectionWindow::~DetectionWindow()
{
    delete current_detector;
    delete ui;
}

void DetectionWindow::on_btn_home_3_clicked()
{
    close() ;
}

void DetectionWindow::on_btn_open_dir_2_clicked()
{
    handleLoadDirButton() ;
}
void DetectionWindow::set_language(language* lang) {
    this->lang=lang ;
    this->text_functions = lang->get_text_functions() ;
    this->text_titles = lang->get_text_titles() ;
    set_contain() ;
//    for(comboItem combo : lang->get_languages()){
//        ui_->comboBox_language->addItem(combo.icon,combo.title);
//    }
//    init_finished = true ;
//    // set selected language
//    ui_->comboBox_language->setCurrentIndex(ui_->comboBox_language->findText(lang->get_selected_lang()));

}
void DetectionWindow::set_contain() {

    ui->label_load->setText(text_titles[0]) ;
    ui->label_home->setText(text_titles[1]) ;
    ui->label_help->setText(text_titles[2]) ;
    ui->label_back->setText(text_titles[3]) ;
    ui->label_next->setText(text_titles[4]) ;

    ui->label_face->setText(text_functions[0]) ;
    ui->label_bicycle->setText(text_functions[1]) ;
    ui->label_person->setText(text_functions[2]) ;
    ui->label_cat->setText(text_functions[3]) ;
    ui->label_dog->setText(text_functions[4]);
    ui->label_apple->setText(text_functions[5]);
    ui->label_car->setText(text_functions[6]);
    ui->label_car_bus->setText(text_functions[7]);

}

