#include "projectcustomwidget.h"
#include "qdebug.h"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    // networkManager = MyNetworkManager::instance();

    m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(5,5,0,0);
    m_HMainLayout->setAlignment(Qt::AlignLeft);

    QFont labelFont("Ubuntu",11,400);
    this->setFocusPolicy(Qt::ClickFocus);  // focus adding
    this->setObjectName("customProjectItemWidget") ;
    // this->setStyleSheet("background-color: rgba(35, 31, 32, 0.1);");
    d_containerWidget = new QWidget(this);

    // QHBoxLayout * hor_layout = new QHBoxLayout(d_containerWidget);
    // hor_layout->setContentsMargins(0,0,0,0);
    completeBtn = new QPushButton(this);
    // completeBtn->setFixedSize(20,this->height());
    // completeBtn->setStyleSheet("background-color: #8be51e; color: white;");

    // hor_layout->addWidget(completeBtn);
    QIcon complete_icon("://imgs/completed.svg");
    completeBtn->setIcon(complete_icon);
    completeBtn->setFixedSize(25,25);
    completeBtn->setIconSize(QSize(25,25));
    completeBtn->setStyleSheet("border-radius: 2px;");

    deleteBtn = new QPushButton(this);
    // deleteBtn->setStyleSheet("background-color: #fa3c36  ; color: white;");
    // deleteBtn->setFixedSize(20,this->height());
    QIcon deleteIcon(":/imgs/delete.svg");
    deleteBtn->setIcon(deleteIcon);
    deleteBtn->setFlat(true);
    deleteBtn->setIconSize(QSize(25,25));
    deleteBtn->setFixedSize(25,25);
    deleteBtn->setStyleSheet("border-radius: 2px;");



    d_containerLayout = new QVBoxLayout();
    d_containerLayout->setContentsMargins(7,7,7,7);
    d_containerWidget->setObjectName("projectContainerObject");

    // QSpacerItem *spacer = new QSpacerItem(5,3);

    d_projectStatuslabel = new QLabel(tr(""), this);  // shyad public karke access dena hoga
    d_projectStatuslabel->setObjectName("d_projectStatuslabel");
    d_startTaskButton = new QPushButton(this);
    d_editTaskButton = new QPushButton(this);
    QFont font;
    font.setFamily("arial"); // Set font family
    font.setPointSize(8);  // Set font size
    //    font.setItalic(true); // Set font style (not italic)
    d_editTaskButton->setFont(font);

    m_startTimer = new QTimer();
    m_startTimer->setInterval(1000);
    m_startTimer->setTimerType(Qt::CoarseTimer);

    countdownTime = QTime(0,0,0);

    m_startReminderTimer = new QTimer();
    m_startReminderTimer->setInterval(1000);
    m_startReminderTimer->setTimerType(Qt::CoarseTimer);

    remindercountdownTime = QTime(0,0,0);

    d_editTaskButton->setObjectName("myPushBtn");  // Set object name
    //==================================================
    d_projectNameLabel =  new QLabel(tr("Project Name"),this);
    d_projectNameLabel->setObjectName("d_projectNameLabel");

    //==================================================
    d_taskNameLabel = new QLabel(tr("Task Title"),this);
    d_taskNameLabel->setObjectName("d_taskNameLabel");
    //==================================================
    d_setReminderbtn = new QPushButton(tr("Set reminder"),this);
    d_setReminderbtn->setObjectName("reminderbtnObj");
    d_setReminderbtn->setVisible(false);
    QFont d_setReminderbtn_font = d_setReminderbtn->font();
    d_setReminderbtn_font.setUnderline(true);
    d_setReminderbtn->setFont(d_setReminderbtn_font);
    d_setReminderbtn->setStyleSheet(
        "QPushButton {"
        "color: #D2232A;"               // Text color
        "padding-left:0px;"
        "border:none;"
        "}"
        );
    d_setReminderbtn->setFlat(true);

    QVBoxLayout * active_time_layout = new QVBoxLayout();
    QLabel * active_task_time = new QLabel(tr("Active Task Time"));
    active_task_time->setObjectName("active_task_time");

    d_taskActiveTimeLabel = new QLabel("00:00:00",this);
    d_taskActiveTimeLabel->setObjectName("d_taskActiveTimeLabel");
    // d_taskActiveTimeLabel->setFixedHeight(23);

    // active_time_layout->setAlignment(Qt::AlignCenter);
    active_time_layout->setContentsMargins(0,0,0,0);
    // active_time_layout->addStretch();
    active_time_layout->addWidget(active_task_time);
    active_time_layout->addWidget(d_taskActiveTimeLabel);

    startbtn_layout = new QHBoxLayout();
    start_icon = new QLabel();
    start_icon->setStyleSheet("background-color: #D2232A; color:#FFFFFF");
    start_pic = QPixmap("://imgs/start.png");
    start_label = new QLabel(tr("Start"),this);
    start_label->setStyleSheet("background-color: #D2232A; color:#FFFFFF ; font-size: 12px;");
