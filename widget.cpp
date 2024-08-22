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

    qDebug() << "widget constructor reference " << this;
    ProjectMainLayout = new QVBoxLayout;
    //    ProjectMainLayout->setContentsMargins(20,20,20,20);
    ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    qDebug() << "containerWidget  reference " << containerWidget;
    qDebug() << "containerWidget parent object reference " << containerWidget->parent();
    qDebug() << "containerWidget parent widget reference " << containerWidget->parentWidget();
    containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->setContentsMargins(0,0,5,5);
    containerWidget->setLayout(containerLayout);

    QHBoxLayout * search_layout = new QHBoxLayout();
    QLabel * search_label = new QLabel(this);
    QPixmap search_icon("://imgs/search.svg");
    search_label->setPixmap(search_icon);
    QLineEdit * search_lineedit = new QLineEdit();
    // search_lineedit->setFocusPolicy(Qt::NoFocus);
    search_lineedit->setPlaceholderText("search");

    QHBoxLayout * create_layout = new QHBoxLayout();

    QPushButton * createTaskBtn = new QPushButton(this);
    QIcon create_icon("://imgs/create.svg");
    createTaskBtn->setIcon(create_icon);
    createTaskBtn->setFlat(true);
    createTaskBtn->setFixedSize(30,30);
    createTaskBtn->setIconSize(QSize(30,30));

    create_layout->addWidget(createTaskBtn);
    create_layout->setAlignment(Qt::AlignHCenter);

    filter_btn = new QPushButton(this);
    QHBoxLayout * filter_layout = new QHBoxLayout();
    QLabel * filter_icon = new QLabel();
    QPixmap filter_pic("://imgs/filter.png");
    QLabel * filter_label = new QLabel("Filter",this);

    overlayWidget = new QWidget(this);
    qDebug() << "overlayWidget  reference " << overlayWidget;
    qDebug() << "overlayWidget parent object reference " << overlayWidget->parent();
    qDebug() << "overlayWidget parent widget reference " << overlayWidget->parentWidget();

    // mainLayout = new QVBoxLayout();
    QVBoxLayout *overlayLayout = new QVBoxLayout(overlayWidget);
    overlayLayout->setContentsMargins(0,0,0,0);

    //projects btn
    QPushButton * projects_btn = new QPushButton(overlayWidget);
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
    QPushButton * folders_btn = new QPushButton(overlayWidget);
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
    // current_task_icon->setPixmap(current_task_pic);
    QLabel * current_task_label = new QLabel("current task");

    // next task btn
    QPushButton * next_task_btn = new QPushButton();
    QHBoxLayout * next_task_layout = new QHBoxLayout();
    QLabel * next_task_icon = new QLabel();
    next_task_icon->setFixedSize(24,24);
    QPixmap next_task_pic("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-dot-yellow.png");
    // next_task_icon->setPixmap(next_task_pic);
    QLabel * next_task_label = new QLabel("next task");

    // future task btn
    QPushButton * future_task_btn = new QPushButton();
    QHBoxLayout * future_task_layout = new QHBoxLayout();
    QLabel * future_task_icon = new QLabel();
    future_task_icon->setFixedSize(24,24);
    QPixmap future_task_pic("");
    // future_task_icon->setPixmap(future_task_pic);
    QLabel * future_task_label = new QLabel("future task");

    // completed task btn
    QPushButton * completed_task_btn = new QPushButton();
    QHBoxLayout * completed_task_layout = new QHBoxLayout();
    QLabel * completed_task_icon = new QLabel();
    completed_task_icon->setFixedSize(24,24);
    QPixmap completed_task_pic("C:/Users/GLB-BLR-304/Documents/GitHub/images/icons8-dot-green.png");
    // completed_task_icon->setPixmap(completed_task_pic);
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
    // overlayLayout->addStretch();
    overlayLayout->addWidget(folders_btn);
    overlayLayout->addWidget(folders_widget);

    // setting overlayWidget
    overlayWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    overlayWidget->setFixedSize(140,50);
    overlayWidget->move(434,52);
    overlayWidget->setAutoFillBackground(true);
    overlayWidget->setLayout(overlayLayout);
    overlayWidget->setStyleSheet("QWidget { background-color: #D2232A ; color: white; }");
    overlayWidget->setVisible(false);
    // overlayWidget->setFixedSize(150,300);

    // QLabel *headingLabel = new QLabel("Task List",this);
    // QFont boldFont("Sans Serif",14) ;
    // headingLabel->setStyleSheet("color: #e6acac;");
    // headingLabel->setFont(boldFont);
    // headingLabel->setContentsMargins(2, 2, 2, 2);

    networkManager =  MyNetworkManager::instance();;


