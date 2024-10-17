#include "projectcustomwidget.h"
#include "qapplication.h"
#include "qdebug.h"
#include "QFocusEvent"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    initializeUIOfProjectsAndTasks();
}

void ProjectCustomWidget::initializeUIOfProjectsAndTasks()
{
    networkManager = MyNetworkManager::instance();

    m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(2,2,2,2);
    m_HMainLayout->setAlignment(Qt::AlignLeft);
    ActiveTaskQTime = QTime(0, 0, 0);
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

    taskSpecificTimer = new QTimer(this);

    // hor_layout->addWidget(completeBtn);
    QIcon complete_icon("://imgs/completed.svg");
    completeBtn->setIcon(complete_icon);
    completeBtn->setFixedSize(24,24);
    completeBtn->setIconSize(QSize(24,24));
    completeBtn->setStyleSheet("border-radius: 2px;");

    deleteBtn = new QPushButton(this);
    // deleteBtn->setStyleSheet("background-color: #fa3c36  ; color: white;");
    // deleteBtn->setFixedSize(20,this->height());
    QIcon deleteIcon(":/imgs/delete.svg");
    deleteBtn->setIcon(deleteIcon);
    deleteBtn->setFlat(true);
    deleteBtn->setIconSize(QSize(24,24));
    deleteBtn->setFixedSize(24,24);
    deleteBtn->setStyleSheet("border-radius: 2px;");



    d_containerLayout = new QVBoxLayout();
    d_containerLayout->setContentsMargins(10,10,15,10);
    d_containerWidget->setObjectName("projectContainerObject");

    // QSpacerItem *spacer = new QSpacerItem(5,3);

    d_projectStatuslabel = new QLabel(tr(""), this);  // shyad public karke access dena hoga
    d_projectStatuslabel->setObjectName("d_projectStatuslabel");
    d_startTaskButton = new QPushButton(this);
    d_pauseTaskButton = new QPushButton(this); // new added by dk
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
    d_projectNameLabel =  new QLabel("Project Name",this);
    d_projectNameLabel->setObjectName("d_projectNameLabel");

    //==================================================
    d_taskNameLabel = new QLabel("Task Title",this);
    d_taskNameLabel->setObjectName("d_taskNameLabel");
    //==================================================
    d_setReminderbtn = new QPushButton("Set reminder",this);
    d_setReminderbtn->setObjectName("reminderbtnObj");
    d_setReminderbtn->setVisible(false);
    d_setReminderbtn->setFlat(true);
    QFont d_setReminderbtn_font = d_setReminderbtn->font();
    d_setReminderbtn_font.setUnderline(true);
    d_setReminderbtn->setFont(d_setReminderbtn_font);
    d_setReminderbtn->setStyleSheet(
        "QPushButton {"
        "color: #D2232A;"               // Text color
        "}"
        );


    QVBoxLayout * active_time_layout = new QVBoxLayout();
    QLabel * active_task_time = new QLabel("Active Task Time");
    active_task_time->setObjectName("active_task_time");

    d_taskActiveTimeLabel = new QLabel(activeTime,this);
    d_taskActiveTimeLabel->setObjectName("d_taskActiveTimeLabel");
    // d_taskActiveTimeLabel->setFixedHeight(23);


    // active_time_layout->setAlignment(Qt::AlignCenter);
    active_time_layout->setContentsMargins(0,0,0,0);
    // active_time_layout->addStretch();
    active_time_layout->addWidget(active_task_time);
    active_time_layout->addWidget(d_taskActiveTimeLabel);

    QHBoxLayout * startbtn_layout = new QHBoxLayout();
    QLabel * start_icon = new QLabel();
    start_icon->setStyleSheet("background-color: #D2232A; color:#FFFFFF");
    // QPixmap start_pic("://imgs/start.png");
    QIcon icon("://imgs/start.png");
    QSize iconSize(12,12);
    QPixmap pixmap = icon.pixmap(iconSize);
    // QIcon resizedIcon(pixmap);
    QLabel * start_label = new QLabel(tr("Start"),this);
    start_label->setStyleSheet("background-color: #D2232A; color:#FFFFFF ; font-size: 11px; ");
    //    start_label->setStyleSheet("background-color: #8be51e");

    //    start_label->setStyleSheet("color: #FFFFFF;");
    start_icon->setPixmap(pixmap);


    startbtn_layout->setContentsMargins(6,0,13,0);
    // startbtn_layout->addSpacing(5);
    startbtn_layout->addStretch();
    startbtn_layout->addWidget(start_icon);
    startbtn_layout->addStretch();
    startbtn_layout->addWidget(start_label);
    startbtn_layout->addStretch();

    d_startTaskButton->setFixedSize(80,24);
    d_startTaskButton->setLayout(startbtn_layout);
    d_startTaskButton->setStyleSheet(
        "QPushButton {"
        "background-color: #D2232A;"
        "border-radius: 11px;"
        "}"
        );

    QHBoxLayout * pausebtn_layout = new QHBoxLayout();
    QLabel * pause_icon = new QLabel();
    pause_icon->setStyleSheet("background-color: #D2232A; color:#FFFFFF");
    QPixmap pause_pic(":/imgs/pause.png");
    QLabel * pause_label = new QLabel(tr("Pause"),this);
    pause_label->setStyleSheet("background-color: #D2232A; color:#FFFFFF ; font-size: 11px;");

    pause_icon->setPixmap(pause_pic);

    pausebtn_layout->setContentsMargins(3,0,13,0);
    pausebtn_layout->addSpacing(5);
    pausebtn_layout->addWidget(pause_icon);
    pausebtn_layout->addWidget(pause_label);

    d_pauseTaskButton->setLayout(pausebtn_layout);
    d_pauseTaskButton->setFixedSize(80,24);
    //    d_pauseTaskButton->setLayout(startbtn_layout);
    d_pauseTaskButton->setStyleSheet(
        "QPushButton {"
        "background-color: #D2232A;"
        "border-radius: 11px;"
        "}"
        );

    QHBoxLayout * editbtn_layout = new QHBoxLayout();
    QLabel * edit_icon = new QLabel();
    QPixmap edit_pic("://imgs/edit.svg");
    QLabel * edit_label = new QLabel("Edit",this);

    edit_icon->setStyleSheet("border-top:1px solid #D2232A;border-bottom:1px solid #D2232A; ");
    edit_icon->setPixmap(edit_pic);
    edit_label->setStyleSheet("color : #D2232A; border-top:1px solid #D2232A;border-bottom:1px solid #D2232A; ");

    editbtn_layout->setContentsMargins(9,0,13,0);
    editbtn_layout->addStretch();
    editbtn_layout->addStretch();
    editbtn_layout->addWidget(edit_icon);
    editbtn_layout->addStretch();
    editbtn_layout->addWidget(edit_label);
    editbtn_layout->addStretch();
    editbtn_layout->addStretch();

    d_editTaskButton->setFixedSize(80,24);
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

    if(m_taskStatus != 3 ){     // completed task case
        p_FirstLayout->addWidget(d_startTaskButton);
        p_FirstLayout->addWidget(d_pauseTaskButton);
        p_FirstLayout->addWidget(d_editTaskButton);
        p_FirstLayout->addWidget(completeBtn);
    }
    p_FirstLayout->addWidget(deleteBtn);
    completeBtn->hide();
    deleteBtn->hide();


    p_SecondLayout = new QHBoxLayout;
    p_SecondLayout->setContentsMargins(0,0,0,0);
    p_SecondLayout->addWidget(d_projectNameLabel,Qt::AlignLeft);

    p_ThirdLayout = new QHBoxLayout;
    p_ThirdLayout->setContentsMargins(0,0,0,0);
    p_ThirdLayout->addWidget(d_taskNameLabel,Qt::AlignLeft);

    p_ForthLayout = new QHBoxLayout;
    p_ForthLayout->setContentsMargins(0,0,0,0);

    reminder_widget = new QWidget();
    QVBoxLayout * reminder_widget_layout = new QVBoxLayout();
    QPushButton * reminder_layout_button = new QPushButton();
    QVBoxLayout * reminder_layout = new QVBoxLayout();
    QLabel * reminder_label = new QLabel("Remaining Time");
    d_taskRemainingTime = new QLabel("00:00:00");

    reminder_label->setStyleSheet(
        "QLabel {"
        "font-size: 12px;"
        "}"
        );
    reminder_layout->setContentsMargins(0,0,0,0);
    reminder_layout->addWidget(reminder_label);
    reminder_layout->addWidget(d_taskRemainingTime);

    reminder_layout_button->setFixedSize(100,35);
    reminder_layout_button->setFlat(true);
    reminder_layout_button->setLayout(reminder_layout);

    reminder_widget_layout->setContentsMargins(0,0,0,0);
    reminder_widget_layout->addWidget(reminder_layout_button);

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

    setFixedSize(655,140);
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

    rmd_wid = new ReminderWidget(this);

    connect(d_editTaskButton,&QPushButton::clicked,this,[this](){
        if(!edit_task){
            edit_task = new CreateTask(this);
            edit_task->TaskId = task_id;
            edit_task->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
            edit_task->setAttribute(Qt::WA_DeleteOnClose);
            edit_task->nameLineEdit->setText(d_taskNameLabel->text());
            edit_task->createBtn->setText("Update");
            edit_task->setWindowTitle("Edit Task");
            edit_task->show();
            connect(edit_task, &QWidget::destroyed, this, [this]() {
                qDebug() << "edit_task Widget destroyed!";
                edit_task = nullptr;
            });
        }
    });

    // signals and slots
    connect(m_startTimer,&QTimer::timeout,this,[=]{
        updateStartTimer();
    });

    connect(m_startReminderTimer,&QTimer::timeout,this,[=]{
        updateReminderTimer();
    });

    connect(taskSpecificTimer,&QTimer::timeout,this,[=]{
        ActiveTaskQTime = ActiveTaskQTime.addSecs(1);
        updatetaskSpecificTimer(ActiveTaskQTime);
    });

    connect(networkManager,&MyNetworkManager::taskStartDataSignal,this,&ProjectCustomWidget::taskStartDataSlot);

    connect(d_startTaskButton,&QPushButton::clicked,this,[=]{
        // networkManager->checkTaskAndStart(token,task_id);

        qDebug()<<"++++++++++++ : "<<activeTime;
        qDebug()<<"start api called";
        networkManager->startTaskApi(token,task_id);  // need to remove other things and move them in slot that will be called by this api call reply finished
        //        taskSpecificTimer->start(1);
        //        if(!is_started){
        //            is_started = true;
        //            qDebug() << "setting is_started" <<  is_started;
        //            m_startTimer->start();
        //            start_label->setText("Pause");
        //            startbtn_layout->setContentsMargins(5,0,8,0);
        //            QPixmap pause_icon("://imgs/pause.png");
        //            start_icon->setPixmap(pause_icon);
        //            d_setReminderbtn->setVisible(true);
        //            qDebug() << "startbtn_layout if " << startbtn_layout->contentsMargins();
        //        }
        //        else{
        //            is_started = false;
        //            qDebug() << "setting is_started" <<  is_started;
        //            m_startTimer->stop();
        //            m_startReminderTimer->stop();
        //            remindercountdownTime = QTime(0,0,0);
        //            start_label->setText("Start");
        //            start_icon->setPixmap(start_pic);
        //            // rmd_wid->deleteLater();
        //            // rmd_wid = new ReminderWidget();
        //            d_setReminderbtn->setVisible(false);
        //            reminder_widget->setVisible(false);
        //            rmd_wid->update_widget->setVisible(false);
        //            rmd_wid->custom_widget->setVisible(false);
        //            rmd_wid->custom_time_button->setStyleSheet(
        //                "QPushButton {"
        //                "background-color:  rgba(35, 31, 32, 0.1);"
        //                "border-radius: 10px;"
        //                "}"
        //                );
        //            rmd_wid->set_reminder_button->setVisible(true);
        //            d_taskRemainingTime->setText("00:00:00");
        //            rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
        //            startbtn_layout->setContentsMargins(9,0,13,0);
        //            qDebug() << "startbtn_layout else" << startbtn_layout->contentsMargins();
        //            emit sendUpdateReminder();
        //        }
    });

    connect(d_pauseTaskButton,&QPushButton::clicked,this,[=]{
        qDebug()<<"stop api called";
        networkManager->stopTaskApi(token,task_id);  // need to remove other things and move them in slot that will be called by this api call reply finished
        //        taskSpecificTimer->stop();

        //        qDebug()<<"---------- : "<<this->activeTime;
    });

    connect(d_setReminderbtn,&QPushButton::clicked,this,[=]{
        qDebug() << "d_setReminderbtn button clicked " << d_setReminderbtn;
        // rmd_wid->d_taskActiveTimeInReminder->setText(countdownTime.toString("hh:mm:ss"));
        rmd_wid->show();
    });

    connect(rmd_wid,&ReminderWidget::displayReminderTime,this,[=](QTime getremindertime){
        qDebug() << "in  displaying the reminder layout time slot";
        remindercountdownTime =getremindertime;
        reminder_widget->setVisible(true);
        d_setReminderbtn->setVisible(false);
        d_taskRemainingTime->setText(remindercountdownTime.toString("hh:mm:ss"));
        m_startReminderTimer->start();
    });

    connect(this,&ProjectCustomWidget::sendUpdateReminder,rmd_wid,&ReminderWidget::SetUpdateReminder);

    connect(reminder_layout_button,&QPushButton::clicked,this,[=]{
        qDebug() << "reminder_layout_button clicked ";
        rmd_wid->update_widget->setVisible(true);
        rmd_wid->show();
        emit sendUpdateReminder();
    });

    connect(rmd_wid,&ReminderWidget::resetReminderSignal,this,[=]{
        qDebug() << "in  displaying the reset reminder time slot";
        m_startReminderTimer->stop();
        remindercountdownTime = QTime(0,0,0);
        d_taskRemainingTime->setText("00:00:00");
        rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
        reminder_widget->setVisible(false);
        qDebug() << "reminder_widget - set visible is false 2";
        d_setReminderbtn->setVisible(true);
    });

    connect(completeBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "complete btn clicked ";
        m_startTimer->stop();
        //        d_startTaskButton->setVisible(false);
        //        d_editTaskButton->setVisible(false);
        //        d_projectStatuslabel->setText("Finish Task");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Complete Task");
        msgBox.setText("Are you sure you want to mark completed the task?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);  // Default focus on "No" to prevent yes if user clicks  on no

        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes) {
            qDebug() << "Task completed!";
            networkManager->completedTaskApi(token,task_id);
        } else {
            qDebug() << "Task not completed."; // No clicked: Do nothing
            networkManager->fetchTasksForMobileList(token,10); // this will reload all tasks when delete failed
        }

    });

    connect(deleteBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "delete btn clicked " << task_id;

        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete Task");
        msgBox.setText("Are you sure you want to delete the task?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);  // Default focus on "No" to prevent yes if user clicks  on no

        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes) {
            qDebug() << "Task deleted!";
            networkManager->deleteTaskApi(token,task_id);
        } else {
            qDebug() << "Task not deleted."; // No clicked: Do nothing
            networkManager->fetchTasksForMobileList(token,10); // this will reload all tasks when delete failed
        }
    });
}

