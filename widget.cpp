#include "widget.h"
#include "createtask.h"
#include "qdebug.h"


enum class TaskStatus {
    Current,
    Next,
    Future,
    completed
};

QList<TaskModelClass*> Widget::TaskModelClassContainerList;
QList<TaskModelClass*> Widget::TaskModelFliterContainerList;
//QList<TaskModelClass*> TaskModelClassContainerList;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    ProjectMainLayout = new QVBoxLayout;
    //    ProjectMainLayout->setContentsMargins(20,20,20,20);
    ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->setContentsMargins(0,0,0,0);
    containerWidget->setLayout(containerLayout);

    QHBoxLayout * search_layout = new QHBoxLayout();
    QLabel * search_icon = new QLabel("search");
    QLineEdit * search_lineedit = new QLineEdit();
    // search_lineedit->setFocusPolicy(Qt::NoFocus);
    filter_btn = new QPushButton("filter",this);

    overlayWidget = new QWidget();

    // mainLayout = new QVBoxLayout();
    QVBoxLayout *overlayLayout = new QVBoxLayout(overlayWidget);
    overlayLayout->setContentsMargins(0,0,0,0);

    //projects btn
    QPushButton * projects_btn = new QPushButton();
    QHBoxLayout * projectsLayout = new QHBoxLayout();
    projectsLayout->setContentsMargins(0,0,0,0);
    QLabel * point_icon = new QLabel();
    QPixmap point("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-dot-20.png");
    point_icon->setPixmap(point);
    point_icon->setFixedSize(20,20);
    QLabel * projects_label = new QLabel("Projects");
    QLabel * down_arrow_icon = new QLabel();
    QPixmap down_arrow("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-expand-arrow-18.png");
    down_arrow_icon->setFixedSize(20,20);
    down_arrow_icon->setPixmap(down_arrow);

    QWidget * projects_widget = new QWidget();
    QVBoxLayout * projects_display_layout = new QVBoxLayout();
    QPushButton * defaultbtn = new QPushButton("Default");
    defaultbtn->setFlat(true);

    projects_display_layout->setContentsMargins(0,0,0,0);
    projects_display_layout->addWidget(defaultbtn);

    projects_widget->setLayout(projects_display_layout);
    projects_widget->setVisible(false);

    //folders btn
    QPushButton * folders_btn = new QPushButton();
    QHBoxLayout * foldersLayout = new QHBoxLayout();
    foldersLayout->setContentsMargins(0,0,0,0);
    QLabel * point_icon2 = new QLabel();
    point_icon2->setPixmap(point);
    point_icon2->setFixedSize(20,20);
    QLabel * folders_label = new QLabel("Folder");
    QLabel * down_arrow_icon2 = new QLabel();
    down_arrow_icon2->setFixedSize(20,20);
    down_arrow_icon2->setPixmap(down_arrow);

    QWidget * folders_widget = new QWidget();
    QVBoxLayout * folders_display_layout = new QVBoxLayout();

    // current task btn
    QPushButton * current_task_btn = new QPushButton();
    QHBoxLayout * current_task_layout = new QHBoxLayout();
    QLabel * current_task_icon = new QLabel();
    current_task_icon->setFixedSize(24,24);
    QPixmap current_task_pic("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-dot-24.png");
    current_task_icon->setPixmap(current_task_pic);
    QLabel * current_task_label = new QLabel("current task");

    // next task btn
    QPushButton * next_task_btn = new QPushButton();
    QHBoxLayout * next_task_layout = new QHBoxLayout();
    QLabel * next_task_icon = new QLabel();
    next_task_icon->setFixedSize(24,24);
    QPixmap next_task_pic("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-dot-yellow.png");
    next_task_icon->setPixmap(next_task_pic);
    QLabel * next_task_label = new QLabel("next task");

    // future task btn
    QPushButton * future_task_btn = new QPushButton();
    QHBoxLayout * future_task_layout = new QHBoxLayout();
    QLabel * future_task_icon = new QLabel();
    future_task_icon->setFixedSize(24,24);
    QPixmap future_task_pic("");
    future_task_icon->setPixmap(future_task_pic);
    QLabel * future_task_label = new QLabel("future task");

    // completed task btn
    QPushButton * completed_task_btn = new QPushButton();
    QHBoxLayout * completed_task_layout = new QHBoxLayout();
    QLabel * completed_task_icon = new QLabel();
    completed_task_icon->setFixedSize(24,24);
    QPixmap completed_task_pic("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-dot-green.png");
    completed_task_icon->setPixmap(completed_task_pic);
    QLabel * completed_task_label = new QLabel("completed task");

    // setting current task btn
    current_task_layout->addWidget(current_task_icon);
    current_task_layout->addWidget(current_task_label);

    current_task_btn->setLayout(current_task_layout);
    current_task_btn->setFlat(true);

    folders_display_layout->addWidget(current_task_btn);

    // setting next task btn
    next_task_layout->addWidget(next_task_icon);
    next_task_layout->addWidget(next_task_label);

    next_task_btn->setLayout(next_task_layout);
    next_task_btn->setFlat(true);

    folders_display_layout->addWidget(next_task_btn);


    // setting future task btn
    future_task_layout->addWidget(future_task_icon);
    future_task_layout->addWidget(future_task_label);

    future_task_btn->setLayout(future_task_layout);
    future_task_btn->setFlat(true);

    folders_display_layout->addWidget(future_task_btn);


    // setting completed task btn
    completed_task_layout->addWidget(completed_task_icon);
    completed_task_layout->addWidget(completed_task_label);

    completed_task_btn->setLayout(completed_task_layout);
    completed_task_btn->setFlat(true);

    folders_display_layout->addWidget(completed_task_btn);

    folders_display_layout->setContentsMargins(0,0,0,0);
    folders_widget->setLayout(folders_display_layout);
    folders_widget->setVisible(false);

    // setting projects layout
    projectsLayout->addWidget(point_icon);
    projectsLayout->addWidget(projects_label);
    projectsLayout->addWidget(down_arrow_icon);

    // setting folders layout
    foldersLayout->addWidget(point_icon2);
    foldersLayout->addWidget(folders_label);
    foldersLayout->addWidget(down_arrow_icon2);

    projects_btn->setLayout(projectsLayout);
    projects_btn->setFlat(true);
    folders_btn->setLayout(foldersLayout);
    folders_btn->setFlat(true);

    // setting overlayLayout
    overlayLayout->addWidget(projects_btn);
    overlayLayout->addWidget(projects_widget);
    overlayLayout->addWidget(folders_btn);
    overlayLayout->addWidget(folders_widget);
    // overlayLayout->addStretch();

    overlayWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    overlayWidget->setFixedWidth(140);
    overlayWidget->setAutoFillBackground(true);
    overlayWidget->setLayout(overlayLayout);
    overlayWidget->setStyleSheet("QWidget { background-color: #FE4F29 ; color: white; }");
    overlayWidget->setVisible(false);

    QLabel *headingLabel = new QLabel("Task List",this);
    QFont boldFont("Sans Serif",14) ;
    headingLabel->setStyleSheet("color: #e6acac;");
    headingLabel->setFont(boldFont);
    headingLabel->setContentsMargins(2, 2, 2, 2);

    networkManager =  MyNetworkManager::instance();;


