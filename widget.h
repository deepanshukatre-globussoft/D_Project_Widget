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
    static QList<TaskModelClass*> TaskModelFliterContainerList;
    ~Widget();


public:

    QVBoxLayout *ProjectMainLayout;
    QVBoxLayout *containerLayout;
    QWidget *containerWidget;
    QScrollArea *scrollArea;
    QScrollArea * projectsscrollArea;
    MyNetworkManager *networkManager;


    QList<ProjectCustomWidget *> TasksContainerList ;
    void initConfiguration();
    void deleteConfiguration();
    QString token = "cba094201826bfcac1cfabfd4712a27f:e036145a11c6cabf024e998d9f9953420c4f14c4f139e1de6c1475f38aca1901a44abf9379a2a31853e45747f6b71e9b68ffe6de5efca8e5be88a9500987a7d5e13d7f101110148068e655102b32dfc97821d220c991dc6779cfe10fe243da20da5dc92cae219b0c57039bb1efc2862e2394eb798ac9ea5c038b7795f87826f4af534d53bde1b515660a07b57b6c8785a975b605fc80fdf723959a9627ab6bdb498a94f2d10bbe6bc827d054f46b99dc31bda1fa8f0b6d9503aca9157494b97bad81b1eb9725f4f7eb9681865318a4ef5a9d0f47942e58da47cb2a0c62b35ca957e5f5257ff86e7d19d3acb6fdd2262deeeaf995e644dc6f439f313e33733f9f756b08e49cecbebbad93ce3728d952b1ffeda24a4009fe87dbf540499a35da87";

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
