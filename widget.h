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

    QString token = "f8a0b2386437b16f779142b19cdd9f56:c98860891d4885096e1ce9c1bde477d9f6601c606d4acf15544caa2807a3e1f46ebf72b114ab415562e066d2d70747fc33ba10fa529132678969b4c130847e8b21f700207516f9588958f1546e4ca4870db959b69a81bfa2da9be19370c0d68f4a9e0790afaa6d2440429e8395b428c67f48434ef787166736523e315f4652ec1d896aa973963bb0d88b2f09251fece60f4899f561aac579d3babd4c778724af9c62499a8974700afdd7e3a28c7a9a59d3cd2e623ccd29a5d714bc3fce98c35de36825c0b491c80b085e98d192c50d129e98e84ca555bdb7fbad744e5190c7f2103a0fffd4eebe41ce7721d5165a82e25b8a82010c40fad33e7ae2f70c2576c78cfbb9963e655a222ef23e232cd611ce4e2af72b320ab15103251fbbb949aedf";
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
