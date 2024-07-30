#include "projectcustomwidget.h"
#include "qdebug.h"

bool ProjectCustomWidget::isAnyTaskStarted = false;

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

    m_startReminderTimer = new QTimer();
    m_startReminderTimer->setInterval(1000);
    m_startReminderTimer->setTimerType(Qt::CoarseTimer);

    countdownTime = QTime(0,0,0);

    buttonsList << "5 min" << "15 min" << "30 min" << "1 hr" << "2 hr" << "3 hr";

    d_editTaskButton->setObjectName("myPushBtn");  // Set object name
    //==================================================
    d_projectNameLabel =  new QLabel("Project Name",this);
    //==================================================
    d_taskNameLabel = new QLabel("Task Title",this);
    //==================================================
    d_setReminderbtn = new QPushButton("Set reminder");
    d_setReminderbtn->setObjectName("reminderbtnObj");
    d_taskActiveTimeLabel = new QLabel("00:00:00",this);
    d_taskActiveTimeInReminder = new QLabel();

    p_FirstLayout = new QHBoxLayout;
    p_FirstLayout->addWidget(d_projectStatuslabel);
    p_FirstLayout->addStretch();
    p_FirstLayout->addWidget(d_startTaskButton);
    p_FirstLayout->addWidget(d_editTaskButton);


    p_SecondLayout = new QHBoxLayout;
    p_SecondLayout->addWidget(d_projectNameLabel,Qt::AlignLeft);

    p_ThirdLayout = new QHBoxLayout;
    p_ThirdLayout->addWidget(d_taskNameLabel,Qt::AlignLeft);

    p_ForthLayout = new QHBoxLayout;
    // p_ForthLayout->addWidget(d_setReminderbtn);
    p_ForthLayout->addStretch();
    p_ForthLayout->addWidget(d_taskActiveTimeLabel);


    d_containerLayout->addLayout(p_FirstLayout);
    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_SecondLayout);
//    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ThirdLayout);
//    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ForthLayout);

    d_containerWidget->setLayout(d_containerLayout);

    setFixedSize(600,100);
    m_HMainLayout->addWidget(d_containerWidget);

//    m_HMainLayout->addSpacerItem(spacer);
//    m_HMainLayout->addLayout(p_SecondLayout);


    setLayout(m_HMainLayout);

    // signals and slots
    connect(m_startTimer,&QTimer::timeout,this,[=]{
        updateStartTimer();
    });

    connect(m_startReminderTimer,&QTimer::timeout,this,[=]{
        updateReminderTimer();
    });

    connect(d_startTaskButton,&QPushButton::clicked,this,[=]{
        qDebug() << "d_startTaskButton button clicked " << d_startTaskButton;

        if(!is_started){
            qDebug() << "setting is_started true";
            is_started = true;
            m_startTimer->start();
            d_startTaskButton->setText("pause");
            p_ForthLayout->insertWidget(0,d_setReminderbtn);
        }
        else{
            is_started = false;
        qDebug() << "setting is_started false" <<  ProjectCustomWidget::isAnyTaskStarted;
        m_startTimer->stop();
        d_startTaskButton->setText("start");
        p_ForthLayout->removeWidget(d_setReminderbtn);
        }
    });

    connect(d_setReminderbtn,&QPushButton::clicked,this,[=]{
        qDebug() << "d_setReminderbtn button clicked " << d_setReminderbtn;
        setReminderFunctionality();
        // if(!is_started){
        //     qDebug() << "setting isrunning true";
        //     is_started = true;
        //     m_startTimer->start();
        //     d_startTaskButton->setText("pause");
        // }
        // else{
        //     is_started = false;
        //     qDebug() << "setting isrunning false";
        //     // timer
        //     m_startTimer->stop();
        //     d_startTaskButton->setText("start");
        // }

    });

}

