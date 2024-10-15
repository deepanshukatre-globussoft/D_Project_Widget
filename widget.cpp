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
QMap<QString,QString> Widget::projectMap;
//QList<TaskModelClass*> TaskModelClassContainerList;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
     this->setObjectName("MainWidget");
    this->setWindowTitle(tr("Silah TTS"));
     this->show();
//    qDebug() << "widget constructor reference " << this;
    ProjectMainLayout = new QVBoxLayout;
    //    ProjectMainLayout->setContentsMargins(20,20,20,20);
    // ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->setContentsMargins(0,0,5,5);
    containerWidget->setLayout(containerLayout);
    containerWidget->setObjectName("containerWidget");
    // containerWidget->setStyleSheet("QWidget { background-color: white;  }");

    QHBoxLayout * search_layout = new QHBoxLayout();

    searchbar_widget = new QWidget(this);
    QHBoxLayout * search_minilayout_icon = new QHBoxLayout();
    QLabel * search_label = new QLabel(this);
    QPixmap search_icon("://imgs/search.svg");
    search_label->setPixmap(search_icon);
    search_label->setFixedSize(25,25);
    search_label->setScaledContents(true);
//    QLabel * serchtextlabel = new QLabel("search");
    QLineEdit * search_lineedit = new QLineEdit();

//    search_lineedit->setFixedHeight(35);
//    search_lineedit->setFont(QFont("Arial", 13));
    search_lineedit->setPlaceholderText(tr("Search"));
    search_lineedit->setFocusPolicy(Qt::ClickFocus);
    search_lineedit->setObjectName("search_lineeditObject");

    search_minilayout_icon->addWidget(search_label);
    search_minilayout_icon->addWidget(search_lineedit);

    searchbar_widget->setLayout(search_minilayout_icon);
    searchbar_widget->setStyleSheet(" background: rgba(248, 248, 248, 1); border-radius :20px;");

    QHBoxLayout * create_layout = new QHBoxLayout();

    QPushButton * createTaskBtn = new QPushButton(containerWidget);
    QIcon create_icon("://imgs/create.svg");
    createTaskBtn->setIcon(create_icon);
    createTaskBtn->setFlat(true);
    createTaskBtn->setFixedSize(45,45);
    createTaskBtn->setIconSize(QSize(45,45));
    createTaskBtn->setStyleSheet("border-radius:5px");
    // createTaskBtn->move(328,360);
//    createTaskBtn->setGeometry(100,100,30,30);
//     createTaskBtn->raise();

//    create_layout->addWidget(createTaskBtn);
    create_layout->setAlignment(Qt::AlignHCenter);
