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
    this->setObjectName("customProjectItemWidget") ;
    // this->setStyleSheet("background-color: rgba(35, 31, 32, 0.1);");
    d_containerWidget = new QWidget(this);

    // QHBoxLayout * hor_layout = new QHBoxLayout(d_containerWidget);
    // hor_layout->setContentsMargins(0,0,0,0);
    QPushButton *completeBtn = new QPushButton(this);
    // completeBtn->setFixedSize(20,this->height());
    // completeBtn->setStyleSheet("background-color: #8be51e; color: white;");

    // hor_layout->addWidget(completeBtn);
    QIcon complete_icon("://imgs/completed.svg");
    completeBtn->setIcon(complete_icon);
    completeBtn->setFixedSize(29,29);
    completeBtn->setIconSize(QSize(29,29));
    completeBtn->setStyleSheet("border-radius: 2px;");

    QPushButton *deleteBtn = new QPushButton(this);
    // deleteBtn->setStyleSheet("background-color: #fa3c36  ; color: white;");
    // deleteBtn->setFixedSize(20,this->height());
    QIcon deleteIcon(":/imgs/delete.svg");
    deleteBtn->setIcon(deleteIcon);
    deleteBtn->setFlat(true);
    deleteBtn->setIconSize(QSize(29,29));
    deleteBtn->setFixedSize(29,29);
    deleteBtn->setStyleSheet("border-radius: 2px;");



    d_containerLayout = new QVBoxLayout();
    d_containerLayout->setContentsMargins(10,10,5,5);
    d_containerWidget->setObjectName("projectContainerObject");

    // QSpacerItem *spacer = new QSpacerItem(5,3);

    d_projectStatuslabel = new QLabel(tr(""), this);  // shyad public karke access dena hoga
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
    d_projectNameLabel =  new QLabel("Project Name",this);
    d_projectNameLabel->setObjectName("d_projectNameLabel");

    //==================================================
    d_taskNameLabel = new QLabel("Task Title",this);
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

    d_taskActiveTimeLabel = new QLabel("00:00:00",this);
    d_taskActiveTimeLabel->setObjectName("d_taskActiveTimeLabel");
    // d_taskActiveTimeLabel->setFixedHeight(23);
    active_task_time->setStyleSheet(
        "QLabel {"
        "color : #0F5EA9;"
        "font-size: 12px;"
        "}"
        );
    d_taskActiveTimeLabel->setStyleSheet(
        "QLabel {"
        "color : #0F5EA9;"
        "}"
        );

    QFont active_time_font;
    active_time_font.setPointSize(11);

    d_taskActiveTimeLabel->setFont(active_time_font);

    // active_time_layout->setAlignment(Qt::AlignCenter);
    active_time_layout->setContentsMargins(0,0,0,0);
    // active_time_layout->addStretch();
    active_time_layout->addWidget(active_task_time);
    active_time_layout->addWidget(d_taskActiveTimeLabel);

    QHBoxLayout * startbtn_layout = new QHBoxLayout();
    QLabel * start_icon = new QLabel();
    QPixmap start_pic("://imgs/start.png");
    QLabel * start_label = new QLabel(tr("Start"),this);

    start_label->setStyleSheet("color: #FFFFFF;");
    start_icon->setPixmap(start_pic);

    startbtn_layout->setContentsMargins(9,0,13,0);
    startbtn_layout->addWidget(start_icon);
    startbtn_layout->addWidget(start_label);

    d_startTaskButton->setFixedSize(68,29);
    d_startTaskButton->setLayout(startbtn_layout);
    d_startTaskButton->setStyleSheet(
        "QPushButton {"
        "background-color: #D2232A;"
        "border-radius: 10px;"
        "}"
        );

    QHBoxLayout * editbtn_layout = new QHBoxLayout();
    QLabel * edit_icon = new QLabel();
    QPixmap edit_pic("://imgs/edit.svg");
    QLabel * edit_label = new QLabel("Edit",this);

    // edit_label->setStyleSheet("color: #FFFFFF;");
    edit_icon->setPixmap(edit_pic);
    edit_label->setStyleSheet("color : #D2232A;");

    editbtn_layout->setContentsMargins(9,0,13,0);
    editbtn_layout->addWidget(edit_icon);
    editbtn_layout->addWidget(edit_label);

    d_editTaskButton->setFixedSize(68,29);
    d_editTaskButton->setLayout(editbtn_layout);
    d_editTaskButton->setStyleSheet(
        "QPushButton {"
        "border: 1px solid #D2232A;"
        // "background-color: #D2232A;"
        "border-radius: 10px;"
        "}"
        );


    p_FirstLayout = new QHBoxLayout;
    p_FirstLayout->setContentsMargins(0,0,0,0);
    p_FirstLayout->addWidget(d_projectStatuslabel);
    p_FirstLayout->addStretch();
    p_FirstLayout->addWidget(d_startTaskButton);
    p_FirstLayout->addWidget(d_editTaskButton);
    p_FirstLayout->addWidget(completeBtn);
    p_FirstLayout->addWidget(deleteBtn);


    p_SecondLayout = new QHBoxLayout;
    p_SecondLayout->setContentsMargins(0,0,0,0);
    p_SecondLayout->addWidget(d_projectNameLabel,Qt::AlignLeft);

    p_ThirdLayout = new QHBoxLayout;
    p_ThirdLayout->setContentsMargins(0,0,0,0);
    p_ThirdLayout->addWidget(d_taskNameLabel,Qt::AlignLeft);

    p_ForthLayout = new QHBoxLayout;
    p_ForthLayout->setContentsMargins(0,0,0,0);

    // QWidget * hor_widget = new QWidget();
    // hor_widget->setLayout(p_ForthLayout);
    // hor_widget->setStyleSheet("QWidget { border: 1px solid black; }");

    reminder_widget = new QWidget();
    QVBoxLayout * reminder_widget_layout = new QVBoxLayout();
    QPushButton * reminder_layout_button = new QPushButton();
    QVBoxLayout * reminder_layout = new QVBoxLayout();
    QLabel * reminder_label = new QLabel("Remaining Time");
    d_taskActiveTimeInReminder = new QLabel("00:00:00");

    d_taskActiveTimeInReminder->setFont(active_time_font);
    reminder_label->setStyleSheet(
        "QLabel {"
        "font-size: 12px;"
        "}"
        );
    reminder_layout->setContentsMargins(0,0,0,0);
    reminder_layout->addWidget(reminder_label);
    reminder_layout->addWidget(d_taskActiveTimeInReminder);

    reminder_layout_button->setFixedSize(100,32);
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

    setFixedSize(600,125);
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

    rmd_wid = new ReminderWidget();

    edit_task = new CreateTask();
    edit_task->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    // signals and slots
    connect(m_startTimer,&QTimer::timeout,this,[=]{
        updateStartTimer();
    });

    connect(m_startReminderTimer,&QTimer::timeout,this,[=]{
        updateReminderTimer();
    });

    connect(d_startTaskButton,&QPushButton::clicked,this,[=]{
        // networkManager->checkTaskAndStart(token,task_id);
        if(!is_started){
            is_started = true;
            qDebug() << "setting is_started" <<  is_started;
            m_startTimer->start();
            start_label->setText("Pause");
            startbtn_layout->setContentsMargins(5,0,8,0);
            QPixmap pause_icon("://imgs/pause.png");
            start_icon->setPixmap(pause_icon);
            d_setReminderbtn->setVisible(true);
            qDebug() << "startbtn_layout if " << startbtn_layout->contentsMargins();
        }
        else{
            is_started = false;
            qDebug() << "setting is_started" <<  is_started;
            m_startTimer->stop();
            m_startReminderTimer->stop();
            remindercountdownTime = QTime(0,0,0);
            start_label->setText("Start");
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
            d_taskActiveTimeInReminder->setText("00:00:00");
            rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
            startbtn_layout->setContentsMargins(9,0,13,0);
            qDebug() << "startbtn_layout else" << startbtn_layout->contentsMargins();
            emit sendUpdateReminder();
        }
    });

    connect(d_editTaskButton,&QPushButton::clicked,this,[=]{
        edit_task->nameLineEdit->setText(d_taskNameLabel->text());
        edit_task->show();
        edit_task->createBtn->setText("Update");
        edit_task->setWindowTitle("Edit Task");
    });

    connect(d_setReminderbtn,&QPushButton::clicked,this,[=]{
        qDebug() << "d_setReminderbtn button clicked " << d_setReminderbtn;
        rmd_wid->show();
    });

    connect(rmd_wid,&ReminderWidget::displayReminderTime,this,[=](QTime getremindertime){
        qDebug() << "in  displaying the reminder layout time slot";
        remindercountdownTime =getremindertime;
        reminder_widget->setVisible(true);
        d_setReminderbtn->setVisible(false);
        d_taskActiveTimeInReminder->setText(remindercountdownTime.toString("hh:mm:ss"));
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
        d_taskActiveTimeInReminder->setText("00:00:00");
        rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
        reminder_widget->setVisible(false);
        d_setReminderbtn->setVisible(true);
    });

    connect(completeBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "complete btn clicked ";
        d_startTaskButton->setVisible(false);
        d_editTaskButton->setVisible(false);
        m_startTimer->stop();
        d_projectStatuslabel->setText("Finish Task");
    });

    connect(deleteBtn,&QPushButton::clicked,this,[=]{
        qDebug() << "delete btn clicked ";
    });
}

