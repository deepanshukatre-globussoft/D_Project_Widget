//#include "createtask.h"
#include "widget.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include <QApplication>
#include <QFontDatabase>
#include<QTranslator>
//#include "reminderwidget.h"
//#include "projectcustomwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
       // translator.load(":/translations/ar.qm");
   // qDebug() << "Loading translation file:" << translator.load(":/translations/ar.qm");

   // qApp->installTranslator(&translator);


    QFile file("://myqss.qss");

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString stylesheet = stream.readAll();
        a.setStyleSheet(stylesheet);
    }

//    QLocale locale = QLocale::system();
//    QString language = locale.name(); qDebug() << language;

//    int id = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Regular.ttf");
//    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
//    QFont ubuntuFont(family);


//    QFontDatabase fontDatabase;
//    int fontId = fontDatabase.addApplicationFont(":/fonts/Ubuntu-Regular.ttf");
//    if (fontId == -1) {
//        qWarning("Failed to load font");
//    } else {
//        QString fontFamily = fontDatabase.applicationFontFamilies(fontId).at(0);
//        QFont font(fontFamily);
////        font.setPointSize(12); // Set the default font size
//        QApplication::setFont(font); // Apply font globally
//    }

    Widget w;
    w.show();

    // CreateTask createTaskObj;
    // createTaskObj.show();

    // ReminderWidget r;
    // r.show();

    // ProjectCustomWidget pro;
    // pro.show();

    return a.exec();
}