ProjectCustomWidget::ProjectCustomWidget(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    d_taskActiveTimeLabel->setText(taskActiveTime);
}

void ProjectCustomWidget::focusInEvent(QFocusEvent *event)
{
    this->setStyleSheet("background-color: #F2F9FF;");
    drawBorder = true; // Enable border drawing
    update(); // Trigger repaint
    if(m_taskStatus == 3 ){
        deleteBtn->show();
        d_startTaskButton->hide();
    }else{
        completeBtn->show();
        deleteBtn->show();
    }
    QWidget::focusInEvent(event);
}

void ProjectCustomWidget::focusOutEvent(QFocusEvent *event)
{
    QWidget *newFocusWidget = QApplication::focusWidget();
    drawBorder = false; // Enable border drawing
    update(); // Trigger repaint
    if (newFocusWidget && this->isAncestorOf(newFocusWidget)) {
        // If the new focus is a child widget, do not hide the buttons
        event->ignore();
    }else {
        // If the focus is moving away from the parent and its children, hide buttons
        this->setStyleSheet("background-color: #F8F8F8;");
        completeBtn->hide();
        deleteBtn->hide();

        QWidget::focusOutEvent(event);  // Call base class method
    }
}

void ProjectCustomWidget::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    isSwipeDetected = false;
}

void ProjectCustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint distance = event->pos() - startPos;
    // If horizontal swipe is detected
    if (!isSwipeDetected && (qAbs(distance.x()) > swipeThreshold)) {
        isSwipeDetected = true;
    }
}

void ProjectCustomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isSwipeDetected) {
        QPoint distance = event->pos() - startPos;
        // Emit signal based on swipe direction
        if (distance.x() > 0) {
            qDebug()<<"R swipe";
            /*            this->setContentsMargins(50,10,10,10);*/
        } else if (distance.x() < 0) {
            qDebug()<<"L swipe";
        }
    }
    // Reset after releasing the mouse
    startPos = QPoint();
    isSwipeDetected = false;
}

void ProjectCustomWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Enable antialiasing for smoother edges
    if (drawBorder) { // Only draw border if the widget is clicked or focused
        painter.setPen(QPen(QColor(76, 156, 229, 255),1)); // Set pen color and border thickness   border: 1px solid rgba(76, 156, 229, 1)
        // painter.drawRect(rect().adjusted(1, 1, -1, -1)); // Draw border inside widget's boundaries
    } else {
        // border: 1px solid rgba(35, 31, 32, 0.1)
        painter.setPen(QPen(QColor(35, 31, 32, 255),0.2));
    }
    int radius = 8; // Set the border radius
    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), radius, radius); // Draw a rounded rectangle
}

