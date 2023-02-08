#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <language.h>

namespace Ui {
class help;
}

class help : public QDialog
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = 0);
    void set_language(language* lang) ;
    ~help();

private slots:
    void on_btn_home_clicked();


private:
    Ui::help *ui;
    language* lang ;
};

#endif // HELP_H
