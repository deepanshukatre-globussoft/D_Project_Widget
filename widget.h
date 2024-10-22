#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include "taskmodelclass.h"
#include <QJsonArray>
#include <QPixmap>
#include <QEvent>
#include <QApplication>
#include <QMouseEvent>
#include "createtask.h"

#include <QList>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    static QList<TaskModelClass*> TaskModelClassContainerList;
    static QList<TaskModelClass*> TaskModelSearchFliterContainerList;
    static QList<TaskModelClass*> TaskModelProjectsFliterContainerList;
    static QList<TaskModelClass*> TaskModelFolderFliterContainerList;
    ~Widget();


public:

    QVBoxLayout *ProjectMainLayout;
    QVBoxLayout *containerLayout;
    QWidget *containerWidget;
    QScrollArea *scrollArea;
    QScrollArea * projectsscrollArea;
    MyNetworkManager *networkManager;


    QList<ProjectCustomWidget *> TasksContainerList ; // this will hold all ui task data
    void initConfiguration();
    void deleteConfiguration();


    QWidget *overlayWidget;
    QString token = "7d5ed83b64b04ffbeb8cab10c1db0bc8:962438eb10e9cfee075799c62bbb0e157bfb3ab145916e4ee46dde10c3dc514710d3ec60624c26d1d4936b53edeb4702ec6f05554bad3a2d9ed6f815622a200a52365abd3681b2cd911de27581c0f41549d77bce15477610770c6a9763b861460340031c09f0d9ef1be661ee48eb6efda0211f5bbe0d25105fc812e57d45ea2bacdb5ea5d2623dc608fa51153af3756835c1ac39f5cb309428593c18140a444d4beb632e94b5be9bdc10c7feca6915e7126a1fd94cdef0b1092e5c099902c8aa177543bf8aeb9aa258d4dcbb234344f96356a02354c4240b03ba735add580647f9898570cb7675f9507d75b4d7db8f5aeb0b4521d39eeb87ead8a0fe3bc863bdbcedb21f7648bf7c86d1826ccaa8cb45712ea15c03bdab78f750e05e3919eacf";
    QWidget *overlayCreatetaskWidget;

    void initialize_UI_Components();
    CreateTask * create_task = nullptr;

protected:
           // void showEvent(QShowEvent  *event) override;
           // void hideEvent(QHideEvent *event) override;
           // void moveEvent(QMoveEvent * event) override;
    // bool eventFilter(QObject *watched, QEvent *event)
    // {
    //     if (watched == searchbar_widget && event->type() == QEvent::Paint) {
    //         QPainter painter(searchbar_widget);
    //         painter.setPen(QPen(QColor(35, 31, 32, 2), 1));
    //         // painter.drawRect(searchbar_widget->rect().adjusted(1,1,-1,-1)); // Adjust for precise borderrgba(35, 31, 32, 0.2)
    //         int radius = 8; // Set the border radius
    //         painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), radius, radius);
    //         return true; // Handle the event
    //     }
    //     return QWidget::eventFilter(watched, event);
    // }


    void mousePressEvent(QMouseEvent *event) override;


private:
    QPushButton *refreshbtn;
    QPushButton *updatebtn;
    QPushButton * filter_btn;
    QWidget * searchbar_widget;
    QPushButton *pro_btn[20];
    QLabel *pro_name[20];
    QLabel * projects_label;
    QLabel * folders_label;
    QLabel * filter_icon;
    QLabel * filter_label;
    QPixmap filter_pic;
    QWidget * folders_widget;
    QLabel * dkfolders_label;
    QLabel * current_task_label;
    QLabel * dkcurrent_task_label;
    QLabel * next_task_label;
    QLabel * future_task_label;
    QLabel * completed_task_label;
    QWidget * projects_widget;

    QComboBox *projectComboBox;



    void onProjectDataFetched(const QJsonArray &dataArray);
    void onsendingTasksFromAPIdata(const QJsonArray &dataArray);
    void onTaskDataFetched(int count);
private slots:
    void onEmptySignal(); // Test slot for empty signal
    void projectFilterSelect(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);


};
#endif // WIDGET_H