//    createTaskBtn->setGeometry(100,100,)

    filter_btn = new QPushButton(this);
    QHBoxLayout * filter_layout = new QHBoxLayout();
    QLabel * filter_icon = new QLabel();
    QPixmap filter_pic("://imgs/filter.png");
    QLabel * filter_label = new QLabel(tr("Filter"),this);

    overlayWidget = new QWidget(this);
    overlayCreatetaskWidget = new QWidget(this);

    QVBoxLayout *createTaskOverlayLayout = new QVBoxLayout(overlayCreatetaskWidget);

    createTaskOverlayLayout->setContentsMargins(0,0,0,0);
    QVBoxLayout *overlayLayout = new QVBoxLayout(overlayWidget);

    //projects btn
    QPushButton * projects_btn = new QPushButton(overlayWidget);
    // projects_btn->setStyleSheet("padding-left:0px;");
    QHBoxLayout * projectsLayout = new QHBoxLayout();
    projectsLayout->setContentsMargins(0,0,0,0);
    projectsLayout->setAlignment(Qt::AlignLeft);
    projectsLayout->setSpacing(0);
    QLabel * point_icon = new QLabel();
    QPixmap point("://imgs/whitedot.svg");
    point_icon->setPixmap(point);
    point_icon->setFixedSize(20,30);
    projects_label = new QLabel(tr("Projects"));
    projects_label->setFixedSize(110,28);
    QLabel * down_arrow_icon = new QLabel();
    QPixmap down_arrow("://imgs/arrow_down.svg");
    down_arrow.scaled(QSize(30,30));
    down_arrow_icon->setFixedSize(30,30);
    down_arrow_icon->setPixmap(down_arrow);

    projects_widget = new QWidget(this);
    QVBoxLayout * projects_display_layout = new QVBoxLayout(this);
    projects_display_layout->setContentsMargins(30,3,0,3);


    // QWidget *projects_scoll_widget = new QWidget(overlayWidget);
    // QVBoxLayout * projects_scroll_layout = new QVBoxLayout();
    // projects_scroll_layout->setContentsMargins(0,0,0,0);
    // Add many items to the comboBox
    int count = 6;
    // if(count>5){
        projectsscrollArea = new QScrollArea(this);
        projectsscrollArea->setContentsMargins(0,0,0,0);
        projectsscrollArea->setWidget(projects_widget);
        projectsscrollArea->setWidgetResizable(true); //    scrollArea->setFixedSize(630,400); // Adjust size dk
        projectsscrollArea->setFixedSize(170,2);
        projectsscrollArea->move(483,85);
        projectsscrollArea->setVisible(false);
        // Enable vertical scrolling
        // projectsscrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        // Disable horizontal scrolling
        // projectsscrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        projectsscrollArea->setStyleSheet(
            "QScrollBar:vertical {"
            //        "    background: #f0f0f0;"  // Background color of the scrollbar track
            "    width: 0px;"
            "    margin: 0px 0px 0px 0px;"
            "    border:0px;"
            "}"

            );
    // }

    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (int i = 0; i < count; i++) {
        // projectsComboBox->addItem(QString("Item %1").arg(i + 1));

        pro_btn[i] = new QPushButton();
        QHBoxLayout * pro_layout = new QHBoxLayout();
        QLabel * pro_icon = new QLabel();
        QPixmap pro_pic("://imgs/whitedot.svg");
        pro_icon->setPixmap(pro_pic);
        // current_task_icon->setFixedSize(12,18);
        pro_name[i] = new QLabel("Project " + QString::number(i+1));
        pro_name[i]->setFixedHeight(23);

        // setting current task btn
        pro_layout->setAlignment(Qt::AlignLeft);
        pro_layout->setContentsMargins(0,0,0,0);
        pro_layout->setSpacing(0);
        pro_layout->addWidget(pro_icon);
        pro_layout->addWidget(pro_name[i]);

        pro_btn[i]->setLayout(pro_layout);
        pro_btn[i]->setFixedHeight(25);
        pro_btn[i]->setFlat(true);

        // qDebug() << "projectwidget height " << projects_widget->height();
        projects_display_layout->addWidget(pro_btn[i]);
        // qDebug() << pro_btn[i]->size() << "size";
        // qDebug() << "projectwidget height 1" << projects_widget->height();
        // qDebug() << "projectwidget height 2" << projects_widget->height();
// count<5
        if(i<5){
            // qDebug() << "in i<5 and count >5";
            projectsscrollArea->setFixedHeight((projectsscrollArea->height()+33));
        }

        // qDebug() << "projectsscrollArea height " << projectsscrollArea->height();

        // qDebug() << "projectwidget height 3" << projects_widget->height();

        connect(pro_btn[i], &QPushButton::clicked, signalMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));

        signalMapper->setMapping(pro_btn[i], i);
    }

    // Connect signalMapper's mappedInt signal to handleButtonClicked slot
    connect(signalMapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mappedInt), this, &Widget::projectFilterSelect);

    projects_widget->setLayout(projects_display_layout);
    // projects_widget->setWindowFlags(Qt::FramelessWindowHint);
    projects_widget->setVisible(false);
    projects_widget->move(483,85);
    // projects_widget->setFixedSize(170,170);
    projects_widget->setStyleSheet("margin:0px; background-color: rgba(210, 35, 42, 1); padding :2px; border-radius:5px; color: #ffffff; ");

    QFrame* h_line = new QFrame(this);
    h_line->setFrameShape(QFrame::HLine);
    h_line->setFrameShadow(QFrame::Sunken);
    // h_line->setLineWidth(150);
    h_line->setStyleSheet("color: 0.5px solid rgba(255, 255, 255, 0.2);");

    //folders btn
    QPushButton * folders_btn = new QPushButton(overlayWidget);
    // folders_btn->setStyleSheet("border:1px solid black");
    QHBoxLayout * foldersLayout = new QHBoxLayout();
    foldersLayout->setContentsMargins(0,0,0,0);
    foldersLayout->setAlignment(Qt::AlignLeft);
    foldersLayout->setSpacing(0);
    QLabel * point_icon2 = new QLabel();
    point_icon2->setPixmap(point);
    point_icon2->setFixedSize(20,30);
    folders_label = new QLabel(tr("Folder"));
    folders_label->setFixedSize(110,28);
    QLabel * down_arrow_icon2 = new QLabel();
    down_arrow_icon2->setFixedSize(30,30);
    down_arrow_icon2->setPixmap(down_arrow);

    folders_widget = new QWidget(this);
    folders_widget->setStyleSheet("padding-left:0px;");
    QVBoxLayout * folders_display_layout = new QVBoxLayout();
    folders_display_layout->setContentsMargins(23,0,10,0);

    // current task btn
    QPushButton * current_task_btn = new QPushButton();
    // current_task_btn->setStyleSheet("border:1px solid white;");
    QHBoxLayout * current_task_layout = new QHBoxLayout();
    QLabel * current_task_icon = new QLabel();
    QPixmap current_task_pic("://imgs/bluedot.svg");
    current_task_icon->setPixmap(current_task_pic);
    // current_task_icon->setFixedSize(12,18);
    current_task_label = new QLabel(tr("Current Tasks"));

    // next task btn
    QPushButton * next_task_btn = new QPushButton();
    QHBoxLayout * next_task_layout = new QHBoxLayout();
    QLabel * next_task_icon = new QLabel();
    // next_task_icon->setFixedSize(24,24);
    QPixmap next_task_pic("://imgs/yellowdot.svg");
    next_task_icon->setPixmap(next_task_pic);
    next_task_label = new QLabel(tr("Next Tasks"));

    // future task btn
    QPushButton * future_task_btn = new QPushButton();
    QHBoxLayout * future_task_layout = new QHBoxLayout();
    QLabel * future_task_icon = new QLabel();
    // future_task_icon->setFixedSize(24,24);
    QPixmap future_task_pic("://imgs/reddot.svg");
    future_task_icon->setPixmap(future_task_pic);
    future_task_label = new QLabel(tr("Future Tasks"));

    // completed task btn
    QPushButton * completed_task_btn = new QPushButton();
    // completed_task_btn->setStyleSheet("border:1px solid white;");
    QHBoxLayout * completed_task_layout = new QHBoxLayout();
    QLabel * completed_task_icon = new QLabel();
    // completed_task_icon->setFixedSize(24,24);
    QPixmap completed_task_pic("://imgs/greendot.svg");
    completed_task_icon->setPixmap(completed_task_pic);
    completed_task_label = new QLabel(tr("Completed Tasks"));
    completed_task_label->setScaledContents(true);

    // setting current task btn
    current_task_layout->setAlignment(Qt::AlignLeft);
    current_task_layout->setContentsMargins(0,0,0,0);
    current_task_layout->setSpacing(0);
    current_task_layout->addWidget(current_task_icon);
    current_task_layout->addWidget(current_task_label);

    current_task_btn->setLayout(current_task_layout);
    current_task_btn->setFlat(true);

    // setting next task btn
    next_task_layout->setAlignment(Qt::AlignLeft);
    next_task_layout->setContentsMargins(0,0,0,0);
    next_task_layout->setSpacing(0);
    next_task_layout->addWidget(next_task_icon);
    next_task_layout->addWidget(next_task_label);

    next_task_btn->setLayout(next_task_layout);
    next_task_btn->setFlat(true);

    // setting future task btn
    future_task_layout->setAlignment(Qt::AlignLeft);
    future_task_layout->setContentsMargins(0,0,0,0);
    future_task_layout->setSpacing(0);
    future_task_layout->addWidget(future_task_icon);
    future_task_layout->addWidget(future_task_label);

    future_task_btn->setLayout(future_task_layout);
    future_task_btn->setFlat(true);

    // setting completed task btn
    completed_task_layout->setAlignment(Qt::AlignLeft);
    completed_task_layout->setContentsMargins(0,0,0,0);
    completed_task_layout->setSpacing(0);
    completed_task_layout->addWidget(completed_task_icon);
    completed_task_layout->addWidget(completed_task_label);

    completed_task_btn->setLayout(completed_task_layout);
    completed_task_btn->setFlat(true);

    folders_display_layout->addWidget(current_task_btn);
    folders_display_layout->addWidget(next_task_btn);
    folders_display_layout->addWidget(future_task_btn);
    folders_display_layout->addWidget(completed_task_btn);
    folders_display_layout->setSpacing(0);

    folders_widget->setLayout(folders_display_layout);
    folders_widget->setVisible(false);

    // setting projects layout
    projectsLayout->addWidget(point_icon);
    projectsLayout->addWidget(projects_label);
    projectsLayout->addWidget(down_arrow_icon);
    // projectsLayout->addStretch();

    // setting folders layout
    foldersLayout->addWidget(point_icon2);
    foldersLayout->addWidget(folders_label);
    foldersLayout->addWidget(down_arrow_icon2);
    // foldersLayout->addStretch();

    projects_btn->setLayout(projectsLayout);
    projects_btn->setFlat(true);
    folders_btn->setLayout(foldersLayout);
    folders_btn->setFlat(true);

    // setting overlayLayout
    overlayLayout->addWidget(projects_btn);
    // overlayLayout->addWidget(projects_widget);
    overlayLayout->addWidget(h_line);
    overlayLayout->addWidget(folders_btn);
    overlayLayout->addWidget(folders_widget);
    overlayLayout->setSpacing(0);
    createTaskOverlayLayout->addWidget(createTaskBtn);

    // setting overlayWidget
    overlayWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    overlayWidget->setFixedSize(170,70);
    overlayWidget->move(483,53);
    overlayWidget->setAutoFillBackground(true);
    overlayWidget->setLayout(overlayLayout);
    overlayWidget->setStyleSheet(" background-color: rgba(210, 35, 42, 1); padding :5px; border-radius:5px; color: white; ");
    overlayWidget->setVisible(false);

    overlayCreatetaskWidget->setFixedSize(45,45);
    overlayCreatetaskWidget->move(325,390);
    overlayCreatetaskWidget->setLayout(createTaskOverlayLayout);

    overlayCreatetaskWidget->setVisible(true);
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
    QLabel * refresh_label = new QLabel(tr("Refresh"),this);

    filter_icon->setPixmap(filter_pic);
    filter_icon->setFixedSize(24,24);

    filter_label->setStyleSheet("color : #D2232A;");
    filter_label->setFont(QFont("Ubuntu",-1,400));

    filter_layout->addWidget(filter_icon);
    filter_layout->setSpacing(17);
    filter_layout->addWidget(filter_label);

    filter_btn->setLayout(filter_layout);
    // filter_btn->setFlat(true);


    // filter_btn->setIcon(filter_pic);
    filter_btn->setFixedSize(100,40);
    // filter_btn->setIconSize(filter_btn->size());
    filter_btn->setFlat(true);

    refresh_icon->setPixmap(refresh_pic);
    refresh_icon->setFixedSize(24,24);

    refresh_label->setStyleSheet("color : #D2232A;");
    refresh_label->setFont(QFont("Ubuntu",-1,400));

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
    connect(networkManager,&MyNetworkManager::toSendProjectTaskList,this,&Widget::toDisplayTasks);
    connect(refreshbtn, &QPushButton::clicked, this,[this](){
        overlayWidget->setVisible(false);
        projects_widget->setVisible(false);
        folders_widget->setVisible(false);
        projects_label->setText(tr("Projects"));
        folders_label->setText(tr("Folder"));
        networkManager->fetchTasksForMobileList(token,10);
    });