//    networkManager->testslot();

//    CreateTask *createTaskObj =  new CreateTask();

    refreshbtn = new QPushButton("Refresh",this);
//    updatebtn = new QPushButton("updatebtn",this);


    connect(networkManager, &MyNetworkManager::projectDataFetched, this, &Widget::onProjectDataFetched);
    connect(networkManager, &MyNetworkManager::taskDataFetched, this, &Widget::onTaskDataFetched);
    connect(networkManager, &MyNetworkManager::sendingTasksFromAPIdataSignal, this, &Widget::onsendingTasksFromAPIdata);
    connect(networkManager, &MyNetworkManager::deleteConfigurationsignal, this,[this](){
        deleteConfiguration();
    });
    connect(networkManager, &MyNetworkManager::initConfigurationsignal, this,[this](){
        initConfiguration();
    });
    connect(refreshbtn, &QPushButton::clicked, this,[this](){
        networkManager->fetchTasksForMobileList(token,10);
    });

//    QSpacerItem *spacer = new QSpacerItem(10,5);

//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");
//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

    search_layout->addWidget(search_icon);
    search_layout->addWidget(search_lineedit);
    search_layout->addWidget(filter_btn);
    search_layout->addWidget(refreshbtn);

    ProjectMainLayout->addLayout(search_layout);
    ProjectMainLayout->addWidget(headingLabel);
