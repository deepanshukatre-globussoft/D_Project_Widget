#include "widget.h"
#include "qdebug.h"


enum class FolderStatus {
    Current,
    Next,
    Future,
    completed
};

QList<TaskModelClass*> Widget::TaskModelClassContainerList; // for all task to show we append in this list by default this will used
//QList<TaskModelClass*> Widget::TaskModelFliterContainerList;
//QList<TaskModelClass*> TaskModelClassContainerList;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initialize_UI_Components();
}

Widget::~Widget(){ }

void Widget::initialize_UI_Components()
{
    this->setObjectName("MainWidget");
    this->setWindowTitle(tr("Silah TTS"));
    //    qDebug() << "widget constructor reference " << this;
    ProjectMainLayout = new QVBoxLayout;
    ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->setContentsMargins(2,5,5,5);
    containerLayout->setAlignment(Qt::AlignTop);
    containerWidget->setLayout(containerLayout);
    containerWidget->setObjectName("containerWidget");
    // containerWidget->setStyleSheet("QWidget { background-color: white;  }");

    searchbar_widget = new QWidget(this);
    searchbar_widget->installEventFilter(this); // Install event filter to intercept paint events
    QHBoxLayout * search_layout = new QHBoxLayout();
    QHBoxLayout * search_minilayout_icon = new QHBoxLayout();

    //    QHBoxLayout * search_minilayout_icon = new QHBoxLayout();
    //    QLabel * search_label = new QLabel(this);
    //    QPixmap search_icon("://imgs/search.svg");
    //    search_label->setPixmap(search_icon);
    //    QLabel * serchtextlabel = new QLabel("search");
    QLineEdit * search_lineedit = new QLineEdit();

    search_lineedit->setPlaceholderText(tr("Search"));

    QLabel * search_label = new QLabel(this);
    QPixmap search_icon("://imgs/search.svg");
    search_label->setPixmap(search_icon);
    search_label->setFixedSize(25,25);
    search_label->setScaledContents(true);
    search_lineedit->setFocusPolicy(Qt::ClickFocus);
    search_lineedit->setFont(QFont("Ubuntu",12));
    search_lineedit->setStyleSheet("border: none; background: rgba(248, 248, 248, 1); ");

    search_minilayout_icon->addWidget(search_label);
    search_minilayout_icon->addWidget(search_lineedit);
    searchbar_widget->setLayout(search_minilayout_icon);
    searchbar_widget->setFixedHeight(42);
    searchbar_widget->setObjectName("searchBarWidget");
    // searchbar_widget->setStyleSheet(" background: rgba(248, 248, 248, 1); border-radius :20px; QWidget{border: 0.5px solid rgba(35, 31, 32, 0.2)}");

    QHBoxLayout * create_layout = new QHBoxLayout();

//    QVBoxLayout * dddOverlaylayout =  new QVBoxLayout();

//    QLabel *label = new QLabel("Main Content Below", this);  // overlaylayout commented that one was not used
//    QPushButton *button = new QPushButton("Click Me", this);
//    dddOverlaylayout->addWidget(label);
//    dddOverlaylayout->addWidget(button);

    // Create the overlay widget

    //    projectComboBox->setStyleSheet("QComboBox::drop-down { border: none; }"   // Remove the drop-down border
    //                            "QScrollBar:vertical { width: 0px; }"    // Hide vertical scrollbar
    //                            "QScrollBar:horizontal { height: 0px; }" // Hide horizontal scrollbar
    //                            "QScrollBar:vertical:hover { width: 0px; }"    // Hide vertical scrollbar on hover
    //                            "QScrollBar:horizontal:hover { height: 0px; }"); // Hide horizontal scrollbar on hover


    //    for (int i = 1; i <= 10; ++i) {                   // dk comment for the adding the comboox items via api
    //        projectComboBox->addItem("Option " + QString::number(i));
    //    }

    QPushButton * createTaskBtn = new QPushButton(containerWidget);
    QIcon create_icon("://imgs/create.svg");
    createTaskBtn->setIcon(create_icon);
    createTaskBtn->setFlat(true);
    createTaskBtn->setFixedSize(60,60);
    createTaskBtn->setIconSize(QSize(60,60));
    createTaskBtn->setStyleSheet("border-radius:5px");
    // createTaskBtn->move(328,360);
    //    createTaskBtn->setGeometry(100,100,30,30);
    //     createTaskBtn->raise();

    //    create_layout->addWidget(createTaskBtn);
    create_layout->setAlignment(Qt::AlignHCenter);
    //    createTaskBtn->setGeometry(100,100,)

    filter_btn = new QPushButton(this);
    QHBoxLayout * filter_layout = new QHBoxLayout();
    filter_icon = new QLabel();
    filter_pic = QPixmap("://imgs/filter.png");
    filter_label = new QLabel(tr("Filter"),this);

    overlayWidget = new QWidget(this);
    overlayCreatetaskWidget = new QWidget(this);

    QVBoxLayout *createTaskOverlayLayout = new QVBoxLayout(overlayCreatetaskWidget);

    createTaskOverlayLayout->setContentsMargins(0,0,0,0);
    QVBoxLayout *overlayLayout = new QVBoxLayout(overlayWidget);
    overlayLayout->setContentsMargins(8,6,8,8);
    overlayLayout->setAlignment(Qt::AlignHCenter);
    overlayLayout->setAlignment(Qt::AlignVCenter);
    qDebug() << "overlaymargins " << overlayLayout->contentsMargins();

    projectComboBox = new QComboBox(overlayWidget);
    projectComboBox->setFixedSize(130,30);
    projectComboBox->setMaxVisibleItems(5);
    // projectComboBox->setGeometry(50, 50, 120, 30);
    // projectComboBox->raise();
    // projectComboBox->setVisible(true);

    projectComboBox->setFont(QFont("Ubuntu",10));
    // projectComboBox->setStyleSheet("margin:0px; padding-left:1px;");
    projectComboBox->setStyleSheet("QComboBox {"
                                  "margin: 0px;"
                                  "padding-left : 0px;"
                                   // "border: 1px solid black;"
                                  "}"
                                  "QComboBox::drop-down {"
                                  "border: none;"
                                  "width: 0px;"
                                  // "}"
                                  // "QComboBox::down-arrow {"
                                  // "image: url(://imgs/downarrow.png);"
                                  // "width: 16px;"
                                  // "height: 16px;"
                                  // "padding-right : 75px;"
                                  // "image-position: right center;"
                                  "}");
    projectComboBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // // Apply the stylesheet to remove the arrow and customize the scrollbar
    // projectComboBox->setStyleSheet(R"(
    //     QComboBox {
    //         /* Remove the arrow */
    //         // border-radius: 3px;
    //         // padding-right: 15px;  /* Adjust to prevent overlap */
    //         // padding-left: 10px;
    //         font-size: 15px;
    //     }

    //     // /* The drop-down list styling */
    //     // QComboBox QAbstractItemView {
    //     //     border: 1px solid gray;
    //     //     // selection-background-color: lightblue;
    //     //     /* Set max height for the popup to fit visible items */
    //     // }

    //     // /* Scroll bar custom styling */
    //     // QComboBox QAbstractItemView::verticalScrollBar {
    //     //     width: 0px;  /* Hide the scroll bar */
    //     // }

    //     // QComboBox QAbstractItemView::verticalScrollBar::handle:vertical {
    //     //     background: darkgray;
    //     //     min-height: 20px;
    //     //     border-radius: 4px;
    //     // }

    //     // QComboBox QAbstractItemView::verticalScrollBar::add-line:vertical,
    //     // QComboBox QAbstractItemView::verticalScrollBar::sub-line:vertical {
    //     //     height: 0px; /* Remove the up and down arrows */
    //     // }

    //     // QComboBox QAbstractItemView::verticalScrollBar::handle:vertical:hover {
    //     //     background: lightgray;
    //     // }
    // )");


//     //projects btn
//     QPushButton * projects_btn = new QPushButton();
//     // projects_btn->setStyleSheet("padding-left:0px;");
//     QHBoxLayout * projectsLayout = new QHBoxLayout();
//     projectsLayout->setContentsMargins(0,0,0,0);
//     projectsLayout->setAlignment(Qt::AlignLeft);
//     projectsLayout->setSpacing(0);
    QLabel * point_icon = new QLabel();
    QPixmap point("://imgs/whitedot.svg");
    point_icon->setPixmap(point);
    point_icon->setFixedSize(20,20);
    point_icon->setStyleSheet(" border:1px solid black;");
//     projects_label = new QLabel(tr("Projects"));
//     projects_label->setFixedSize(110,28);
    QLabel * down_arrow_icon = new QLabel();
    QPixmap down_arrow("://imgs/arrow_down.svg");
    down_arrow.scaled(QSize(30,30));
    down_arrow_icon->setPixmap(down_arrow);
    down_arrow_icon->setFixedSize(30,30);
    // down_arrow_icon->setStyleSheet("border: 1px solid black;");

    projects_widget = new QWidget(overlayWidget);
    QHBoxLayout * projects_display_layout = new QHBoxLayout(overlayWidget);
    projects_display_layout->setContentsMargins(0,0,0,0);
    // projects_display_layout->addWidget(point_icon);
    projects_display_layout->addWidget(projectComboBox);
    projects_display_layout->addWidget(down_arrow_icon);

    projects_widget->setLayout(projects_display_layout);
    // projects_widget->setStyleSheet("border:1px solid black;");

    QFrame* h_line = new QFrame(); // removing parent relation but temporary coz it can leak memory
    h_line->setFrameShape(QFrame::HLine);
    h_line->setFrameShadow(QFrame::Sunken);
    h_line->setLineWidth(100);
    h_line->setStyleSheet("color: 1px solid rgba(255, 255, 255, 255);border:1px solid black;");

    //folders btn
    QPushButton * folders_btn = new QPushButton(overlayWidget);
    // QPushButton * dkProFolders_btn = new QPushButton(overlayWidget);

    QHBoxLayout * foldersLayout = new QHBoxLayout();
    foldersLayout->setContentsMargins(0,0,0,0);
    foldersLayout->setAlignment(Qt::AlignLeft);
    foldersLayout->setSpacing(0);
    // QHBoxLayout * dkfoldersLayout = new QHBoxLayout();
    // dkfoldersLayout->setContentsMargins(0,0,0,0);
    // dkfoldersLayout->setAlignment(Qt::AlignLeft);
    // dkfoldersLayout->setSpacing(0);

    QLabel * point_icon2 = new QLabel();
    point_icon2->setPixmap(point);
    point_icon2->setFixedSize(20,30);
    point_icon2->setStyleSheet("padding-left:3px;");
    folders_label = new QLabel(tr("Folder"));
    folders_label->setFixedSize(110,28);
    folders_label->setStyleSheet("margin:0px; padding-left:0px;");
    QLabel * down_arrow_icon2 = new QLabel();
    down_arrow_icon2->setFixedSize(30,30);
    down_arrow_icon2->setPixmap(down_arrow);
    // down_arrow_icon2->setStyleSheet("border: 1px solid black;");

    QLabel * dkpoint_icon2 = new QLabel();
    dkpoint_icon2->setPixmap(point);
    dkpoint_icon2->setFixedSize(20,30);
    dkfolders_label = new QLabel(tr("Pro"));
    dkfolders_label->setFixedSize(150,28);
    QLabel * dkdown_arrow_icon2 = new QLabel();
    dkdown_arrow_icon2->setFixedSize(30,30);
    dkdown_arrow_icon2->setPixmap(down_arrow);

    folders_widget = new QWidget(overlayWidget);
    folders_widget->setStyleSheet("padding-left:0px; ");
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

    // folders_display_layout->setSpacing(0);
    folders_display_layout->addWidget(current_task_btn);
    folders_display_layout->addWidget(next_task_btn);
    folders_display_layout->addWidget(future_task_btn);
    folders_display_layout->addWidget(completed_task_btn);
    // folders_display_layout->addStretch();
    folders_display_layout->setSpacing(1);

    folders_widget->setLayout(folders_display_layout);
    folders_widget->setVisible(false);
    folders_widget->setFixedHeight(90);
    folders_widget->move(484,63);

    // // setting projects layout
    // projectsLayout->addWidget(point_icon2);
    // projectsLayout->addWidget(projects_label);
    // projectsLayout->addWidget(down_arrow_icon);
    // // projectsLayout->addStretch();

    // setting folders layout
    foldersLayout->addWidget(point_icon2);
    foldersLayout->addWidget(folders_label);
    foldersLayout->addWidget(down_arrow_icon2);
    foldersLayout->setSpacing(0);
    // setting folders layout
    // dkfoldersLayout->addWidget(dkpoint_icon2);
    // dkfoldersLayout->addWidget(dkfolders_label);
    // dkfoldersLayout->addStretch();
    //    dkfoldersLayout->addWidget(down_arrow_icon2);
    // foldersLayout->addStretch();

    // projects_btn->setLayout(projectsLayout);
    // projects_btn->setFlat(true);

    folders_btn->setLayout(foldersLayout);
    folders_btn->setFlat(true);
    folders_btn->setFixedHeight(25);
    // folders_btn->setStyleSheet("border: 1px solid black;");

    // dkProFolders_btn->setLayout(dkfoldersLayout);
    // dkProFolders_btn->setFlat(true);

    // setting overlayLayout
    //    overlayLayout->addWidget(projects_btn);

       // overlayLayout->addWidget(dkProFolders_btn);
    // overlayLayout->addWidget(projectComboBox);

    overlayLayout->addWidget(projects_widget);
    overlayLayout->addWidget(h_line);
    overlayLayout->addWidget(folders_btn);
    overlayLayout->addWidget(folders_widget);
    overlayLayout->setSpacing(0);
    createTaskOverlayLayout->addWidget(createTaskBtn);

    // setting overlayWidget
    overlayWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    overlayWidget->setFixedSize(170,80);
    overlayWidget->move(484,53);
    overlayWidget->setAutoFillBackground(true);
    overlayWidget->setLayout(overlayLayout);
    // overlayWidget->setObjectName("overlayWidgetObj");
    overlayWidget->setStyleSheet(" background-color: rgba(210, 35, 42, 1); padding :5px; border-radius:5px; color: white; ");
    overlayWidget->setVisible(false);

    overlayCreatetaskWidget->setFixedSize(60,60);
    overlayCreatetaskWidget->move(315,380);
    overlayCreatetaskWidget->setLayout(createTaskOverlayLayout);

    overlayCreatetaskWidget->setVisible(true);
    // overlayWidget->setFixedSize(150,300);

    // QLabel *headingLabel = new QLabel("Task List",this);
    // QFont boldFont("Sans Serif",14) ;
    // headingLabel->setStyleSheet("color: #e6acac;");
    // headingLabel->setFont(boldFont);
    // headingLabel->setContentsMargins(2, 2, 2, 2);

    networkManager =  MyNetworkManager::instance();;

    //    CreateTask *createTaskObj =  new CreateTask();

    refreshbtn = new QPushButton(this);
    QHBoxLayout * refresh_layout = new QHBoxLayout();
    QLabel * refresh_icon = new QLabel();
    QPixmap refresh_pic("://imgs/refresh.svg");
    QLabel * refresh_label = new QLabel("Refresh",this);

    filter_icon->setPixmap(filter_pic);
    filter_icon->setFixedSize(24,24);

    filter_label->setStyleSheet("color : #D2232A;");
    filter_label->setFont(QFont("Ubuntu",-1,400));

    filter_layout->addWidget(filter_icon);
    filter_layout->setSpacing(10);
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
    QString filterStyleSheet = "QPushButton {"
        "border: 1px solid #D2232A;"
        "border-radius: 20px;"
    "}";

    filter_btn->setStyleSheet(filterStyleSheet);
    refreshbtn->setStyleSheet(filterStyleSheet);

    connect(networkManager,&MyNetworkManager::dataSenderToComboBoxProjectList,this,&Widget::ondataSenderToComboBoxProjectList);

    connect(networkManager, &MyNetworkManager::projectDataFetched, this, &Widget::onProjectDataFetched);
    connect(networkManager, &MyNetworkManager::taskDataFetched, this, &Widget::onTaskDataFetched);
    connect(networkManager, &MyNetworkManager::sendingTasksFromAPIdataSignal, this, &Widget::onsendingTasksFromAPIdata);
    connect(networkManager, &MyNetworkManager::deleteConfigurationsignal, this,[this](){
        deleteConfiguration();
    });
    connect(networkManager, &MyNetworkManager::initConfigurationsignal, this,[this](){
        initConfiguration();
    });
    connect(refreshbtn, &QPushButton::clicked, this,[this, refresh_label, refresh_icon, refresh_pic, filterStyleSheet](){
        MyNetworkManager::currentFolderSelected = "";
        overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        overlayWidget->setFixedHeight(80);
        filter_label->setStyleSheet("color : #D2232A;");
        filter_btn->setStyleSheet(filterStyleSheet);
        filter_icon->setPixmap(filter_pic);
        refresh_label->setStyleSheet("color: #FFFFFF;");
        refreshbtn->setStyleSheet(
            "QPushButton {"
            "background-color:#D2232A;"
            "border-radius: 20px;"
            "}"
            );
        QPixmap refresh_white("://imgs/refreshwhite.svg");
        refresh_icon->setPixmap(refresh_white);
        QTimer::singleShot(80, this, [&,this]() {
            qDebug() << "Executing the singleshot for refresh";
            refresh_label->setStyleSheet("color : #D2232A;");
            refreshbtn->setStyleSheet(filterStyleSheet);
            refresh_icon->setPixmap(refresh_pic);
        });
        networkManager->fetchTasksForMobileList(token,10);
        networkManager->getAllProjects(token);
        projectComboBox->setCurrentIndex(0);
        folders_label->setText("Folder");
        // dkfolders_label->setText("Project");
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
    networkManager->getAllProjects(token);   // first time calling and setting data to the filter
    // projectsscrollArea->raise();
    // overlayWidget->show();
    // overlayWidget->raise();

    //signals and slots
    connect(createTaskBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "clicked create task button ";
        if(!create_task){
            create_task = new CreateTask(this);
            create_task->show();
            connect(create_task, &QWidget::destroyed, this, [this]() {
                qDebug() << "create_task Widget destroyed!";
                create_task = nullptr;
            });
        }
    });

    connect(filter_btn, &QPushButton::clicked, this, [=]{
        qDebug() << "overlay widget pos " << overlayWidget->pos();
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
            projectComboBox->raise();
            overlayWidget->setVisible(true);
            overlayWidget->raise();
            // projectsscrollArea->setVisible(true);
            // projectsscrollArea->raise();
        }else{
            overlayWidget->setVisible(false);
            // projectsscrollArea->setVisible(false);
            filter_icon->setPixmap(filter_pic);
            filter_label->setStyleSheet("color : #D2232A;");
            // filter_btn->setIcon(filter_pic);
            filter_btn->setStyleSheet(filterStyleSheet);
        }
    });

    connect(search_lineedit,&QLineEdit::editingFinished,this,[=]{
        qDebug() << "search line edit text " << search_lineedit->text() ;
        if(search_lineedit->text().isEmpty()){
            networkManager->fetchTasksForMobileList(token,0);
            return;
        }
        networkManager->allTasksInSeletedSearchKeyword(token,search_lineedit->text(),0,10);
        for(int i=0;i<TasksContainerList.length();i++){
            if(TasksContainerList.at(i)->d_taskNameLabel->text().contains(search_lineedit->text(),Qt::CaseInsensitive)){
                qDebug() << "title contains "<< search_lineedit->text() << " :" << TasksContainerList.at(i)->d_taskNameLabel->text();
                TasksContainerList.at(i)->setVisible(true);
            }else{
                TasksContainerList.at(i)->setVisible(false);
            }
        }
    });

    connect(folders_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "folders_btn clicked " << overlayWidget->size();
        if(folders_widget->isHidden()){
            folders_widget->setVisible(true);
            // projectComboBox->setVisible(false);
            overlayWidget->setFixedHeight(170);
        }else{
            folders_widget->setVisible(false);
            // projectComboBox->setVisible(false);
            overlayWidget->setFixedHeight(80);
        }
    });
    // connect(dkProFolders_btn,&QPushButton::clicked,this,[=]{
    //     if(projectComboBox->isHidden()){
    //         qDebug() << "dkProFolders_btn clicked making comboox visible";
    //         projectComboBox->setVisible(true);
    //         // folders_widget->setVisible(false);
    //         // overlayWidget->setFixedHeight(200);
    //     }else{
    //         qDebug() << "dkProFolders_btn clicked making comboox invisible";
    //         projectComboBox->setVisible(false);
    //         folders_widget->setVisible(false);
    //         //            overlayWidget->setFixedHeight(70);
    //     }
    // });

    connect(projectComboBox, &QComboBox::textActivated, this, [this](const QString &text) {
        int index = projectComboBox->currentIndex();
        QString projectId = projectComboBox->itemData(index).toString();
        qDebug() << "project combobox text "<< text << "====================== " << projectId;

        QString folderFilterText;
        bool isFolderSelected = false;
        if(folders_label->text() != "Folder"){                                             // Checking folder Selected or not
            isFolderSelected = true;
            folderFilterText = folders_label->text();
            folderFilterText.chop(1);
            if(folderFilterText == "Completed Task")
                folderFilterText = "Finished Task";

            qDebug() << "folder filter text " << folderFilterText;
        }

        if(text == "Projects" || projectId.isEmpty() || projectId == "777"){                // All projects
            qDebug()<<"all projects is selected so not doing api call";
            if(isFolderSelected){                                                           // Folder selected for All Projects
                networkManager->allTasksInSeletedFolder(token,folderFilterText,0,10);
            }else{                                                                          // All tasks of all projects and folders
                networkManager->fetchTasksForMobileList(token,0);
            }
        }else{                                                                              // Project selected
            if(isFolderSelected){                                                           // Project and folder selected
                qDebug() << "project and folder are selected ";
                networkManager->allTasksInSeletedProjectAndFolder(token,projectId,folderFilterText,0,10);
            }else{
                networkManager->allTasksInSeletedProject(token,projectId,0,10);             // Only project selected
            }
        }
    });

    connect(current_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "current_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(current_task_label->text());
        overlayWidget->setFixedHeight(80);

        int index = projectComboBox->currentIndex();
        QString projectId = projectComboBox->itemData(index).toString();
        if(projectComboBox->currentText() == "Projects" || projectId.isEmpty() || projectId == "777"){
            qDebug()<<"projectId is empty when current task is selected";
            networkManager->allTasksInSeletedFolder(token,"Current Task",0,10);
        }else{
            networkManager->allTasksInSeletedProjectAndFolder(token,projectId,"Current Task",0,10);
            qDebug()<<"projectId is not empty when current task is selected"<<projectId << index;
        }
    });
    connect(next_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "next_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(next_task_label->text());
        overlayWidget->setFixedHeight(80);

        int index = projectComboBox->currentIndex();
        QString projectId = projectComboBox->itemData(index).toString();
        if(projectId.isEmpty() || projectId == "777"){
            qDebug()<<"projectId is empty when next task is selected";
            networkManager->allTasksInSeletedFolder(token,"Next Task",0,10);
        }else{
            networkManager->allTasksInSeletedProjectAndFolder(token,projectId,"Next Task",0,10);
            qDebug()<<"projectId is not empty when next task is selected"<<projectId << index;
        }

    });
    connect(future_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "future_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(future_task_label->text());
        overlayWidget->setFixedHeight(80);
        // networkManager->allTasksInSeletedFolder(token,"Future Task",0,10);

        int index = projectComboBox->currentIndex();
        QString projectId = projectComboBox->itemData(index).toString();
        if(projectId.isEmpty() || projectId == "777"){
            qDebug()<<"projectId is empty when future task is selected";
            networkManager->allTasksInSeletedFolder(token,"Future Task",0,10);
        }else{
            networkManager->allTasksInSeletedProjectAndFolder(token,projectId,"Future Task",0,10);
            qDebug()<<"projectId is not empty when Future  task is selected"<<projectId << index;
        }
    });
    connect(completed_task_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "completed_task_btn clicked ";
        // overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        folders_label->setText(completed_task_label->text());
        overlayWidget->setFixedHeight(80);
        // networkManager->allTasksInSeletedFolder(token,"Finished Task",0,10);

        int index = projectComboBox->currentIndex();
        QString projectId = projectComboBox->itemData(index).toString();
        qDebug() << "project Id " << projectId << projectComboBox->itemText(index);
        if(projectId.isEmpty() || projectId == "777"){
            qDebug()<<"projectId is empty when Finished task is selected";
            networkManager->allTasksInSeletedFolder(token,"Finished Task",0,10);
        }else{
            networkManager->allTasksInSeletedProjectAndFolder(token,projectId,"Finished Task",0,10);
            qDebug()<<"projectId is not empty when Finished task is selected"<<projectId << index;
        }
    });


    qDebug() << "content margins " << ProjectMainLayout->contentsMargins();

    // connect(scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, [this](int value) {
    //     int maxScrollValue = scrollArea->verticalScrollBar()->maximum();
    //     int viewportHeight = scrollArea->viewport()->height();

    //     qDebug() << "Vertical scroll value changed: " << value << maxScrollValue << viewportHeight;
    //     // Check if the scrollbar is at the bottom
    //     if (value >= maxScrollValue - viewportHeight) {
    //         qDebug() << "Reached the bottom of the scroll area!";
    //         // networkManager->fetchTasksForMobileList(token,10);
    //     }
    // });
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
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setFixedSize(500, 400);  // Set fixed size for the image label
        imageLabel->setText("To Task found for selcted filteration");
        imageLabel->setAlignment(Qt::AlignJustify);

        QPixmap pixmap("://imgs/no-task-img.jpg");  // Load the image
        pixmap = pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imageLabel->setPixmap(pixmap);
        imageLabel->setStyleSheet("QLabel { padding-left: 80px; }");
        containerLayout->addWidget(imageLabel);
        return;
    }else{
        QLayoutItem* item;
        while ((item = containerLayout->takeAt(0))  != nullptr) {
            if (QWidget* widget = item->widget()) {
                widget->hide();         // Hide the widget
                widget->deleteLater();  // Schedule the widget for deletion
            }
            delete item;  // Delete the layout item (not the widget itself)
        }
    }
    for(ProjectCustomWidget *widgetObject : TasksContainerList ){
        //        qDebug() << "This ProjectCustomWidget  added from TasksContainerList:" << widgetObject;
        if(widgetObject->projectTaskStatus != "Finished Task"){
        //     qDebug() << "project status widget " << widgetObject->projectTaskStatus;
            containerLayout->addWidget(widgetObject);
         }
        else if(MyNetworkManager::currentFolderSelected == "Finished Task" && widgetObject->projectTaskStatus == "Finished Task"){
            containerLayout->addWidget(widgetObject);
        }
    }

    //    containerLayout->addStretch();  // let it be uncommented dk issue for bottom in 1,2 iter this will happen
    //    containerLayout->addStretch();

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