//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");
//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

    search_layout->addWidget(searchbar_widget);
    // search_layout->addWidget(createTaskBtn);
    search_layout->addWidget(filter_btn);
    search_layout->addWidget(refreshbtn);

    // searchbar_widget->setLayout(search_layout);
    ProjectMainLayout->addLayout(search_layout);
    // ProjectMainLayout->addWidget(headingLabel);
//    ProjectMainLayout->addWidget(refreshbtn);


    scrollArea = new QScrollArea(this);
    scrollArea->setContentsMargins(0,0,0,0);
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true); //    scrollArea->setFixedSize(630,400); // Adjust size dk

    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"  // Removes the border from the scroll area
        "background-color: #ffffff;"
        "}"
        "QScrollBar:vertical {"
        "    width: 11px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        );



    // QList<ProjectCustomWidget *> customWidgets = containerWidget->findChildren<ProjectCustomWidget *>();
    // for (ProjectCustomWidget *widget : customWidgets) {
    //     // Check if the widget is selected
    //     QPushButton *pushbtn = widget->findChild<QPushButton *>();
    //     qDebug()<<"pushbtn : "<<pushbtn->text();
    //     //        if (checkBox && checkBox->isChecked()) {
    //     //            delete widget;
    //     //        }
    // }

    overlayCreatetaskWidget->show();
    overlayCreatetaskWidget->raise();
    //    ProjectMainLayout->addWidget(containerWidget);
    ProjectMainLayout->addWidget(scrollArea);
    // ProjectMainLayout->addWidget(createTaskBtn);
    ProjectMainLayout->addLayout(create_layout);

    setLayout(ProjectMainLayout);
