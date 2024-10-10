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



    QString token = "bba0d6557e361414a6f82a0884dab45c:2be8310172b1513985e41a017c3123ed68a93e89391044afc609e53c65b148e3f6da64eb50086625f13a49733078cfc0bc255a85a73449dde480f989ae0b930bed37978b04e759827ec0e06fdd348afacfe1c5ca00ad68f4d615a4b7098a61d430cb0649ace78eb94e797ea3a8b31ce45595191f3aa725c97daccc3467455950cde682c68a7f48ef9db4cbb6d6d8dd8ce9508561dd818e1e2281101830936f2fe73838246f37e875e2a234e765404f00734881d57d14e0caec3346a6a8dd274824ffa6ec4f88c61656299f785c9d9feb9a6ea479e130c38aced99e43975863a895ff07489d5b86079b6dd3095aa02f7f265085643e74639e0de69c0a10b033e74a74cd2ea3714b4ca0ac1af99992442fdf8acc78f02d0b0246f83f24cbcd09e3";
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