void ProjectCustomWidget::setReminderFunctionality()
{
    d_reminderWidget = new QWidget();
    d_reminderWidget->setFixedSize(400,400);

    m_reminderLayout = new QVBoxLayout();
    m_reminderLayout->setContentsMargins(30,30,30,30);

    QHBoxLayout * m_hor_reminderLayout1 = new QHBoxLayout();
    QHBoxLayout * m_hor_reminderLayout2 = new QHBoxLayout();
    QHBoxLayout * m_hor_reminderLayout3 = new QHBoxLayout();
    QHBoxLayout * m_hor_reminderLayout4 = new QHBoxLayout();
    // QHBoxLayout * m_hor_reminderLayout5 = new QHBoxLayout();

    QVBoxLayout * work_tasktitle_hor_layout = new QVBoxLayout();

    // QLabel * set_reminder_label = new QLabel("Set Reminder");

    // m_hor_reminderLayout1->addWidget(set_reminder_label);
    // m_hor_reminderLayout1->setAlignment(Qt::AlignTop);
    // m_hor_reminderLayout1->setAlignment(Qt::AlignHCenter);

    QLabel * work_label = new QLabel("Work");
    QLabel * task_title_label = new QLabel("Task Title");

    d_taskActiveTimeInReminder = new QLabel();
    work_tasktitle_hor_layout->addWidget(work_label);
    work_tasktitle_hor_layout->addWidget(task_title_label);

    m_hor_reminderLayout1->addLayout(work_tasktitle_hor_layout);
    m_hor_reminderLayout1->addStretch();
    m_hor_reminderLayout1->addWidget(d_taskActiveTimeInReminder);

    QFrame* h_line = new QFrame(this);
    h_line->setFrameShape(QFrame::HLine);
    h_line->setFrameShadow(QFrame::Sunken);
    h_line->setLineWidth(2);
    h_line->setMidLineWidth(1);
    h_line->setGeometry(0, 0, width(), 2);

    QLabel * d_taskRemindLabel = new QLabel("Remind me that I'm timing in:");
    d_taskReminderTimeLabel = new QLabel("00:00:00");

    m_hor_reminderLayout2->addWidget(d_taskRemindLabel);
    m_hor_reminderLayout2->addStretch();
    m_hor_reminderLayout2->addWidget(d_taskReminderTimeLabel);

    QFrame* h_line2 =new QFrame(this);
    h_line2->setFrameShape(QFrame::HLine);
    h_line2->setFrameShadow(QFrame::Sunken);
    h_line2->setLineWidth(2);
    h_line2->setMidLineWidth(1);
    h_line2->setGeometry(0, 0, width(), 2);

    QLabel * selectTimerLabel = new QLabel("Select a new reminder interval:");

    buttonsList << "5 min" << "15 min" << "30 min" << "1 hr" << "2 hr" << "3 hr";

    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (int i = 0; i < 6; ++i) {
        buttons[i] = new QPushButton(buttonsList.at(i), this);
        if(i<=2){
            m_hor_reminderLayout3->addWidget(buttons[i]);
        }
        else{
            m_hor_reminderLayout4->addWidget(buttons[i]);
        }

        // Connect button clicked signal to signalMapper's map slot
        connect(buttons[i], &QPushButton::clicked, signalMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));

        // Set mapping for each button
        signalMapper->setMapping(buttons[i], i);
    }

    // Connect signalMapper's mappedInt signal to handleButtonClicked slot
    connect(signalMapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mappedInt), this, &ProjectCustomWidget::addbuttonbackground);


    QPushButton * custom_time_button = new QPushButton("Custom Time");

    QVBoxLayout * custom_time_layout = new QVBoxLayout();
    custom_time_layout->setContentsMargins(0,0,0,0);
    QLabel * custom_time_label = new QLabel("Enter custom time");

    QHBoxLayout * time_imput_layout = new QHBoxLayout();

    QLineEdit * input_time_lineedit = new QLineEdit();
    QComboBox * time_combo_box = new QComboBox();

    time_combo_box->addItem("min");
    time_combo_box->addItem("hr");

    QHBoxLayout * done_btn_layout = new QHBoxLayout();
    QPushButton * done_button = new QPushButton("Done");
    done_btn_layout->addWidget(done_button,Qt::AlignRight);

    time_imput_layout->addWidget(input_time_lineedit);
    time_imput_layout->addWidget(time_combo_box);

    custom_time_layout->addWidget(custom_time_label);
    custom_time_layout->addLayout(time_imput_layout);
    custom_time_layout->addLayout(done_btn_layout);

    QPushButton * set_reminder_button = new QPushButton("Set Reminder");

    // m_reminderLayout->addWidget(set_reminder_label);
    // m_reminderLayout->addStretch();
    m_reminderLayout->addLayout(m_hor_reminderLayout1);
    m_reminderLayout->addWidget(h_line);
    m_reminderLayout->addLayout(m_hor_reminderLayout2);
    m_reminderLayout->addWidget(h_line2);
    m_reminderLayout->addWidget(selectTimerLabel);
    m_reminderLayout->addLayout(m_hor_reminderLayout3);
    m_reminderLayout->addLayout(m_hor_reminderLayout4);
    m_reminderLayout->addWidget(custom_time_button);
    m_reminderLayout->addStretch();
    m_reminderLayout->addWidget(set_reminder_button);

    d_reminderWidget->setLayout(m_reminderLayout);

    d_reminderWidget->show();

    connect(custom_time_button,&QPushButton::clicked,this,[=]{
        qDebug() << "custom button clicked ";
        m_reminderLayout->insertLayout(8,custom_time_layout);
    });

    connect(done_button,&QPushButton::clicked,this,[=]{
        qDebug() << "done_button clicked ";
        // m_reminderLayout->removeItem(custom_time_layout);
    });

    connect(set_reminder_button,&QPushButton::clicked,this,[=]{
        qDebug() << "set_reminder_button clicked ";
        // d_reminderWidget->hide();

        QString timetext = buttons[lastClickedIndex]->text();
        if(timetext.contains(" min")){
            timetext.remove(" min");
        }
        else{
            timetext.remove(" hr");
        }

        qDebug() << "timetext " << timetext;

        bool ok = true;
        switch (timetext.toInt(&ok)) {
        case 5 :
            remindercountdownTime = QTime(0,5,0);
            break;
        case 15 :
            remindercountdownTime = QTime(0,15,0);
            break;
        case 30 :
            remindercountdownTime = QTime(0,30,0);
            break;
        case 1 :
            remindercountdownTime = QTime(1,0,0);
            break;
        case 2 :
            remindercountdownTime = QTime(2,0,0);
            break;
        case 3 :
            remindercountdownTime = QTime(3,0,0);
            break;
        default:
            qDebug() << "no reminder time button executed ";
            break;
        }

        qDebug() << remindercountdownTime.toString("hh:mm:ss");
        m_startReminderTimer->start();
        // updateReminderTimer();
    });


}

void ProjectCustomWidget::receiveData(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    qDebug()<<"received data ";
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    d_taskActiveTimeLabel->setText(taskActiveTime);
}

void ProjectCustomWidget::updateStartTimer()
{
    countdownTime = countdownTime.addSecs(1); // Decrement by one second
    d_taskActiveTimeLabel->setText(countdownTime.toString("hh:mm:ss"));
    // if(d_taskActiveTimeInReminder){
        d_taskActiveTimeInReminder->setText(countdownTime.toString("hh:mm:ss"));
    // }
}

void ProjectCustomWidget::addbuttonbackground(int index)
{
    qDebug() << "Button" << index << "clicked";
    if (lastClickedIndex != index && lastClickedIndex <=5) {
        buttons[lastClickedIndex]->setStyleSheet(""); // Reset the previous button's style
    }

    buttons[index]->setStyleSheet("background-color: blue; color: white;"); // Set the new button's style
    lastClickedIndex = index;



}

void ProjectCustomWidget::updateReminderTimer()
{
    remindercountdownTime = remindercountdownTime.addSecs(-1); // Decrement by one second
    d_taskReminderTimeLabel->setText(remindercountdownTime.toString("hh:mm:ss"));
}