//    setFixedSize(650,400);
    setFixedSize(700,450);

    // First time calling the api so it should not come empty
    networkManager->fetchTasksForMobileList(token,10);
    // projectsscrollArea->raise();
    // overlayWidget->show();
    // overlayWidget->raise();

    //signals and slots
    connect(createTaskBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "clicked create task button ";
        CreateTask * create_task = new CreateTask();
        create_task->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
        connect(create_task,&CreateTask::sendToCreateTask,this,&Widget::onTaskCreation);
        create_task->show();
    });

    connect(filter_btn, &QPushButton::clicked, this, [=]{
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
            overlayWidget->setVisible(true);
            overlayWidget->raise();
            // projectsscrollArea->setVisible(true);
            // projectsscrollArea->raise();
        }else{
            overlayWidget->setVisible(false);
            projects_widget->setVisible(false);
            projectsscrollArea->setVisible(false);
            filter_icon->setPixmap(filter_pic);
            filter_label->setStyleSheet("color : #D2232A;");
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

    connect(projects_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "projects_btn clicked ";
        if(projects_widget->isHidden()){
            qDebug() << "is projects visible true ";
            projectsscrollArea->setVisible(true);
            projects_widget->setVisible(true);
            projectsscrollArea->raise();
        }else{
            qDebug() << "is projects visible false";
            projects_widget->setVisible(false);
            projectsscrollArea->setVisible(false);
        }
    });
    connect(folders_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "folders_btn clicked ";
        if(folders_widget->isHidden()){
            folders_widget->setVisible(true);
            overlayWidget->setFixedHeight(200);
        }else{
            folders_widget->setVisible(false);
            overlayWidget->setFixedHeight(70);
        }
    });

    connect(current_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "current_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(current_task_label->text());
        overlayWidget->setFixedHeight(70);
    });
    connect(next_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "next_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(next_task_label->text());
        overlayWidget->setFixedHeight(70);
    });
    connect(future_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "future_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(future_task_label->text());
        overlayWidget->setFixedHeight(70);
    });
    connect(completed_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "completed_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(completed_task_label->text());
        overlayWidget->setFixedHeight(70);
    });

    // qDebug() << "end of widget constructor ";
    // QUrl url("https://track.dev.empmonitor.com/api/v3/project/stop-project-task");   // 6704ed000e8f24f13150e509

    // QUrlQuery query;
    // // query.addQueryItem("skip", QString::number(10));
    // // query.addQueryItem("limit", QString::number(10));
    // // query.addQueryItem("title", "FirstTask123");
    // // query.addQueryItem("folder_name", "Current Task");
    // // query.addQueryItem("project_id", "67037fe16cb902bf9f726f0e");
    // query.addQueryItem("task_id","6704ed000e8f24f13150e509");
    // url.setQuery(query);
    // QNetworkRequest request(url);
    // request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // QNetworkReply *reply = networkManager->networkManager->get(request);
    // connect(reply, &QNetworkReply::finished, this, [reply](){
    //     qDebug() <<"Project list "<<reply->readAll();
    // });
    // qDebug() << "reply error " << reply->errorString();
    // toGetProjectList();

    networkManager->getAllProjectTask(token,0,10);

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
    // for(ProjectCustomWidget *widgetObject : TasksContainerList ){
    //     // qDebug() << "This ProjectCustomWidget  added from TasksContainerList:" << widgetObject;
    //     containerLayout->addWidget(widgetObject);
    // }

    // containerLayout->addStretch();
    // containerLayout->addStretch();


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
            qDebug() << "Pro Name" << projectTitle << "Pro Id" << projectId << "Task Name" << title << "Task Id" << id;


            TaskModelClass *task = new TaskModelClass(id, status, title, folderId,
                                                      folderName, projectId, projectTitle);

            TaskModelClassContainerList.append(task);       // for whole data in unfiltered list