QString ProjectCustomWidget::secondsToTimeFormat(int totalSeconds)
{
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    // Using sprintf for better performance
    char timeStr[9]; // Format is always "HH:MM:SS", 8 characters + null terminator
    sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);

    return QString(timeStr); // Convert C string to QString
}

int ProjectCustomWidget::timeFormatToSeconds(const QString &time)
{
    int hours = 0, minutes = 0, seconds = 0;
    std::string timeStr = time.toStdString();
    if (sscanf_s(timeStr.c_str(), "%d:%d:%d", &hours, &minutes, &seconds) != 3) {
        // Invalid format, handle accordingly
        return -1;
    }
    return hours * 3600 + minutes * 60 + seconds;
}

void ProjectCustomWidget::toStartTask(int activeTime)
{
    qDebug() << "in start task functionality " << activeTime;
    d_startTaskButton->setVisible(false);
    d_pauseTaskButton->setVisible(true);
    d_setReminderbtn->setVisible(true);
    taskSpecificTimer->start(1000);
    //        updatetaskSpecificTimer(m_taskActiveTime.toInt());
    qDebug()<<"+++ ActiveTaskQTime : "<<ActiveTaskQTime;
    ActiveTaskQTime.addSecs(activeTime);
    qDebug()<<"--- ActiveTaskQTime : "<< ActiveTaskQTime;
    //        activeTime = m_taskActiveTime.toInt();
    if(!remainingTime.isEmpty()){
        QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
        QDateTime reminderdatetime = QDateTime::fromString(remainingTime, Qt::ISODate);
        qDebug() << "Qdate time " << reminderdatetime << remainingTime;
        if (currentDateTime < reminderdatetime) {
            qDebug() << "datetime is in the future compared to currentDateTime";
            int remintimesecs = qAbs(currentDateTime.secsTo(reminderdatetime));
            qDebug() << "Remaining time in seconds:" << remintimesecs;
            remindercountdownTime = QTime(0, 0).addSecs(remintimesecs);
            d_taskRemainingTime->setText(remindercountdownTime.toString("hh:mm:ss"));
            qDebug() << "Reminder countdown time set:" << remindercountdownTime.toString("hh:mm:ss");
            m_startReminderTimer->start(1000);
            d_setReminderbtn->setVisible(false);
            reminder_widget->setVisible(true);
        } else {
            qDebug() << "datetime is in the past compared to currentDateTime";
        }
    }
}