//    start_label->setStyleSheet("background-color: #8be51e");

//    start_label->setStyleSheet("color: #FFFFFF;");
    start_icon->setPixmap(start_pic);

    startbtn_layout->setContentsMargins(9,0,13,0);
    startbtn_layout->addSpacing(5);
    startbtn_layout->addWidget(start_icon);
    startbtn_layout->addWidget(start_label);

    d_startTaskButton->setFixedSize(76,25);
    d_startTaskButton->setLayout(startbtn_layout);
    d_startTaskButton->setStyleSheet(
        "QPushButton {"
        "background-color: #D2232A;"
        "border-radius: 11px;"
        "}"
        );

    QHBoxLayout * editbtn_layout = new QHBoxLayout();
    QLabel * edit_icon = new QLabel();
    QPixmap edit_pic("://imgs/edit.svg");
    QLabel * edit_label = new QLabel(tr("Edit"),this);

    edit_icon->setStyleSheet("border-top:1px solid #D2232A;border-bottom:1px solid #D2232A; ");
    edit_icon->setPixmap(edit_pic);
    edit_label->setStyleSheet("color : #D2232A; border-top:1px solid #D2232A;border-bottom:1px solid #D2232A; ");
    // edit_label->setStyleSheet("color : #D2232A;");
    // edit_label->setFixedHeight(25);

    editbtn_layout->setContentsMargins(9,0,13,0);
    editbtn_layout->addWidget(edit_icon);
    editbtn_layout->addWidget(edit_label);

    d_editTaskButton->setFixedSize(72,25);
    d_editTaskButton->setLayout(editbtn_layout);
    d_editTaskButton->setStyleSheet(
        "QPushButton {"
        "border: 1px solid #D2232A;"
        // "background-color: #D2232A;"
        "border-radius: 11px;"
        "}"
        );


    p_FirstLayout = new QHBoxLayout;
    p_FirstLayout->setContentsMargins(0,0,0,0);
    p_FirstLayout->addWidget(d_projectStatuslabel);
    p_FirstLayout->addStretch();
    p_FirstLayout->addWidget(completeBtn);
    p_FirstLayout->addWidget(deleteBtn);
    p_FirstLayout->addWidget(d_startTaskButton);
    p_FirstLayout->addWidget(d_editTaskButton);
    // completeBtn->hide();
    // deleteBtn->hide();


    p_SecondLayout = new QHBoxLayout;
    p_SecondLayout->setContentsMargins(0,0,0,0);
    p_SecondLayout->addWidget(d_projectNameLabel);

    p_ThirdLayout = new QHBoxLayout;
    p_ThirdLayout->setContentsMargins(0,0,0,0);
    p_ThirdLayout->addWidget(d_taskNameLabel);

    p_ForthLayout = new QHBoxLayout;
    p_ForthLayout->setContentsMargins(0,0,0,0);

    // QWidget * hor_widget = new QWidget();
    // hor_widget->setLayout(p_ForthLayout);
    // hor_widget->setStyleSheet("QWidget { border: 1px solid black; }");

    reminder_widget = new QWidget();
    QVBoxLayout * reminder_widget_layout = new QVBoxLayout();
    QPushButton * reminder_layout_button = new QPushButton();
    QVBoxLayout * reminder_layout = new QVBoxLayout();
    QLabel * reminder_label = new QLabel(tr("Remaining Time"));
    d_taskReminderTimeInReminder = new QLabel("00:00:00");
    d_taskReminderTimeInReminder->setObjectName("d_taskActiveTimeLabel");

    reminder_label->setStyleSheet(
        "QLabel {"
        "font-size: 12px;"
        "}"
        );
    d_taskReminderTimeInReminder->setStyleSheet("font-weight:500; font-size: 15px;");
    reminder_layout->setContentsMargins(0,0,0,0);
    reminder_layout->addWidget(reminder_label);
    reminder_layout->addWidget(d_taskReminderTimeInReminder);

    reminder_layout_button->setFixedSize(100,35);
    reminder_layout_button->setFlat(true);
    reminder_layout_button->setLayout(reminder_layout);

    reminder_widget_layout->setContentsMargins(0,0,0,0);
    reminder_widget_layout->addWidget(reminder_layout_button);

    // reminder_layout_button->setLayout(reminder_layout);
    // reminder_layout_button->setFlat(true);
    // reminder_widget_layout->addWidget(reminder_layout_button);

    reminder_widget->setLayout(reminder_widget_layout);
    reminder_widget->setVisible(false);
    reminder_widget->setStyleSheet("color : #D2232A;");

    p_ForthLayout->addWidget(reminder_widget);
    p_ForthLayout->addWidget(d_setReminderbtn);
    p_ForthLayout->addStretch();
    p_ForthLayout->addLayout(active_time_layout);

    d_containerLayout->addLayout(p_FirstLayout);
    // d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_SecondLayout);
    //    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ThirdLayout);
    //    d_containerLayout->addSpacerItem(spacer);
    // d_containerLayout->addStretch();
    d_containerLayout->addLayout(p_ForthLayout);
    // d_containerLayout->addWidget(hor_widget);

    // hor_layout->addLayout(d_containerLayout);
    // hor_layout->addWidget(deleteBtn);

    d_containerWidget->setLayout(d_containerLayout);

    setFixedSize(655,130);
    m_HMainLayout->addWidget(d_containerWidget);

    //    m_HMainLayout->addSpacerItem(spacer);
    //    m_HMainLayout->addLayout(p_SecondLayout);


    setLayout(m_HMainLayout);

    // Create a QGraphicsDropShadowEffect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setOffset(5, 5);
    shadow->setColor(QColor(0,0,0,35));

    // Apply the shadow effect to the label
    this->setGraphicsEffect(shadow);
    // this->setStyleSheet("QWidget {border-radius: 8px; }");

    // this->setStyleSheet(
    //     "QWidget { border-radius: 80px; }"
    //     // "QWidget > * { border: none; }"
    //     );
    // this->setStyleSheet("background-color: rgba(35, 31, 32, 0.1);"); // #231F20 with 10% opacity

    networkMgr = MyNetworkManager::instance();

    rmd_wid = new ReminderWidget();

    // signals and slots
    connect(m_startTimer,&QTimer::timeout,this,[=]{
        updateStartTimer();
    });

    connect(m_startReminderTimer,&QTimer::timeout,this,[=]{
        updateReminderTimer();
    });

    connect(d_startTaskButton,&QPushButton::clicked,this,&ProjectCustomWidget::startOrPauseTaskAction);

    connect(d_editTaskButton,&QPushButton::clicked,this,[=]{
        CreateTask * edit_task = new CreateTask();
        edit_task->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
        edit_task->nameLineEdit->setText(d_taskNameLabel->text());
        edit_task->createBtn->setText(tr("Update"));
        edit_task->setWindowTitle(tr("Edit Task"));
        edit_task->show();
        connect(edit_task,&CreateTask::sendToUpdateTask,this,[=]{
            qDebug() << "Executing the update task slot";
        });
    });

    connect(d_setReminderbtn,&QPushButton::clicked,this,[=]{
        rmd_wid->work_label->setText(d_projectNameLabel->text());
        rmd_wid->task_title_label->setText(d_taskNameLabel->text());
        rmd_wid->show();
        // int reminderTimeSecs = remindercountdownTime.secsTo(QTime::currentTime());
        // qDebug() << "reminderTimeSecs" << reminderTimeSecs;
        rmd_wid->getTokenAndTaskIdForReminderTimeSec(token,task_id);
    });

    connect(rmd_wid,&ReminderWidget::displayReminderTime,this,[=](QTime getremindertime){
        qDebug() << "in  displaying the reminder layout time slot";
        remindercountdownTime =getremindertime;
        reminder_widget->setVisible(true);
        d_setReminderbtn->setVisible(false);
        d_taskReminderTimeInReminder->setText(remindercountdownTime.toString("hh:mm:ss"));
        m_startReminderTimer->start();
    });

    connect(this,&ProjectCustomWidget::sendUpdateReminder,rmd_wid,&ReminderWidget::SetUpdateReminder);

    connect(reminder_layout_button,&QPushButton::clicked,this,[=]{
        qDebug() << "reminder_layout_button clicked ";
        rmd_wid->setWindowTitle(tr("Update Reminder"));
        rmd_wid->update_widget->setVisible(true);
        rmd_wid->show();
        emit sendUpdateReminder();
    });

    connect(rmd_wid,&ReminderWidget::resetReminderSignal,this,[=]{
        qDebug() << "in  displaying the reset reminder time slot";
        m_startReminderTimer->stop();
        remindercountdownTime = QTime(0,0,0);
        d_taskReminderTimeInReminder->setText("00:00:00");
        rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
        reminder_widget->setVisible(false);
        d_setReminderbtn->setVisible(true);
    });

    connect(completeBtn,&QPushButton::clicked,this,[=]{
        toFinishTask();
        qDebug() << "complete btn clicked ";
        d_startTaskButton->setVisible(false);
        d_editTaskButton->setVisible(false);
        completeBtn->setVisible(false);
        deleteBtn->setVisible(false);
        // active_time_layout->deleteLater();
        // delete active_time_layout;
        m_startTimer->stop();
        // d_projectStatuslabel->setText("Finish Task");
    });

    connect(deleteBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "delete btn clicked ";
        toDeleteTask();
    });
}

