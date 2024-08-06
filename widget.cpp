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
//QList<TaskModelClass*> TaskModelClassContainerList;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    ProjectMainLayout = new QVBoxLayout;
//    ProjectMainLayout->setContentsMargins(20,20,20,20);
    ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    containerLayout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(containerLayout);

    QLabel *headingLabel = new QLabel("Task List",this);
    QFont boldFont("Sans Serif",14) ;
//    boldFont.setBold(true);
    headingLabel->setStyleSheet("color: #e6acac;");
    headingLabel->setFont(boldFont);
    headingLabel->setContentsMargins(2, 2, 2, 2);

    networkManager =  MyNetworkManager::instance();;


//    networkManager->testslot();

//    CreateTask *createTaskObj =  new CreateTask();

    refreshbtn = new QPushButton("Refresh",this);
//    updatebtn = new QPushButton("updatebtn",this);

//    QObject::connect(customWidgetProject1, &ProjectCustomWidget::sendData, customWidgetProject1, &ProjectCustomWidget::receiveData);
//    QObject::connect(customWidgetProject2, &ProjectCustomWidget::sendData, customWidgetProject2, &ProjectCustomWidget::receiveData);

//    bool connectionStatus = connect(networkManager, &MyNetworkManager::projectDataFetched,[this](){
//        qDebug()<<"signal emmited";
//    });
//    qDebug() << "NetworkManager address:" << networkManager;
//    qDebug() << "This address:" << this;

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

    QSpacerItem *spacer = new QSpacerItem(10,5);

//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");
//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

    ProjectMainLayout->addWidget(headingLabel);
    ProjectMainLayout->addWidget(refreshbtn);



    scrollArea = new QScrollArea(this);
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

        qDebug() << "delete all TasksContainerList & TaskModelClassContainerList data";
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

            QJsonObject project_data_Obj = taskObject["project_data"].toObject();
            QString projectTitle = project_data_Obj["title"].toString();
            QString projectId = project_data_Obj["_id"].toString();


            TaskModelClass *task = new TaskModelClass(id, status, title, folderId,
                                                      folderName, projectId, projectTitle);

            TaskModelClassContainerList.append(task);
        }
    }

    for(int i=0; i< TaskModelClassContainerList.size();++i){
//        TaskModelClass *taskobjdata = TaskModelClassContainerList[i];
        qDebug()<<"task name in the model containser list" << TaskModelClassContainerList[i]->m_taskName;
    }
}

void Widget::onTaskDataFetched()
{
//    qDebug()<<"widget onTaskDataFetched method slot" << id<<" " <<title<<" "<<folderName<<" "<<projectTitle ;

    for(int i=0; i< TaskModelClassContainerList.size();++i){
        ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
        customWidgetTaskdata->receiveData(TaskModelClassContainerList[i]->m_taskFolderName,
                                          TaskModelClassContainerList[i]->m_taskProjectName,
                                          TaskModelClassContainerList[i]->m_taskName,
                                          TaskModelClassContainerList[i]->m_taskid);
        TasksContainerList.append(customWidgetTaskdata);
    }

    //    containerLayout->addWidget(customWidgetTaskdata);
}

void Widget::onEmptySignal()
{
qDebug()<<" onEmptySignal";
}