void Widget::onsendingTasksFromAPIdata(const QJsonArray &dataArray)  // adding data in the task container model list
{
    for (const QJsonValue &value : dataArray) {
        if (value.isObject()) {
            QJsonObject taskObject = value.toObject();
            // qDebug() << "task object " << taskObject;
            int status = taskObject["status"].toInt();
            QString id = taskObject["_id"].toString();
            QString title = taskObject["name"].toString();
            qint64 active_timeInt = taskObject["active_time"].toInt();
            QString active_time = QString::number(active_timeInt);
            QString task_remaining_time = taskObject["task_remaining_time"].toString();
            QString task_finished_time = taskObject["task_finished_time"].toString();

            QJsonObject folderObject = taskObject["folder_data"].toObject();
            QString folderName = folderObject["name"].toString();
            //            qDebug()<<"name " <<taskObject["active_time"].toInt();
            //            qDebug()<<"active_time " <<active_time << task_remaining_time <<task_finished_time;

            //            QString folderId = folderObject["_id"].toString();
            //    ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
            //    customWidgetTaskdata->receiveData(folderName,projectTitle,title,id);
            //    containerLayout->addWidget(customWidgetTaskdata);

            QJsonObject project_data_Obj = taskObject["project_data"].toObject();
            QString projectTitle = project_data_Obj["title"].toString();
            QString projectId = project_data_Obj["_id"].toString();

            //            TaskModelClass *task = new TaskModelClass(id, status, title, folderId,
            //                                                      folderName, projectId, projectTitle);

            TaskModelClass *task = new TaskModelClass(id, status, title, active_time,
                                                      task_remaining_time,folderName,
                                                      projectId,task_finished_time, projectTitle);

            TaskModelClassContainerList.append(task);       // for whole data in unfiltered list
            //            TaskModelFliterContainerList.append(task);    // setting data for the filtered list
        }
    }

    for(int i=0; i< TaskModelClassContainerList.size();++i){
        //        TaskModelClass *taskobjdata = TaskModelClassContainerList[i];
        //        qDebug()<<__LINE__<<"task name in the model containser list" << TaskModelClassContainerList[i]->m_taskName << TaskModelClassContainerList[i]->m_taskid;
    }
}

