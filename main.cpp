#include "createtask.h"
#include "widget.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("://myqss.qss");

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString stylesheet = stream.readAll();
        a.setStyleSheet(stylesheet);
    }

    Widget w;
    w.show();
//    CreateTask createTaskObj;
//    createTaskObj.show();
    return a.exec();
}