ProjectCustomWidget::ProjectCustomWidget(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    d_taskActiveTimeLabel->setText(taskActiveTime);
}

void ProjectCustomWidget::setProjectTaskDetails(QJsonObject jsonObject)
{
    // Parsing the fields of Task
    m_task.taskId = jsonObject.value("_id").toString();
    m_task.assignedUser = jsonObject.value("assigned_user").toInt();
    m_task.status = jsonObject.value("status").toInt();
    m_task.taskFinishedTime = QDateTime::fromString(jsonObject.value("task_finished_time").toString(), Qt::ISODate);
    m_task.taskRemainingTime = QDateTime::fromString(jsonObject.value("task_remaining_time").toString(), Qt::ISODate);
    m_task.name = jsonObject.value("name").toString();
    m_task.createdAt = QDateTime::fromString(jsonObject.value("createdAt").toString(), Qt::ISODate);
    m_task.activeTime = jsonObject.value("active_time").toInt();

    // Parsing the nested folder_data
    QJsonObject folderDataObject = jsonObject.value("folder_data").toObject();
    m_task.folderData.id = folderDataObject.value("_id").toString();
    m_task.folderData.name = folderDataObject.value("name").toString();

    // Parsing the nested project_data
    QJsonObject projectDataObject = jsonObject.value("project_data").toObject();
    m_task.projectData.id = projectDataObject.value("_id").toString();
    m_task.projectData.title = projectDataObject.value("title").toString();

    // // Print the Task struct values (using m_task)
    qDebug() << "Task ID:" << m_task.taskId;
    // qDebug() << "Assigned User:" << m_task.assignedUser;
    // qDebug() << "Status:" << m_task.status;
    // qDebug() << "Task Finished Time:" << (m_task.taskFinishedTime.isValid() ? m_task.taskFinishedTime.toString(Qt::ISODate) : "null");
    // qDebug() << "Task Remaining Time:" << (m_task.taskRemainingTime.isValid() ? m_task.taskRemainingTime.toString(Qt::ISODate) : "null");
    // qDebug() << "Task Name:" << m_task.name;
    // qDebug() << "Created At:" << m_task.createdAt.toString(Qt::ISODate);
    // qDebug() << "Active Time:" << m_task.activeTime;

    // // Print nested folderData
    // qDebug() << "Folder ID:" << m_task.folderData.id;
    // qDebug() << "Folder Name:" << m_task.folderData.name;

    // // Print nested projectData
    // qDebug() << "Project ID:" << m_task.projectData.id;
    // qDebug() << "Project Title:" << m_task.projectData.title;

    d_projectStatuslabel->setText(m_task.folderData.name);
    d_projectNameLabel->setText(m_task.projectData.title);
    d_taskNameLabel->setText(m_task.name);

}