void Widget::onTaskDataFetched(int count) // adding data in the task container ui list from task model container list
{
    qDebug() << "taskmodelclasscontainerlist " << TaskModelClassContainerList.size();

    if(count == 1){
        for(int i=0; i< TaskModelClassContainerList.size();++i){
            ProjectCustomWidget *customWidgetTaskdata = new ProjectCustomWidget();
            //            customWidgetTaskdata->setTaskProjectsIdNameinProjectCustomWidget(TaskModelClassContainerList[i]->m_taskFolderName,
            //                                              TaskModelClassContainerList[i]->m_taskProjectName,
            //                                              TaskModelClassContainerList[i]->m_taskName,
            //                                              TaskModelClassContainerList[i]->m_taskid);
            customWidgetTaskdata->setTaskAllDataInProjectCustomWidget(TaskModelClassContainerList[i]->m_taskid,TaskModelClassContainerList[i]->m_taskStatus,
                                                                      TaskModelClassContainerList[i]->m_taskName,
                                                                      TaskModelClassContainerList[i]->m_taskActiveTime,TaskModelClassContainerList[i]->m_taskRemainingTime,
                                                                      TaskModelClassContainerList[i]->m_taskFolderName,TaskModelClassContainerList[i]->m_taskProjectId,
                                                                      TaskModelClassContainerList[i]->m_taskFinishedTime,TaskModelClassContainerList[i]->m_taskProjectName);
            TasksContainerList.append(customWidgetTaskdata);
        }

        // int verticalScrollValue = scrollArea->verticalScrollBar()->maximum();
        // int horizontalScrollValue = scrollArea->horizontalScrollBar()->value();

        // qDebug() << "Initial vertical scroll value: " << verticalScrollValue << horizontalScrollValue;
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

void Widget::ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList)
{
    projectComboBox->clear();

    QIcon icon("://imgs/whitedot.svg");
    QSize iconSize(10,10);
    QPixmap pixmap = icon.pixmap(iconSize);
    QIcon resizedIcon(pixmap);
    QString projectTitle("Projects");
    projectComboBox->addItem(resizedIcon,projectTitle, 777);

    for (const QJsonValue& value : projectIdAndNameList) {
        QJsonObject projectObject = value.toObject();
        QString projectId = projectObject.value("_id").toString();   // Extract _id
        QString projectTitle = projectObject.value("title").toString(); // Extract title

        projectComboBox->addItem(resizedIcon,projectTitle, projectId); // title, hidden _id

        qDebug() << "Project ID:" << projectId << projectTitle;
    }
}
void Widget::mousePressEvent(QMouseEvent *event) {
    // Only handle left-button presses if within a specific area
    qDebug() << "mouse press event ";

    QWidget *clickedWidget = QApplication::widgetAt(event->globalPos());

    // Check if the clicked widget is the external widget or its child
    if (clickedWidget == containerWidget || containerWidget->isAncestorOf(clickedWidget)) {
        qDebug() << "Mouse click is inside the external widget or one of its children!";
    } else {
        qDebug() << "Mouse click is outside the external widget!";
    }

    if(!overlayWidget->isHidden()){
        overlayWidget->setVisible(false);
        folders_widget->setVisible(false);
        overlayWidget->setFixedHeight(60);
        filter_label->setStyleSheet("color : #D2232A;");
        filter_btn->setStyleSheet(
            "QPushButton {"
            "border: 1px solid #D2232A;"
            "border-radius: 20px;"
            "}"
            );
        filter_icon->setPixmap(filter_pic);
    }
    // If you don't want the base class to handle the event, do NOT call this
    QWidget::mousePressEvent(event);
}
