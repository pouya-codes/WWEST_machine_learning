#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qsettings.h>
#include "language.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSettings* setting ;
    language* lang ;
    bool init_finished = false;

    void createWindow();
    void init_languages() ;

private slots:
    void handleStartButton();
    void handleExitButton();
    void handleLanguagesButton();
    void handleHelpButton();
    void on_btn_help_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
