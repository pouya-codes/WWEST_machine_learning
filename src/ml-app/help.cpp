#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
}

help::~help()
{
    delete ui;
}

void help::on_btn_home_clicked()
{
    close();
}

void help::set_language(language* lang) {
    this->lang=lang ;
    if (lang!=nullptr) {
        ui->textEdit->setText(lang->get_text_about()[0]) ;
    }
}
