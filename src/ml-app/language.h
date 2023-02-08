#ifndef LANGUAGE_H
#define LANGUAGE_H
#include "QIcon"
#include "QString"
#include <QVector>
#include <QLocale>
#include <QDir>
#include <QMessageBox>
#include "QXmlStreamReader"
#include <QTextCodec>
#include <QDebug>
#include <QSettings>

struct comboItem {
    QString title ;
    QIcon icon ;
};

class language
{
private:
    QString LANGUAGE_KEY = "language";
    QSettings* settings;
    QString selected_lang ;
    QVector<comboItem> languages ;
    QStringList text_main_menu;
    QStringList text_help;
    QStringList text_functions;
    QStringList text_titles;
    QStringList text_about;
public:
    void set_setting(QSettings* setting) ;
    QString get_selected_lang() ;
    bool set_selected_lang(QString lang) ;
    language(QSettings* setting) ;
    language();
    QVector<comboItem> get_languages();
    bool read_xml(QString lang) ;
    QStringList get_text_main_menu() ;
    QStringList get_text_help() ;
    QStringList get_text_functions() ;
    QStringList get_text_titles() ;
    QStringList get_text_about();
};

#endif // LANGUAGE_H
