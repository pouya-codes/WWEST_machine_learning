#include "language.h"

language::language()
{

}

language::language(QSettings* setting)
{
    this->settings=setting ;



    // get system default language
    //    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    //    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"

    // search for language
    QString langPath = "data/languages" ;
    QDir dir(langPath);
    QStringList fileNames = dir.entryList(QStringList("*.xml"));

    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i];
        locale.truncate(locale.lastIndexOf('.')); // "en"
        QIcon icon(QString("%1/%2.png").arg(langPath).arg(locale));  // "en.png"
        languages.append(comboItem{locale,icon});
        // set program language to system default langauge
        //        if(locale==defaultLocale && selected_lang=="")
        //            set_selected_lang(locale) ;
    }
    selected_lang = settings->value(LANGUAGE_KEY,"en").toString() ;

    set_selected_lang(selected_lang) ;

}

QString language::get_selected_lang() {
    return selected_lang ;
}
bool language::set_selected_lang(QString lang) {
    if (read_xml(lang)){
        selected_lang = lang ;
        settings->setValue(LANGUAGE_KEY,lang);
        return true ;
    }
    return false ;

}

QVector<comboItem> language::get_languages(){
    return languages;
}
bool language::read_xml(QString lang) {
    //clear all StringLists
    text_main_menu.clear();
    text_help.clear();
    text_functions.clear();
    text_titles.clear();
    text_about.clear();

    //open xml file
    QFile* xmlFile ;
    xmlFile = new QFile(QString("data/languages/%1.xml").arg(lang));
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QXmlStreamReader* xmlReader ;
    xmlReader = new QXmlStreamReader(xmlFile);



    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();

        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }

        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {
            if( xmlReader->name() != "translates" &&  xmlReader->name()!="help" &&  xmlReader->name()!="menu" &&  xmlReader->name()!="functions" &&  xmlReader->name()!="titles" &&  xmlReader->name()!="abouts" ) {
                if(xmlReader->name().contains("help_"))
                    text_help.append(xmlReader->readElementText());
                else if (xmlReader->name().contains("menu_"))
                    text_main_menu.append(xmlReader->readElementText());
                else if (xmlReader->name().contains("function_"))
                    text_functions.append(xmlReader->readElementText());
                else if (xmlReader->name().contains("title_"))
                    text_titles.append(xmlReader->readElementText());
                else if (xmlReader->name().contains("about_"))
                    text_about.append(xmlReader->readElementText());
                else
                    qDebug() << "wrong xml tag in " << QString("data/languages/%1.xml").arg(selected_lang) ;
            }
        }
    }
    if (text_main_menu.length()!=4 || text_functions.length()!=8 || text_help.length()!=9 || text_titles.length()!=5 || text_about.length()!=1){
        qDebug() << "wrong number of tags in " << QString("data/languages/%1.xml").arg(lang) ;
        return false ;
    }


    if(xmlReader->hasError()) {
        qDebug() << xmlReader->errorString() ;
        return false;
    }

    //close reader and flush file
    xmlReader->clear();
    xmlFile->close();
}

QStringList language::get_text_main_menu() {
    return text_main_menu ;
}

QStringList language::get_text_help() {
    return text_help ;
}

QStringList language::get_text_functions() {
    return text_functions ;
}
QStringList language::get_text_titles() {
    return text_titles ;
}
QStringList language::get_text_about() {
    return text_about ;
}


void language::set_setting(QSettings *setting) {
    this->settings = setting ;
}