//            TaskModelFliterContainerList.append(task);    // setting data for the filtered list
        }
    }

//     for(int i=0; i< TaskModelClassContainerList.size();++i){
// //        TaskModelClass *taskobjdata = TaskModelClassContainerList[i];
//         qDebug()<<"task name in the model containser list" << TaskModelClassContainerList[i]->m_taskName << TaskModelClassContainerList[i]->m_taskid;
//     }
}

void Widget::onTaskDataFetched(int count)
{

    if(count == 1){
        for(int i=0; i< TaskModelClassContainerList.size();++i){
            ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
            customWidgetTaskdata->receiveData(TaskModelClassContainerList[i]->m_taskFolderName,
                                              TaskModelClassContainerList[i]->m_taskProjectName,
                                              TaskModelClassContainerList[i]->m_taskName,
                                              TaskModelClassContainerList[i]->m_taskid,
                                              TaskModelClassContainerList[i]->m_taskProjectId);
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

void Widget::projectFilterSelect(int index)
{
    qDebug() << pro_name[index]->text();
    projectsscrollArea->setVisible(false);
    projects_widget->setVisible(false);
    projects_label->setText(pro_name[index]->text());
}

void Widget::onTaskCreation(QString taskName, QString projectName, QString folderName, bool isStarted)
{
    qDebug() << "in ontotaskcreation function" << taskName << projectName << folderName << isStarted;
    // ProjectCustomWidget * taskCreatingWidget = new ProjectCustomWidget();
    // taskCreatingWidget->receiveData(folderName, projectName, taskName, "","");
    // containerLayout->insertWidget(0,taskCreatingWidget);
    // TasksContainerList.append(taskCreatingWidget);
    // if(isStarted)
    //     taskCreatingWidget->startOrPauseTaskAction();

    QUrl url("https://track.dev.empmonitor.com/api/v3/project/create-project-tasks");

    QJsonObject jsonObject;
    jsonObject["title"] = taskName;
    jsonObject["folder_name"] = "Current Task";
    jsonObject["project_id"] = "666aa77d044107706577a5cb";
    // jsonObject["start_date"] = NULL;
    // jsonObject["end_date"] = NULL;

    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->networkManager->post(request,jsonData);
    connect(reply, &QNetworkReply::finished, this, [reply](){
        QByteArray response = reply->readAll();
        qDebug() <<"Create Task Response "<<response;
        // if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
        //     QByteArray response = reply->readAll();
        //     qDebug() <<"Create Task Response "<<response;
        //     QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        //     QJsonObject jsonObj = jsonDoc.object();
        //     QString message = jsonObj.value("message").toString();
        //     if (message == "Project task created successfully") {
        //         QMessageBox::information(this, "Task Created", message);
        //     } else {
        //         qDebug() << "Message does not contain the expected text!";
        //     }
        // } else {
        //     qDebug() << "Network reply error " << reply->errorString();
        // }
    });
}

void Widget::toDisplayTasks(QJsonObject jsonTasksObj)
{
    if(jsonTasksObj.isEmpty()){
        QMessageBox::information(this,"Silah TTS","No tasks Assigned");
        return;
    }

    if (jsonTasksObj.contains("data") && jsonTasksObj["data"].isArray()){
        QJsonArray dataArray = jsonTasksObj["data"].toArray();

        if (!dataArray.isEmpty()) {
            for (int i = 0; i < dataArray.size(); ++i) {
                QJsonObject dataObject = dataArray[i].toObject();
                // qDebug() << "taskdataobject " << dataObject;

                ProjectCustomWidget * prowid = new ProjectCustomWidget();
                // qDebug() << "===========================================================";
                prowid->setProjectTaskDetails(dataObject);
                containerLayout->addWidget(prowid);

                // QString projectTitle = dataObject["title"].toString();
                // QString projectId = dataObject["_id"].toString();

                // qDebug() << "Project Title:" << projectTitle;
                // qDebug() << "Project ID:" << projectId;

                // projectMap.insert(projectId,projectTitle);
                // qDebug() << "first element in map " << projectMap.first() << projectMap.firstKey();
            }
            containerLayout->addStretch();
        } else {
            qDebug() << "No data found!";
        }
    } else {
        qDebug() << "Failed to parse JSON!";
    }
    //     }
    //     else {
    //         qDebug() << "reply error " << reply->errorString();
    //     }
    // });
}

// void Widget::toGetFolderList()
// {
//     QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-folder-silah");   // 6704ed000e8f24f13150e509

//     QUrlQuery query;
//     query.addQueryItem("skip", QString::number(10));
//     query.addQueryItem("limit", QString::number(10));
//     // query.addQueryItem("title", "FirstTask123");
//     // query.addQueryItem("folder_name", "Current Task");
//     query.addQueryItem("project_id", projectMap.first());
//     // query.addQueryItem("task_id","6704ed000e8f24f13150e509");
//     url.setQuery(query);
//     QNetworkRequest request(url);
//     request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     QNetworkReply *reply = networkManager->networkManager->get(request);
//     connect(reply, &QNetworkReply::finished, this, [reply](){
//         if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
//             QByteArray response = reply->readAll();
//             qDebug() <<"Project list "<<response;
//             QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//             QJsonObject jsonObj = jsonDoc.object();

//             if (jsonObj.contains("data") && jsonObj["data"].isArray()){
//                 QJsonArray jsonArray = jsonObj["data"].toArray();

//                 if (!jsonArray.isEmpty()) {
//                     QJsonObject dataObject = jsonArray[0].toObject();

//                     QString projectId = dataObject["_id"].toString();
//                     QString projectTitle = dataObject["title"].toString();

//                     qDebug() << "Project ID:" << projectId;
//                     qDebug() << "Project Title:" << projectTitle;
//                 } else {
//                     qDebug() << "No data found!";
//                 }
//             } else {
//                 qDebug() << "Failed to parse JSON!";
//             }
//         }
//         else {
//             qDebug() << "reply error " << reply->errorString();
//         }
//     });
// }

