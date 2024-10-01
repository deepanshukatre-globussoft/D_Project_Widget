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


    QList<ProjectCustomWidget *> TasksContainerList ; // this will hold all ui task data
    void initConfiguration();
    void deleteConfiguration();

    QString token = "4e7813545426ef67f6c633d898400185:69ec0fde80c83dbe2ddf02f7fc251ca293407e0753c1340ec8be73da80696381afbb68cb4da30663d6bb101766ba9eee1a933b451f1bbb49ca3ca789df42bc9ed9c8616cd6f6bececf45d715764bb6240811157a656302df2e8f153932309e6c580732f077717b42050110f6070c92c5833106ef0ca808abfc9bde9f98a2f04bfb741a77338d19532222f8bef51b8b7aea8908c0587f134c41f3be43c91c5db4f2a9b043a3b5c6596e1652b3ad145a2dfb9714e2aa8b0310ad5ffd559e6d2e16810f208963c715ec7337e6051d0e9c8dd474efac9579f6c74e71c89b67498e7fe5d1e501634137df6df9d57ec3dc882e2d4d3bde96353dd39241170ce80b6facc344b2a024da9a945a0e3530a44c8f66cd2ba8ab40dbf991ef6c65ea4b96a0db";

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