//    networkManager->testslot();

//    CreateTask *createTaskObj =  new CreateTask();

    refreshbtn = new QPushButton(this);
    QHBoxLayout * refresh_layout = new QHBoxLayout();
    QLabel * refresh_icon = new QLabel();
    QPixmap refresh_pic("://imgs/refresh.svg");
    QLabel * refresh_label = new QLabel("Refresh",this);

    filter_icon->setPixmap(filter_pic);
    filter_icon->setFixedSize(24,24);

    filter_layout->addWidget(filter_icon);
    filter_layout->addWidget(filter_label);

    filter_btn->setLayout(filter_layout);
    // filter_btn->setFlat(true);


    // filter_btn->setIcon(filter_pic);
    filter_btn->setFixedSize(100,40);
    // filter_btn->setIconSize(filter_btn->size());
    filter_btn->setFlat(true);

    refresh_icon->setPixmap(refresh_pic);
    refresh_icon->setFixedSize(24,24);

    refresh_layout->addWidget(refresh_icon);
    refresh_layout->addWidget(refresh_label);

    refreshbtn->setFixedSize(100,40);
    refreshbtn->setLayout(refresh_layout);
    // refreshbtn->setFlat(true);

    filter_btn->setStyleSheet(
        "QPushButton {"
        "border: 1px solid #D2232A;"
        "border-radius: 20px;"
        "}"
        // "QPushButton:hover {"
        // "background-color: #2980b9;"  // Background color on hover
        // "}"
        );
    refreshbtn->setStyleSheet(
        "QPushButton {"
        "border: 1px solid #D2232A;"
        "border-radius: 20px;"
        "}"
        );


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


//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");
//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

    search_layout->addWidget(search_label);
    search_layout->addWidget(search_lineedit);
    // search_layout->addWidget(createTaskBtn);
    search_layout->addWidget(filter_btn);
    search_layout->addWidget(refreshbtn);

    ProjectMainLayout->addLayout(search_layout);
    // ProjectMainLayout->addWidget(headingLabel);
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
    // ProjectMainLayout->addWidget(createTaskBtn);
    ProjectMainLayout->addLayout(create_layout);

    setLayout(ProjectMainLayout);
    setFixedSize(650,400);

    //signals and slots
    connect(createTaskBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "clicked create task button ";
        CreateTask * create_task = new CreateTask();
        create_task->show();
    });

    connect(filter_btn, &QPushButton::clicked, this, [=]{
        qDebug() << "filter button clicked" << overlayWidget->size();
        if (overlayWidget->isHidden()) {
            filter_btn->setStyleSheet(
                "QPushButton {"
                "background-color:#D2232A;"
                "border-radius: 20px;"
                "}"
                );
            QPixmap filter_white("://imgs/filterwhite.png");
            // filter_btn->setIcon(filter_white);
            filter_icon->setPixmap(filter_white);
            filter_label->setStyleSheet("color: #FFFFFF;");
            overlayWidget->show();
            overlayWidget->raise();
        }else{
            overlayWidget->hide();
            filter_label->setStyleSheet("");
            filter_icon->setPixmap(filter_pic);
            // filter_btn->setIcon(filter_pic);
            filter_btn->setStyleSheet(
                "QPushButton {"
                "border: 1px solid #D2232A;"
                "border-radius: 20px;"
                "}"
                );
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

    qDebug() << " projects_widget->size()" <<  projects_widget->size();
    projects_widget->setFixedHeight(30);
    connect(projects_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "overlayWidget->size() in projects" << overlayWidget->size() << projects_widget->size();
        if(projects_widget->isHidden()){
            qDebug() << "is projects visible true ";
            projects_widget->setVisible(true);
            // overlayWidget->setFixedHeight(81);
            overlayWidget->setFixedHeight(overlayWidget->height() + projects_widget->height());
        }else{
            qDebug() << "is projects visible false";
            projects_widget->setVisible(false);
            // overlayWidget->setFixedHeight(52);
            overlayWidget->setFixedHeight(50);
        }
    });
    folders_widget->setFixedHeight(150);
    qDebug() << "folders height " << folders_widget->height();
    connect(folders_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "folders_btn" << "clicked ";
        qDebug() << "overlayWidget->size() in folders" << overlayWidget->size() << folders_widget->size();
        if(folders_widget->isHidden()){
            qDebug() << "is visible true ";
            folders_widget->setVisible(true);
            overlayWidget->setFixedHeight(overlayWidget->height() + folders_widget->height());
            // overlayWidget->resize(overlayWidget->width(),250);
        }else{
            qDebug() << "is visible false";
            folders_widget->setVisible(false);
            overlayWidget->setFixedHeight(50);
            // overlayWidget->setFixedHeight(overlayWidget->height() - folders_widget->height());
        }
    });

    connect(defaultbtn,&QPushButton::clicked,this,[=]{
        qDebug() << "default btn clicked ";
        overlayWidget->setVisible(false);
        projects_widget->setVisible(false);
    });

    connect(current_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "current_task_btn clicked ";
        overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
    });
    connect(next_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "next_task_btn clicked ";
        overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
    });
    connect(future_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "future_task_btn clicked ";
        overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
    });
    connect(completed_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "completed_task_btn clicked ";
        overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
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
        return;
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

//        for (int i = 0; i < TaskModelFliterContainerList.size(); ++i) {
//            delete TaskModelFliterContainerList[i]; // Delete the object to avoid memory leaks
//        }
//        TaskModelFliterContainerList.clear(); // Clear the list

        qDebug() << "delete all TasksContainerList & TaskModelClassContainerList data" << QDateTime::currentDateTime().toString(Qt::ISODate);

}

