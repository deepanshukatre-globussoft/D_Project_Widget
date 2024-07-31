#include "reminderwidget.h"

ReminderWidget::ReminderWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(400,350);

    m_reminderLayout = new QVBoxLayout();
    m_reminderLayout->setContentsMargins(30,30,30,30);

    QHBoxLayout * m_hor_worktitleLayout = new QHBoxLayout();
    QHBoxLayout * m_hor_remindTimeLayout = new QHBoxLayout();
    QHBoxLayout * m_hor_minbtnLayout = new QHBoxLayout();
    QHBoxLayout * m_hor_hrbtnLayout = new QHBoxLayout();
    // QHBoxLayout * m_hor_reminderLayout5 = new QHBoxLayout();

    QVBoxLayout * work_tasktitle_hor_layout = new QVBoxLayout();

    // QLabel * set_reminder_label = new QLabel("Set Reminder");

    // m_hor_reminderLayout1->addWidget(set_reminder_label);
    // m_hor_reminderLayout1->setAlignment(Qt::AlignTop);
    // m_hor_reminderLayout1->setAlignment(Qt::AlignHCenter);

    QLabel * work_label = new QLabel("Work");
    QLabel * task_title_label = new QLabel("Task Title");

    d_taskActiveTimeInReminder = new QLabel("00:00:00");

    QFrame* h_line = new QFrame(this);
    h_line->setFrameShape(QFrame::HLine);
    h_line->setFrameShadow(QFrame::Sunken);
    h_line->setLineWidth(2);
    h_line->setMidLineWidth(1);
    h_line->setGeometry(0, 0, width(), 2);

    QLabel * d_taskRemindLabel = new QLabel("Remind me that I'm timing in:");
    d_taskReminderTimeLabel = new QLabel("00:00:00");


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
            m_hor_minbtnLayout->addWidget(buttons[i]);
        }
        else{
            m_hor_hrbtnLayout->addWidget(buttons[i]);
        }
        connect(buttons[i], &QPushButton::clicked, signalMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));

        signalMapper->setMapping(buttons[i], i);
    }

    // Connect signalMapper's mappedInt signal to handleButtonClicked slot
    connect(signalMapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mappedInt), this, &ReminderWidget::addbuttonbackground);

    QPushButton * custom_time_button = new QPushButton("Custom Time");

    QVBoxLayout * custom_time_layout = new QVBoxLayout();
    custom_time_layout->setContentsMargins(0,0,0,0);
    QLabel * custom_time_label = new QLabel("Enter custom time");

    QHBoxLayout * time_imput_layout = new QHBoxLayout();

    QLineEdit * input_time_lineedit = new QLineEdit();
    QIntValidator *validator = new QIntValidator(this);

    // Set the range for the integer input if needed
    validator->setRange(1, 1000); // Example range: 0 to 1000

    input_time_lineedit->setValidator(validator);
    QComboBox * time_combo_box = new QComboBox();

    time_combo_box->addItem("min");
    time_combo_box->addItem("hr");

    QHBoxLayout * done_btn_layout = new QHBoxLayout();
    QPushButton * done_button = new QPushButton("Done");
    done_btn_layout->addWidget(done_button,Qt::AlignRight);

    QPushButton * set_reminder_button = new QPushButton("Set Reminder");

    work_tasktitle_hor_layout->addWidget(work_label);
    work_tasktitle_hor_layout->addWidget(task_title_label);

    m_hor_worktitleLayout->addLayout(work_tasktitle_hor_layout);
    m_hor_worktitleLayout->addStretch();
    m_hor_worktitleLayout->addWidget(d_taskActiveTimeInReminder);

    m_hor_remindTimeLayout->addWidget(d_taskRemindLabel);
    m_hor_remindTimeLayout->addStretch();
    m_hor_remindTimeLayout->addWidget(d_taskReminderTimeLabel);

    time_imput_layout->addWidget(input_time_lineedit);
    time_imput_layout->addWidget(time_combo_box);

    custom_time_layout->addWidget(custom_time_label);
    custom_time_layout->addLayout(time_imput_layout);
    custom_time_layout->addLayout(done_btn_layout);

    // m_reminderLayout->addWidget(set_reminder_label);
    // m_reminderLayout->addStretch();
    m_reminderLayout->addLayout(m_hor_worktitleLayout);
    m_reminderLayout->addWidget(h_line);
    m_reminderLayout->addLayout(m_hor_remindTimeLayout);
    m_reminderLayout->addWidget(h_line2);
    m_reminderLayout->addWidget(selectTimerLabel);
    m_reminderLayout->addLayout(m_hor_minbtnLayout);
    m_reminderLayout->addLayout(m_hor_hrbtnLayout);
    m_reminderLayout->addWidget(custom_time_button);
    m_reminderLayout->addStretch();
    m_reminderLayout->addWidget(set_reminder_button);

    this->setLayout(m_reminderLayout);

    // this->show();

    m_startReminderTimer = new QTimer();
    m_startReminderTimer->setInterval(1000);
    m_startReminderTimer->setTimerType(Qt::CoarseTimer);

    // signals and slots
    connect(m_startReminderTimer,&QTimer::timeout,this,[=]{
        updateReminderTimer();
    });

    connect(custom_time_button,&QPushButton::clicked,this,[=]{
        qDebug() << "custom button clicked ";
        m_reminderLayout->insertLayout(8,custom_time_layout);
    });

    connect(input_time_lineedit,&QLineEdit::editingFinished,this,[=]{
        input_time = input_time_lineedit->text().toInt(&ok);
        qDebug() << "lineedit editing finished " << input_time;
    });

    connect(done_button,&QPushButton::clicked,this,[=]{
        qDebug() << "done_button clicked ";
        if(input_time != 0){
            // m_reminderLayout->removeItem(custom_time_layout);
            custom_time_button->setText(QString::number(input_time) +time_combo_box->currentText());

            if(time_combo_box->currentText() == "min"){
                remindercountdownTime = QTime(0,input_time,0);
            }
            else{
                remindercountdownTime = QTime(input_time,0,0);
            }
            qDebug() << "input time " << remindercountdownTime.toString("hh:mm:ss");
        }

    });

    connect(set_reminder_button,&QPushButton::clicked,this,[=]{
        qDebug() << "set_reminder_button clicked ";
        // d_reminderWidget->hide();
        d_taskReminderTimeLabel->setText(remindercountdownTime.toString("hh:mm:ss"));
        m_startReminderTimer->start();
    });
}

void ReminderWidget::addbuttonbackground(int index)
{
    qDebug() << "Button" << index << "clicked";
    if (lastClickedIndex != index && lastClickedIndex <=5) {
        buttons[lastClickedIndex]->setStyleSheet(""); // Reset the previous button's style
    }

    buttons[index]->setStyleSheet("background-color: blue; color: white;"); // Set the new button's style
    lastClickedIndex = index;

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
}

void ReminderWidget::updateReminderTimer()
{
    remindercountdownTime = remindercountdownTime.addSecs(-1); // Decrement by one second
    d_taskReminderTimeLabel->setText(remindercountdownTime.toString("hh:mm:ss"));
}