// void ProjectCustomWidget::focusInEvent(QFocusEvent *event)
// {
// //    this->setStyleSheet(
// //        "background-color: #F2F9FF;"   // Set background color of the widget
// //        "border: 1px solid #D2232A;"    // Set border around the widget
// ////        "QWidget > QWidget { border: none; }"  // Ensure child widgets have no border
// //        );


//     this->setStyleSheet(
//         "#customProjectItemWidget {"
//         "    background-color: #F2F9FF;"   // Set background color
//         "    border: 2px solid #D2232A;"    // Set border only for this widget
//         "}"
//         "QWidget#customProjectItemWidget > * {"
//         "    border: none;"  // No border for any child widgets
//         "}"
//         );
//     // this->setStyleSheet("background-color: #f0dfe0;");

//      // border: 2px solid rgba(76, 156, 229, 1)
// //    this->setStyleSheet("background-color: #F2F9FF;"
// ////                        "QWidget { border: 1px solid black; }"

// ////                             "QWidget { border-radius: 80px; }"
// ////                              "QWidget > * { border: 1px solid black; }"
// //                        "border:1px solid #D2232A");
// //    this->setStyleSheet("QWidget {  border: 2px solid rgba(76, 156, 229, 1) }");
//     // completeBtn->show();
//     // deleteBtn->show();
//     QWidget::focusInEvent(event);
// }

