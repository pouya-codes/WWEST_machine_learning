#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDirIterator"
#include "QFileDialog"
#include "detectionwindow.h"
#include "help.h"
#include "language.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_start , SIGNAL (released()), this, SLOT (handleStartButton()));
    connect(ui->btn_exit , SIGNAL (released()), this, SLOT (handleExitButton()));
    connect(ui->btn_language, SIGNAL (released()), this, SLOT (handleLanguagesButton()));
    connect(ui->btn_help , SIGNAL (released()), this, SLOT (handleHelpButton()));
    QString setting_path = QApplication::applicationDirPath() + "/settings.ini";
    setting = new QSettings(setting_path, QSettings::IniFormat);

    init_languages() ;
}
void MainWindow::init_languages() {
    lang = new language(setting) ;
    for(comboItem combo : lang->get_languages()){
        ui->comboBox->addItem(combo.icon,combo.title);
    }
    // set selected language
    init_finished = true ;
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(lang->get_selected_lang()));

}

void MainWindow::createWindow()
{
    DetectionWindow * wndw_detection = new DetectionWindow();
    wndw_detection->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    wndw_detection->setWindowModality(Qt::ApplicationModal);
    wndw_detection->set_language(lang);
    wndw_detection->show();
}

void MainWindow::handleStartButton()
{
    this->createWindow();
}

void MainWindow::handleExitButton()
{
    this->close();
}

void MainWindow::handleLanguagesButton()
{
    // TODO
}

void MainWindow::handleHelpButton()
{
    // TODO
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_help_clicked()
{
    help w ; // = new help();

    w.setModal(true);
//    w.setAttribute(Qt::WA_DeleteOnClose);
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.set_language(lang);
    hide();
    w.exec();
    show();
//    w->show();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(init_finished) {
        if (lang->set_selected_lang(arg1)) {
            QStringList button_titles = lang->get_text_main_menu() ;
            ui->label_run->setText( button_titles.at(0));
            ui->label_help->setText( button_titles.at(1));
            ui->label_exit->setText( button_titles.at(2));

        }
        else
            ui->comboBox->setCurrentIndex(ui->comboBox->findText(lang->get_selected_lang()));

    }

}
