#include "projectcustomwidget.h"
#include "qdebug.h"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(0,0,0,0);
    m_HMainLayout->setAlignment(Qt::AlignLeft);


    this->setObjectName("customProjectItemWidget") ;
    d_containerWidget = new QWidget(this);
    d_containerLayout = new QVBoxLayout(d_containerWidget);

    d_containerWidget->setObjectName("projectContainerObject");

    QSpacerItem *spacer = new QSpacerItem(5,3);

    d_projectStatuslabel = new QLabel("Project Status ", this);  // shyad public karke access dena hoga
    d_startTaskButton = new QPushButton("start", this);
    d_editTaskButton = new QPushButton("edit", this);
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
    //==================================================
    d_taskNameLabel = new QLabel("Task Title",this);
    //==================================================
    d_setReminderbtn = new QPushButton("Set reminder",this);
    d_setReminderbtn->setObjectName("reminderbtnObj");
    d_setReminderbtn->setVisible(false);
    d_taskActiveTimeLabel = new QLabel("00:00:00",this);
    d_taskActiveTimeLabel->setFixedHeight(23);

    p_FirstLayout = new QHBoxLayout;
    p_FirstLayout->setContentsMargins(0,0,0,0);
    p_FirstLayout->addWidget(d_projectStatuslabel);
    p_FirstLayout->addStretch();
    p_FirstLayout->addWidget(d_startTaskButton);
    p_FirstLayout->addWidget(d_editTaskButton);


    p_SecondLayout = new QHBoxLayout;
    p_SecondLayout->setContentsMargins(0,0,0,0);
    p_SecondLayout->addWidget(d_projectNameLabel,Qt::AlignLeft);

    p_ThirdLayout = new QHBoxLayout;
    p_ThirdLayout->setContentsMargins(0,0,0,0);
    p_ThirdLayout->addWidget(d_taskNameLabel,Qt::AlignLeft);

    p_ForthLayout = new QHBoxLayout;
    p_ForthLayout->setContentsMargins(0,0,0,0);
    // p_ForthLayout->setSizeConstraint(Qt::size)

    reminder_widget = new QWidget();
    QVBoxLayout * reminder_widget_layout = new QVBoxLayout();
    QPushButton * reminder_layout_button = new QPushButton();
    reminder_layout_button->setFixedSize(100,30);
    reminder_layout_button->setFlat(true);
    QVBoxLayout * reminder_layout = new QVBoxLayout();
    QLabel * reminder_label = new QLabel("Remaining Time");
    d_taskActiveTimeInReminder = new QLabel("00:00:00");

    reminder_widget_layout->setContentsMargins(0,0,0,0);
    reminder_layout->setContentsMargins(0,0,0,0);
    reminder_layout->addWidget(reminder_label);
    reminder_layout->addWidget(d_taskActiveTimeInReminder);

    reminder_layout_button->setLayout(reminder_layout);

    reminder_widget_layout->addWidget(reminder_layout_button);

    // reminder_layout_button->setLayout(reminder_layout);
    // reminder_layout_button->setFlat(true);
    // reminder_widget_layout->addWidget(reminder_layout_button);

    reminder_widget->setLayout(reminder_widget_layout);
    // qDebug() << "reminder size " << reminder_widget->size() << reminder_widget_layout->sizeHint();
    reminder_widget->setVisible(false);
    // reminder_widget->setFixedSize(QSize(640, 480));


    p_ForthLayout->addWidget(reminder_widget);
    p_ForthLayout->addWidget(d_setReminderbtn);
    p_ForthLayout->addStretch();
    p_ForthLayout->addWidget(d_taskActiveTimeLabel);


    d_containerLayout->addLayout(p_FirstLayout);
    // d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_SecondLayout);
    //    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ThirdLayout);
    //    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ForthLayout);

    d_containerWidget->setLayout(d_containerLayout);

    setFixedSize(600,125);
    m_HMainLayout->addWidget(d_containerWidget);

    //    m_HMainLayout->addSpacerItem(spacer);
    //    m_HMainLayout->addLayout(p_SecondLayout);


    setLayout(m_HMainLayout);

    rmd_wid = new ReminderWidget();

    // signals and slots
    connect(m_startTimer,&QTimer::timeout,this,[=]{
        updateStartTimer();
    });

    connect(m_startReminderTimer,&QTimer::timeout,this,[=]{
        updateReminderTimer();
    });

    connect(d_startTaskButton,&QPushButton::clicked,this,[=]{
        if(!is_started){
            is_started = true;
            qDebug() << "setting is_started" <<  is_started;
            m_startTimer->start();
            d_startTaskButton->setText("pause");
            d_setReminderbtn->setVisible(true);
        }
        else{
            is_started = false;
            qDebug() << "setting is_started" <<  is_started;
            m_startTimer->stop();
            m_startReminderTimer->stop();
            remindercountdownTime = QTime(0,0,0);
            d_startTaskButton->setText("start");
            d_setReminderbtn->setVisible(false);
            reminder_widget->setVisible(false);
            rmd_wid->update_widget->setVisible(false);
            rmd_wid->set_reminder_button->setVisible(true);
            d_taskActiveTimeInReminder->setText("00:00:00");
            rmd_wid->d_taskReminderTimeLabel->setText("00:00:00");
            emit sendUpdateReminder();
        }
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
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    // d_taskActiveTimeLabel->setText(taskActiveTime);
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