// void ProjectCustomWidget::focusOutEvent(QFocusEvent *event)
// {
//     qDebug() << "focus out event " << event->type() << event->reason();
//     this->setStyleSheet("background-color: #F8F8F8;");
//     // completeBtn->hide();
//     // deleteBtn->hide();
//     QWidget::focusOutEvent(event);
// }

void ProjectCustomWidget::receiveData(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime, const QString &projectId)
{
    // qDebug()<<"received data  "<<taskName;
//    if(projectStatus == "current task"){
//        d_projectStatuslabel->s
//    }
    QLabel *textLabel = new QLabel("");
    textLabel->setStyleSheet("font-size : 13px; color: #414040;");
    QLabel *iconLabel = new QLabel;
    QHBoxLayout *statusLayout = new QHBoxLayout;

    if(projectStatus.contains("Current")){
        QIcon icon("://imgs/blue_icon.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText(tr("Current Tasks"));
    }else if(projectStatus.contains("Future")){
        QIcon icon(":/imgs/red_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText(tr("Future Tasks"));
    }else if(projectStatus.contains("Next")){
        QIcon icon("://imgs/yellow_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText(tr("Next Tasks"));
    }else if(projectStatus.contains("Completed")){
        QIcon icon("://imgs/green_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText(tr("Completed Tasks"));
    }else{
        d_projectStatuslabel->setText(projectStatus);
    }
    d_projectStatuslabel->setLayout(statusLayout);
    d_projectStatuslabel->setAlignment(Qt::AlignLeft);
    statusLayout->addWidget(iconLabel);
    statusLayout->addWidget(textLabel);
    statusLayout->addStretch();
    statusLayout->setMargin(0);


    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    // d_taskActiveTimeLabel->setText(taskActiveTime);
    task_id = taskActiveTime;
    project_id = projectId;
}

void ProjectCustomWidget::updateStartTimer()
{
    countdownTime = countdownTime.addSecs(1); // increment by one second
    d_taskActiveTimeLabel->setText(countdownTime.toString("hh:mm:ss"));
    // if(rmd_wid != nullptr){
    rmd_wid->d_taskActiveTimeInReminder->setText(countdownTime.toString("hh:mm:ss"));
    // }
}

void ProjectCustomWidget::startOrPauseTaskAction()
{
    bool value = networkMgr->toStartTask(token,m_task.taskId);
    qDebug() << "value " << value;
    if(!is_started && value){
        is_started = true;
        qDebug() << "setting is_started" <<  is_started;
        m_startTimer->start();
        start_label->setText(tr("Pause"));
        startbtn_layout->setContentsMargins(5,0,8,0);
        QPixmap pause_icon("://imgs/pause.png");
        start_icon->setPixmap(pause_icon);
        d_setReminderbtn->setVisible(true);
    }
    else{
        // toStopTask();
        is_started = false;
        qDebug() << "setting is_started" <<  is_started;
        m_startTimer->stop();
        m_startReminderTimer->stop();
        remindercountdownTime = QTime(0,0,0);
        start_label->setText(tr("Start"));
        start_icon->setPixmap(start_pic);
        // rmd_wid->deleteLater();
        // rmd_wid = new ReminderWidget();
        d_setReminderbtn->setVisible(false);
        reminder_widget->setVisible(false);
        rmd_wid->update_widget->setVisible(false);
        rmd_wid->custom_widget->setVisible(false);
        rmd_wid->custom_time_button->setStyleSheet(
            "QPushButton {"
            "background-color:  rgba(35, 31, 32, 0.1);"
            "border-radius: 10px;"
            "}"
            );
        rmd_wid->set_reminder_button->setVisible(true);
        d_taskReminderTimeInReminder->setText("00:00:00");
        rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
        startbtn_layout->setContentsMargins(9,0,13,0);
        // qDebug() << "startbtn_layout else" << startbtn_layout->contentsMargins();
        emit sendUpdateReminder();
    }
}

void ProjectCustomWidget::updateReminderTimer()
{
    remindercountdownTime = remindercountdownTime.addSecs(-1); // Decrement by one second
    d_taskReminderTimeInReminder->setText(remindercountdownTime.toString("hh:mm:ss"));
    rmd_wid->d_taskReminderTimeLabel->setText(remindercountdownTime.toString("hh:mm:ss"));
    if(remindercountdownTime.toString("hh:mm:ss").compare("00:00:00") == 0){
        qDebug() << "timer is null ";
        QMessageBox notify;
        notify.setText("reminder time completed of the task");
        // notify.exec();
        m_startReminderTimer->stop();
        remindercountdownTime = QTime(0,0,0);
        trayIcon = new QSystemTrayIcon(QIcon("C:/Users/GLB-BLR-304/Documents/Lightshot/Screenshot_5.png"), this);
        trayIcon->setVisible(true);

        trayIcon->showMessage(tr("SysTrayicon Title"), "This is the notification message.", QSystemTrayIcon::Information, 10000);

        connect(trayIcon, &QSystemTrayIcon::messageClicked, this,[=]{
            QString program = "notepad.exe";
            qDebug() << "in on message clicked slot";
            QStringList arguments;
            QProcess::startDetached(program, arguments);
        });

        reminder_widget->setVisible(false);
        d_setReminderbtn->setVisible(true);
    }
}

// void ProjectCustomWidget::getTimer(QTime get_reminder_time)
// {

// }

// void ProjectCustomWidget::toUpdateTask()
// {
//     QUrl url("https://track.dev.empmonitor.com/api/v3/project/create-project-task");   // 6704ed000e8f24f13150e509

//     QUrlQuery query;
//     // query.addQueryItem("skip", QString::number(10));
//     // query.addQueryItem("limit", QString::number(10));
//     query.addQueryItem("title", taskName);
//     query.addQueryItem("folder_name", folderName);
//     query.addQueryItem("project_id", project_id);
//     // query.addQueryItem("task_id","6704ed000e8f24f13150e509");
//     url.setQuery(query);
//     QNetworkRequest request(url);
//     request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     QNetworkReply *reply = networkManager->networkManager->get(request);
//     connect(reply, &QNetworkReply::finished, this, [reply, this](){
//         if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
//             QByteArray response = reply->readAll();
//             qDebug() <<"Project list "<<response;
//             QJsonDocument jsonDoc = QJsonDocument::fromJson(response);

//             QJsonObject jsonObj = jsonDoc.object();

//             QString message = jsonObj.value("message").toString();

//             // Check if the message contains "Project task created successfully"
//             if (message == "Project task created successfully") {
//                 // Display a message box
//                 QMessageBox::information(this, "Task Created", message);
//             } else {
//                 qDebug() << "Message does not contain the expected text!";
//             }
//         } else {
//             qDebug() << "Network reply error " << reply->errorString();
//         }
//     });
// }

void ProjectCustomWidget::toDeleteTask()
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/delete-project-task");   // 6704ed000e8f24f13150e509

    QUrlQuery query;
    query.addQueryItem("_id",task_id);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkMgr->networkManager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
            QByteArray response = reply->readAll();
            qDebug() <<"Delete Task Response "<<response;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);

            QJsonObject jsonObj = jsonDoc.object();

            QString message = jsonObj.value("message").toString();

            // Check if the message contains "Project task created successfully"
            if (message == "Project task deleted successfully") {
                this->deleteLater();
                // Display a message box
                QMessageBox::information(this, "Task Created", message);
            } else {
                qDebug() << "Message does not contain the expected text!";
                QMessageBox::information(this, "Delete Task", message);
            }
        } else {
            qDebug() << "Delete reply error " << reply->errorString();
        }
    });
}