//    ProjectMainLayout->addWidget(refreshbtn);


    scrollArea = new QScrollArea(this);
    scrollArea->setContentsMargins(0,0,0,0);
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true); //    scrollArea->setFixedSize(630,400); // Adjust size dk



    QList<ProjectCustomWidget *> customWidgets = containerWidget->findChildren<ProjectCustomWidget *>();
    for (ProjectCustomWidget *widget : customWidgets) {
        // Check if the widget is selected
        QPushButton *pushbtn = widget->findChild<QPushButton *>();
        qDebug()<<"pushbtn : "<<pushbtn->text();
        //        if (checkBox && checkBox->isChecked()) {
        //            delete widget;
        //        }
    }

    //    ProjectMainLayout->addWidget(containerWidget);
    ProjectMainLayout->addWidget(scrollArea);


    setLayout(ProjectMainLayout);
    setFixedSize(650,400);

    //signals and slots
    connect(filter_btn, &QPushButton::clicked, this, [=]{
        if (overlayWidget->isHidden()) {
            QPoint buttonPos = filter_btn->mapToGlobal(filter_btn->rect().bottomRight());
            int overlayWidth = overlayWidget->width();
            QPoint overlayPos(buttonPos.x() - overlayWidth, buttonPos.y()+2);
            overlayWidget->move(overlayPos);
            overlayWidget->setVisible(true);
            qDebug() << "overlayWidget->size()" << overlayWidget->size();
        }else{
            overlayWidget->setVisible(false);
        }
    });

    connect(search_lineedit,&QLineEdit::textChanged,this,[=]{
        for(int i=0;i<TasksContainerList.length();i++){
            if(TasksContainerList.at(i)->d_taskNameLabel->text().contains(search_lineedit->text(),Qt::CaseInsensitive)){
                qDebug() << "title starts with "<< search_lineedit->text() << " :" << TasksContainerList.at(i)->d_taskNameLabel->text();
                TasksContainerList.at(i)->setVisible(true);
            }else{
                TasksContainerList.at(i)->setVisible(false);
            }
        }
    });

    connect(projects_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "projects_btn" << "clicked ";
        qDebug() << "overlayWidget->size() in projects" << overlayWidget->size();
        if(projects_widget->isHidden()){
            qDebug() << "is projects visible true ";
            projects_widget->setVisible(true);
            // overlayWidget->setFixedHeight(81);
            // overlayWidget->resize(overlayWidget->width(),250);
        }else{
            qDebug() << "is projects visible false";
            projects_widget->setVisible(false);
            // overlayWidget->setFixedHeight(52);
            // overlayWidget->setFixedHeight(overlayWidget->height() - folders_widget->height());
        }
    });

    connect(folders_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "folders_btn" << "clicked ";
        qDebug() << "overlayWidget->size() in folders" << overlayWidget->size();
        if(folders_widget->isHidden()){
            qDebug() << "is visible true ";
            folders_widget->setVisible(true);
            // overlayWidget->resize(overlayWidget->width(),250);
        }else{
            qDebug() << "is visible false";
            folders_widget->setVisible(false);
            // overlayWidget->setFixedHeight(overlayWidget->height() - folders_widget->height());
        }
    });

    connect(current_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "current_task_btn clicked ";
    });
    connect(next_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "next_task_btn clicked ";
    });
    connect(future_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "future_task_btn clicked ";
    });
    connect(completed_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "completed_task_btn clicked ";
    });
}

Widget::~Widget()
{
}

void Widget::initConfiguration()
{
    //    networkManager->fetchTasksForMobileList(token,10);
    //    qDebug()<<"initConfiguration ProjectCustomWidget adding widget";

    //    QLayoutItem *item;
    //    while ((item = containerLayout->takeAt(0)) != nullptr) {
    //        if (item->widget()) {
    //            delete item->widget();
    //        }
    //        delete item;
    //    }
    //    bool flag = networkManager->fetchTasksForMobileList(token,10);
    if(TasksContainerList.isEmpty()){
        qDebug() << "taskcontainerList is empty";
    }
    for(ProjectCustomWidget *widgetObject : TasksContainerList ){
        qDebug() << "This ProjectCustomWidget  added from TasksContainerList:" << widgetObject;
        containerLayout->addWidget(widgetObject);
    }

    containerLayout->addStretch();


    //    qDeleteAll(TasksContainerList);
    //    TasksContainerList.clear();
    //    customWidgets.clear();

}

