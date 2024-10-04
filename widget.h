#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include "taskmodelclass.h"
#include <QJsonArray>
#include <QPixmap>
#include <QEvent>
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


    QString token = "6b52374aa22159ebd0c6da2292b4be41:6e8e67545005fb408234c632323e925a986ecbaed7e6a867d2466319c5b179144e51590c7a64c7086d5ec1dca39f8d9b21c7cc8d288da1648c3d40fbeae553c2ea737500e819b83fc94de770766e03111fd8aca541b262ca0a816faec8e069d2ee0a76737f0429942f0bd56142f0cbb1102dca0c400637db6edff0ff6ac7bf4ce52ca1d4f0c740f869ed1755ee7553c15c5317f9ca4702e01d0952a0dcd106c318f53096afa7b6fb6b62c7dd959e8f5c6951319d40f8c6a403aa8a879a3df1b2211d68261491e1f1719897190011c57a7d16346f76e71e7e9391637afb6cabad57a092f42e366193c97034e3d25f2cac7579e0f837ca884bc979cec64d821144025471ee5515b39d87160c4c0604650746c97486434f1228ee9555657b90575e";
    QWidget *overlayWidget;
    QWidget *overlayCreatetaskWidget;

protected:
    // void showEvent(QShowEvent  *event) override;
    // void hideEvent(QHideEvent *event) override;
    // void moveEvent(QMoveEvent * event) override;

private:
    QPushButton *refreshbtn;
    QPushButton *updatebtn;
    QPushButton * filter_btn;
    QWidget * searchbar_widget;
    QPushButton *pro_btn[20];
    QLabel *pro_name[20];
    QLabel * projects_label;
    QLabel * folders_label;
    QLabel * current_task_label;
    QLabel * next_task_label;
    QLabel * future_task_label;
    QLabel * completed_task_label;
    QWidget * projects_widget;

    void onProjectDataFetched(const QJsonArray &dataArray);
    void onsendingTasksFromAPIdata(const QJsonArray &dataArray);
    void onTaskDataFetched(int count);
private slots:
    void onEmptySignal(); // Test slot for empty signal
    void projectFilterSelect(int index);


};
#endif // WIDGET_H
