#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include <QJsonArray>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    QVBoxLayout *ProjectMainLayout;
    QVBoxLayout *containerLayout;
    QWidget *containerWidget;
    QScrollArea *scrollArea;
    MyNetworkManager *networkManager;

private:
        void onProjectDataFetched(const QJsonArray &dataArray);
private slots:
        void onEmptySignal(); // Test slot for empty signal
};
#endif // WIDGET_H
