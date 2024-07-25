#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "projectcustomwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QVBoxLayout *ProjectMainLayout;
    QVBoxLayout *containerLayout;
    QWidget *containerWidget;
    QScrollArea *scrollArea;
};
#endif // WIDGET_H
