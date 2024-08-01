#include "widget.h"
#include "createtask.h"
#include "qdebug.h"


enum class TaskStatus {
    Current,
    Next,
    Future,
    completed
};

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


//    ProjectCustomWidget *customWidgetProject1 = new ProjectCustomWidget();
//    ProjectCustomWidget *customWidgetProject2 = new ProjectCustomWidget();
//    ProjectCustomWidget *customWidgetProject3 = new ProjectCustomWidget();
//    ProjectCustomWidget *customWidgetProject4 = new ProjectCustomWidget();

//    CreateTask *createTaskObj =  new CreateTask();

    refreshbtn = new QPushButton("refresh",this);
    updatebtn = new QPushButton("updatebtn",this);

//    QObject::connect(customWidgetProject1, &ProjectCustomWidget::sendData, customWidgetProject1, &ProjectCustomWidget::receiveData);
//    QObject::connect(customWidgetProject2, &ProjectCustomWidget::sendData, customWidgetProject2, &ProjectCustomWidget::receiveData);

//    bool connectionStatus = connect(networkManager, &MyNetworkManager::projectDataFetched,[this](){
//        qDebug()<<"signal emmited";
//    });
//    qDebug() << "NetworkManager address:" << networkManager;
//    qDebug() << "This address:" << this;

    connect(networkManager, &MyNetworkManager::projectDataFetched, this, &Widget::onProjectDataFetched);
    connect(networkManager, &MyNetworkManager::taskDataFetched, this, &Widget::onTaskDataFetched);
    connect(networkManager, &MyNetworkManager::mytestNetworksignal, this,[this](){
        deleteConfiguration();
    });
    connect(networkManager, &MyNetworkManager::mytestNetworksignal2, this,[this](){
        initConfiguration();
    });
    connect(refreshbtn, &QPushButton::clicked, this,[this](){
        networkManager->fetchTasksForMobileList(token,10);
    });


//        emit customWidgetProject1->sendData("Status: In Progress", "Project Alpha", "Task 1", "01:23:45");
//    emit customWidgetProject2->sendData("Status: Completed", "Project Beta", "Task 2", "00:45:30");

    QSpacerItem *spacer = new QSpacerItem(10,5);

//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");

//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

    ProjectMainLayout->addWidget(headingLabel);
    ProjectMainLayout->addWidget(refreshbtn);
//    containerLayout->addWidget(customWidgetProject1); //  for loop use karna hain
//    containerLayout->addSpacerItem(spacer);
//    containerLayout->addWidget(customWidgetProject2);
//    containerLayout->addSpacerItem(spacer);
//    containerLayout->addWidget(customWidgetProject3);
//    containerLayout->addSpacerItem(spacer);
//    containerLayout->addWidget(customWidgetProject4);
//    containerLayout->addWidget(createTaskObj);


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
        qDebug() << "This ProjectCustomWidget  added :" << widgetObject;
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
        qDebug() << "delete all TasksContainerList data";
}

void Widget::onProjectDataFetched(const QJsonArray &dataArray)
{
    qDebug()<<"widget onprojectsdatafetched slot called" << dataArray;

}

void Widget::onTaskDataFetched(const QString &id, const QString &title, const QString &folderName, const QString &projectTitle)
{
    qDebug()<<"widget onTaskDataFetched method slot" << id<<" " <<title<<" "<<folderName<<" "<<projectTitle ;

    ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
    customWidgetTaskdata->receiveData(folderName,projectTitle,title,id);
//    containerLayout->addWidget(customWidgetTaskdata);

    TasksContainerList.append(customWidgetTaskdata);

}

void Widget::onEmptySignal()
{
qDebug()<<" onEmptySignal";
}

