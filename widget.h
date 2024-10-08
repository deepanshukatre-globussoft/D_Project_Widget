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



    QString token = "b1f5cbe8d7ec66f41271fcb683cc62f5:eaef53a051d0856eca0015bc82667377e9464620ff02e4587959e98c35c7bf5fb6f8813349b17f5c20d61c14330d076f7ef3d149229e4ec0654a4b037d4e5c09baa41efe16dfb0c26379aefdb43f084cb2703a35874a1defb069d4e1d37ecd5266a1d5111e2ce071a18184ea6a98c08f56285a49b4d90615641af2aaf15aa343c4ac65fa06f7de24ff4bbea42b4285ed79369172e84acb63d9eacb3ebbaffe027d986e5901a3430aafd8803d335097bc752528090e86221db9d10f12594f13e8044ad68b0e036c75217fbd9ce5aab6a9231511d3910f6a57fb5e143a516e21a4ef9b22cc6ec2329d891b011ba5ecf260dad662888995648b422c39efe948ffb32b70400f64baa3b48bebc908202edf8d8af388d768266a3709a3cf83ad3e5599";
    QWidget *overlayWidget;
    QWidget *overlayCreatetaskWidget;

    void initialize_UI_Components();

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