void Widget::deleteConfiguration()
{
        qDeleteAll(TasksContainerList);
        TasksContainerList.clear();
//        for(int i=0;i<TasksContainerList.size();i++){
//            delete TasksContainerList[i];
//        }
        for (int i = 0; i < TaskModelClassContainerList.size(); ++i) {
            delete TaskModelClassContainerList[i]; // Delete the object to avoid memory leaks
        }
        TaskModelClassContainerList.clear(); // Clear the list

        for (int i = 0; i < TaskModelFliterContainerList.size(); ++i) {
            delete TaskModelFliterContainerList[i]; // Delete the object to avoid memory leaks
        }
        TaskModelFliterContainerList.clear(); // Clear the list

        qDebug() << "delete all TasksContainerList & TaskModelClassContainerList data";

}

// void Widget::showEvent(QShowEvent *event) {
//     qDebug() << "in event show function";
// }

void Widget::hideEvent(QHideEvent *event) {
    // qDebug() << "in event hide function";
    overlayWidget->setVisible(false);
}

void Widget::moveEvent(QMoveEvent *event)
{
    QPoint buttonPos = filter_btn->mapToGlobal(filter_btn->rect().bottomRight());
    int overlayWidth = overlayWidget->width();
    QPoint overlayPos(buttonPos.x() - overlayWidth, buttonPos.y()+2);
    overlayWidget->move(overlayPos);
}

void Widget::onProjectDataFetched(const QJsonArray &dataArray)
{
    qDebug()<<"widget onprojectsdatafetched slot called" << dataArray;
}

void Widget::onsendingTasksFromAPIdata(const QJsonArray &dataArray)
{
    for (const QJsonValue &value : dataArray) {
        if (value.isObject()) {
            QJsonObject taskObject = value.toObject();
            int status = taskObject["status"].toInt();
            QString id = taskObject["_id"].toString();
            QString title = taskObject["name"].toString();

            QJsonObject folderObject = taskObject["folder_data"].toObject();
            QString folderName = folderObject["name"].toString();
            QString folderId = folderObject["_id"].toString();
//    ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
//    customWidgetTaskdata->receiveData(folderName,projectTitle,title,id);
    //    containerLayout->addWidget(customWidgetTaskdata);

            QJsonObject project_data_Obj = taskObject["project_data"].toObject();
            QString projectTitle = project_data_Obj["title"].toString();
            QString projectId = project_data_Obj["_id"].toString();


            TaskModelClass *task = new TaskModelClass(id, status, title, folderId,
                                                      folderName, projectId, projectTitle);

            TaskModelClassContainerList.append(task);       // for whole data in unfiltered list
            TaskModelFliterContainerList.append(task);    // setting data for the filtered list
        }
    }



    for(int i=0; i< TaskModelClassContainerList.size();++i){
//        TaskModelClass *taskobjdata = TaskModelClassContainerList[i];
        qDebug()<<"task name in the model containser list" << TaskModelClassContainerList[i]->m_taskName;
    }
}

void Widget::onTaskDataFetched()
{

//    for(int i=0; i< TaskModelClassContainerList.size();++i){
//        ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
//        customWidgetTaskdata->receiveData(TaskModelClassContainerList[i]->m_taskFolderName,
//                                          TaskModelClassContainerList[i]->m_taskProjectName,
//                                          TaskModelClassContainerList[i]->m_taskName,
//                                          TaskModelClassContainerList[i]->m_taskid);
//        TasksContainerList.append(customWidgetTaskdata);
//    }


    for(int i=0; i< TaskModelFliterContainerList.size();++i){
        ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
        customWidgetTaskdata->receiveData(TaskModelFliterContainerList[i]->m_taskFolderName,
                                          TaskModelFliterContainerList[i]->m_taskProjectName,
                                          TaskModelFliterContainerList[i]->m_taskName,
                                          TaskModelFliterContainerList[i]->m_taskid);
        TasksContainerList.append(customWidgetTaskdata);
    }

    //    containerLayout->addWidget(customWidgetTaskdata);
}

void Widget::onEmptySignal()
{
qDebug()<<" onEmptySignal";
}