// void Widget::showEvent(QShowEvent *event) {
//     qDebug() << "in event show function";
// }

// void Widget::hideEvent(QHideEvent *event) {
//     // qDebug() << "in event hide function";
//     overlayWidget->setVisible(false);
// }

// void Widget::moveEvent(QMoveEvent *event)
// {
//     QPoint buttonPos = filter_btn->mapToGlobal(filter_btn->rect().bottomRight());
//     int overlayWidth = overlayWidget->width();
//     QPoint overlayPos(buttonPos.x() - overlayWidth, buttonPos.y()+2);
//     overlayWidget->move(overlayPos);
// }

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
//            TaskModelFliterContainerList.append(task);    // setting data for the filtered list
        }
    }

    for(int i=0; i< TaskModelClassContainerList.size();++i){
//        TaskModelClass *taskobjdata = TaskModelClassContainerList[i];
        qDebug()<<"task name in the model containser list" << TaskModelClassContainerList[i]->m_taskName << TaskModelClassContainerList[i]->m_taskid;
    }
}

void Widget::onTaskDataFetched(int count)
{

    if(count == 1){
        for(int i=0; i< TaskModelClassContainerList.size();++i){
            ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
            customWidgetTaskdata->receiveData(TaskModelClassContainerList[i]->m_taskFolderName,
                                              TaskModelClassContainerList[i]->m_taskProjectName,
                                              TaskModelClassContainerList[i]->m_taskName,
                                              TaskModelClassContainerList[i]->m_taskid);
            TasksContainerList.append(customWidgetTaskdata);
        }
    }else if(count == 2){  //
//        for(int i=0; i< TaskModelFliterContainerList.size();++i){
//            ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
//            customWidgetTaskdata->receiveData(TaskModelFliterContainerList[i]->m_taskFolderName,
//                                              TaskModelFliterContainerList[i]->m_taskProjectName,
//                                              TaskModelFliterContainerList[i]->m_taskName,
//                                              TaskModelFliterContainerList[i]->m_taskid);
//            TasksContainerList.append(customWidgetTaskdata);
//        }
    }

    //    containerLayout->addWidget(customWidgetTaskdata);
}

void Widget::onEmptySignal()
{
qDebug()<<" onEmptySignal";
}