ProjectCustomWidget::ProjectCustomWidget(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    d_taskActiveTimeLabel->setText(taskActiveTime);
}

void ProjectCustomWidget::receiveData(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    qDebug()<<"received data  "<<taskName;
//    if(projectStatus == "current task"){
//        d_projectStatuslabel->s
//    }
    QLabel *textLabel = new QLabel("");
    QLabel *iconLabel = new QLabel;
    QHBoxLayout *statusLayout = new QHBoxLayout;

    if(projectStatus.contains("Current")){
        QIcon icon("://imgs/blue_icon.png");
        iconLabel->setPixmap(icon.pixmap(15, 15));
        textLabel->setText("Current Task");
    }
    else if(projectStatus.contains("Future")){
        QIcon icon(":/imgs/red_circle.png");
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
    rmd_wid->d_taskActiveTimeInReminder->setText(countdownTime.toString("hh:mm:ss"));
    // }
}

void ProjectCustomWidget::updateReminderTimer()
{
    remindercountdownTime = remindercountdownTime.addSecs(-1); // Decrement by one second
    d_taskActiveTimeInReminder->setText(remindercountdownTime.toString("hh:mm:ss"));
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
        d_setReminderbtn->setVisible(true);
    }
}

void ProjectCustomWidget::getTimer(QTime get_reminder_time)
{

}
