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


    QString token = "30765ca695d7dbb06b2e77101711097c:f1ab3a8a390bcacd69ad89df5d3130a77e5de779babc6102c9f616eac600cc460237644a69bde909f69ffa23de44c363d68c8d2ef3d7dbd4d7e3c2b639b687e70ae644f8007a40066669b1fd1f615aa786d3abbcafae05bdb0b536194216d0675d4499929b2f1a56578c23dc017e21408011cf3de8d672e2b5055aa4dfd87437146b3246cf2a2aedf4e7ff0db663ed33bfefcdb6878fd95cf225c70154cb07aab869cc51f585654b1004197f222723259cf660f765b2dc9fe0ba96b5486672f77af419d6bc87b3abba776827143c4e59b9e1a1aefdae758fe0cce534c67fdee39774a071aec4047e7619d449d71e86598335e4c3288b5b43701a6457491751523cc32eacac9d851b05d16a6eade16d3c34552b08b5a9d6531739aa66d47dce94";
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