void ProjectCustomWidget::toStopTask()
{

}

void ProjectCustomWidget::setTaskProjectsIdNameinProjectCustomWidget(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskid)
{
    QLabel *textLabel = new QLabel("");
    textLabel->setStyleSheet("font-size : 13px; color: #414040;");
    QLabel *iconLabel = new QLabel;
    QHBoxLayout *statusLayout = new QHBoxLayout;

    if(projectStatus.contains("Current")){
        QIcon icon("://imgs/blue_icon.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Current Task");
    }
    else if(projectStatus.contains("Next")){
        QIcon icon("://imgs/yellow_circle.png");
        iconLabel->setPixmap(icon.pixmap(15,15));
        textLabel->setText("Next Task");
    }
    else if(projectStatus.contains("Future")){
        QIcon icon(":/imgs/red_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Future Task");
    }
    else if(projectStatus.contains("Completed")){
        QIcon icon("://imgs/green_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Future Task");
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
    task_id = taskid;
    //    qDebug() << "Task id " << task_id;
}

void ProjectCustomWidget::setTaskAllDataInProjectCustomWidget(const QString &taskid, int taskStatus, const QString &taskName, const QString &m_taskActiveTime, const QString &m_taskRemainingTime,
                                                              const QString &projectStatus, const QString &taskProjectId, const QString &m_taskFinishedTime, const QString &projectName)
{
    //    qDebug()<<"received data now setting in projectcustom widget for task: "<<taskName <<projectStatus;
    QLabel *textLabel = new QLabel("");
    textLabel->setStyleSheet("font-size : 13px; color: #414040;");
    QLabel *iconLabel = new QLabel;
    QHBoxLayout *statusLayout = new QHBoxLayout;

    if(projectStatus.contains("Current")){
        QIcon icon("://imgs/blue_icon.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Current Task");
    }
    else if(projectStatus.contains("Next")){
        QIcon icon("://imgs/yellow_circle.png");
        iconLabel->setPixmap(icon.pixmap(15,15));
        textLabel->setText("Next Task");
    }
    else if(projectStatus.contains("Future")){
        QIcon icon(":/imgs/red_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Future Task");
    }
    else if(projectStatus.contains("Finished")){
        QIcon icon("://imgs/green_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Finished Task");
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
    task_id = taskid;
    m_taskStatus = taskStatus;
    remainingTime = m_taskRemainingTime;
    activeTime = m_taskActiveTime;
    FinishedTime = m_taskFinishedTime;

    qDebug() << "task name " << taskName << "task id " << task_id;

    rmd_wid->setTaskIdForReminder(task_id);
    ActiveTaskQTime = QTime(0, 0, 0).addSecs(m_taskActiveTime.toInt());

    d_taskActiveTimeLabel->setText(secondsToTimeFormat(activeTime.toInt()));

    switch (m_taskStatus) {
    case 0:
        d_startTaskButton->setVisible(true);
        d_pauseTaskButton->setVisible(false);
        d_setReminderbtn->setVisible(false);
        break;
    case 1:
        toStartTask(m_taskActiveTime.toInt());
        // d_startTaskButton->setVisible(false);
        // d_pauseTaskButton->setVisible(true);
        // d_setReminderbtn->setVisible(true);
        // taskSpecificTimer->start(1000);
        // //        updatetaskSpecificTimer(m_taskActiveTime.toInt());
        // qDebug()<<"+++ ActiveTaskQTime : "<<ActiveTaskQTime;
        // ActiveTaskQTime.addSecs(m_taskActiveTime.toInt());
        // qDebug()<<"--- ActiveTaskQTime : "<< ActiveTaskQTime;
        // //        activeTime = m_taskActiveTime.toInt();
        // if(!remainingTime.isEmpty()){
        //     QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
        //     QDateTime reminderdatetime = QDateTime::fromString(remainingTime, Qt::ISODate);
        //     qDebug() << "Qdate time " << reminderdatetime << remainingTime;
        //     if (currentDateTime < reminderdatetime) {
        //         qDebug() << "datetime is in the future compared to currentDateTime";
        //         int remintimesecs = qAbs(currentDateTime.secsTo(reminderdatetime));
        //         qDebug() << "Remaining time in seconds:" << remintimesecs;
        //         remindercountdownTime = QTime(0, 0).addSecs(remintimesecs);
        //         d_taskRemainingTime->setText(remindercountdownTime.toString("hh:mm:ss"));
        //         qDebug() << "Reminder countdown time set:" << remindercountdownTime.toString("hh:mm:ss");
        //         m_startReminderTimer->start(1000);
        //         d_setReminderbtn->setVisible(false);
        //         reminder_widget->setVisible(true);
        //     } else {
        //         qDebug() << "datetime is in the past compared to currentDateTime";
        //     }
        // }
        break;
    case 2:
        d_startTaskButton->setVisible(true);
        d_pauseTaskButton->setVisible(false);
        d_setReminderbtn->setVisible(false);
        taskSpecificTimer->stop();
        break;
    case 3:
        d_startTaskButton->setVisible(false);
        d_editTaskButton->setVisible(false);
        d_pauseTaskButton->setVisible(false);
        d_setReminderbtn->setVisible(false);
        //        p_FirstLayout->removeWidget(completeBtn);
        completeBtn->hide();
        break;
    default:
        qDebug()<<"project is in default switch case";
        break;
    }

    // qDebug() << "taskName" << taskName << "Task id " << task_id;
}

void ProjectCustomWidget::receiveData(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    qDebug()<<"received data  "<<taskName;

    QLabel *textLabel = new QLabel("");
    textLabel->setStyleSheet("font-size : 13px; color: #414040;");
    QLabel *iconLabel = new QLabel;
    QHBoxLayout *statusLayout = new QHBoxLayout;

    if(projectStatus.contains("Current")){
        QIcon icon("://imgs/blue_icon.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Current Task");
    }
    else if(projectStatus.contains("Next")){
        QIcon icon("://imgs/yellow_circle.png");
        iconLabel->setPixmap(icon.pixmap(15,15));
        textLabel->setText("Next Task");
    }
    else if(projectStatus.contains("Future")){
        QIcon icon(":/imgs/red_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Future Task");
    }else if(projectStatus.contains("Next")){
        QIcon icon("://imgs/yellow_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Next Task");
    }else if(projectStatus.contains("Completed")){
        QIcon icon("://imgs/green_circle.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Future Task");
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
    qDebug() << "Task id " << task_id;
}

void ProjectCustomWidget::updateStartTimer()
{
    countdownTime = countdownTime.addSecs(1); // increment by one second
    d_taskActiveTimeLabel->setText(countdownTime.toString("hh:mm:ss"));
    // if(rmd_wid != nullptr){
    rmd_wid->d_taskActiveTimeInReminder->setText("countdownTime");
    // }
}

void ProjectCustomWidget::taskStartDataSlot(const QString &taskid, bool success, const QString &time)
{
//    qDebug()<<"it will manage the data from the slot when start is done" << time;
    switch (m_taskStatus) {
    case 0:
        qDebug()<<"project is not started switch case";
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    default:
        qDebug()<<"project is in default switch case";
        break;
    }
    if(m_taskStatus == 1){
        //        qDebug()<<"success of start task";
        d_startTaskButton->setVisible(false);
        d_pauseTaskButton->setVisible(true);
    }else{
        //        qDebug()<<"fail of start task";
        d_startTaskButton->setVisible(true);
        d_pauseTaskButton->setVisible(false);
    }
}

void ProjectCustomWidget::updateReminderTimer()
{
    remindercountdownTime = remindercountdownTime.addSecs(-1); // Decrement by one second
    d_taskRemainingTime->setText(remindercountdownTime.toString("hh:mm:ss"));
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

        trayIcon->showMessage("SysTrayicon Title", "This is the notification message.", QSystemTrayIcon::Information, 10000);

        connect(trayIcon, &QSystemTrayIcon::messageClicked, this,[=]{
            QString program = "notepad.exe";
            qDebug() << "in on message clicked slot";
            QStringList arguments;
            QProcess::startDetached(program, arguments);
        });

        reminder_widget->setVisible(false);
        qDebug() << "reminder_widget - set visible is false 3";
        d_setReminderbtn->setVisible(true);
    }
}

void ProjectCustomWidget::getTimer(QTime get_reminder_time)
{

}

void ProjectCustomWidget::updatetaskSpecificTimer(QTime myQTime)
{
    QString timeString = myQTime.toString("hh:mm:ss");  // Convert QTime to QString in "hh:mm:ss" format
    d_taskActiveTimeLabel->setText(timeString);
    rmd_wid->d_taskActiveTimeInReminder->setText(timeString);
//    qDebug()<<"int time is "<<  myQTime <<" in updatetaskSpecificTimer";
}
