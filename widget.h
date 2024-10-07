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



    QString token = "bf53e5323d1376b449659f98cde5cffd:bc360e76839ffc4e5b26fc4ce69f3d47668c34affed8cae5d1f6b06c33e63ad910de52edc97583bcec522635acb999a379fbcafa272163a1989fb2f3593bcb77d320fe87c2591bacbbbe567a0de3e90f21b31d7d6d26c40dfff4c157551536cf4ac5954678224b4448c22f33905d9acebde915a21e35e84fbf372e409da26eec5c76470f1a36b0e4d7725ac7b7e85efc1fc4f8a890f7969481352cbed1c65c22bcd30ee6920bd9ed5a5edf7fe89ed176a724a1260731a0831889edc635fb36bf55eb4b7329f08df91754ec7216a2fb2dd080a0948437c723c0fa3834c64409436bd8e67cfbef80969b6e2d5c63941d925262d92d7f0e5f45d3d18378632f34953c1784752426f6f90913be5264f74aac57c78bf17f9fa10575395a0d79e06b46";
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
    QLabel * dkfolders_label;
    QLabel * current_task_label;
    QLabel * dkcurrent_task_label;
    QLabel * next_task_label;
    QLabel * future_task_label;
    QLabel * completed_task_label;
    QWidget * projects_widget;

    QComboBox *dddoverlayWidget;


    void onProjectDataFetched(const QJsonArray &dataArray);
    void onsendingTasksFromAPIdata(const QJsonArray &dataArray);
    void onTaskDataFetched(int count);
private slots:
    void onEmptySignal(); // Test slot for empty signal
    void projectFilterSelect(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);


};
#endif // WIDGET_H