// bool ProjectCustomWidget::toStartTask()
// {
//     QUrl url("https://track.dev.empmonitor.com/api/v3/project/start-project-task");

//     QUrlQuery query;
//     query.addQueryItem("task_id",m_task.taskId);
//     url.setQuery(query);
//     QNetworkRequest request(url);
//     request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     QNetworkReply *reply = networkMgr->networkManager->get(request);
//     connect(reply, &QNetworkReply::finished, this, [reply, this](){
//         QByteArray response = reply->readAll();
//         qDebug() <<"Start Task Response "<<response;
//             QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//             QJsonObject jsonObj = jsonDoc.object();
//             int statusCode = jsonObj.value("code").toInt();
//             QString message = jsonObj.value("message").toString();
//             if(statusCode == 200){
//                 if (message == "Task started successfully") {
//                     qDebug() << "Task started successfully";
//                     QMessageBox::information(this, "Start Task", message);
//                     return true;
//                 } else {
//                     qDebug() << "Message does not contain the expected text!";
//                     QMessageBox::information(this, "Start Task", message);
//                 }
//             }
//             else {
//                 QMessageBox::information(this, "Start Task", message);
//                 return false;
//             }
//     });
//     return false;
// }

void ProjectCustomWidget::toStopTask()
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/stop-project-task");

    QUrlQuery query;
    query.addQueryItem("task_id",task_id);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkMgr->networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
            QByteArray response = reply->readAll();
            // qDebug() <<"Stop Task Response "<<response;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            QString message = jsonObj.value("message").toString();
            if (message == "Task stop successfully") {
                QMessageBox::information(this, "Stop Task", message);
            } else {
                qDebug() << "Message does not contain the expected text!";
            }
        } else {
            qDebug() << "Task stop Network reply error " << reply->errorString();
        }
    });
}

void ProjectCustomWidget::toFinishTask()
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/finish-project-task");

    QUrlQuery query;
    query.addQueryItem("task_id",task_id);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkMgr->networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
            QByteArray response = reply->readAll();
            // qDebug() <<"Finish Task Response "<<response;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            QString message = jsonObj.value("message").toString();
            if (message == "Task finished successfully") {
                QMessageBox::information(this, "Task Finished", message);
            } else {
                qDebug() << "Message does not contain the expected text!";
            }
        } else {
            qDebug() << "Task finished Network reply error " << reply->errorString();
        }
    });
}
