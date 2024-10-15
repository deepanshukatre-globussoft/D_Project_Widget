#include "reminderwidget.h"

int ReminderWidget::reminderTimeSecs;

ReminderWidget::ReminderWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(408,350);
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
    // this->setStyleSheet("background-color : white;");
    this->setWindowTitle(tr("Set Reminder"));
    this->setObjectName("mainreminderwidget");

    m_reminderLayout = new QVBoxLayout();
    m_reminderLayout->setContentsMargins(30,30,30,30);
    // m_reminderLayout->setAlignment(Qt::AlignCenter);

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

    work_label = new QLabel(tr("Work"));
    work_label->setFont(QFont("Ubuntu",12,500));
    task_title_label = new QLabel(tr("Task Title"));

    d_taskActiveTimeInReminder = new QLabel("00:00:00");
    d_taskActiveTimeInReminder->setFixedSize(70,21);
    d_taskActiveTimeInReminder->setStyleSheet(
        "QLabel {"
        "border :1px solid #0F5EA9;"
        "border-radius: 6px;"
        "color : #0F5EA9;"
        "font-size: 15px;"
        // "padding-left:5px;"
        "}"
        );
    QFrame* h_line = new QFrame(this);
    h_line->setFrameShape(QFrame::HLine);
    h_line->setFrameShadow(QFrame::Sunken);
    h_line->setStyleSheet("color: #414040;");

    QLabel * d_taskRemindLabel = new QLabel(tr("Remind me that I'm timing in:"));
    d_taskReminderTimeLabel = new QLabel("00:00:00");
    d_taskReminderTimeLabel->setFixedSize(70,21);
    d_taskReminderTimeLabel->setObjectName("TaskReminderLabel");
//    d_taskReminderTimeLabel->setStyleSheet(
//        "QLabel {"
//        "border :1px solid #D2232A;"
//        "border-radius: 6px;"
//        "color : #D2232A;"
//        "font-size: 17px;"
//        "}"
//        );

    QFrame* h_line2 =new QFrame(this);
    h_line2->setFrameShape(QFrame::HLine);
    h_line2->setFrameShadow(QFrame::Sunken);
    h_line2->setStyleSheet("color: #414040;");

    QLabel * selectTimerLabel = new QLabel(tr("Select a new reminder interval:"));

    buttonsList << "5 " << "15 " << "30 " << "1 " << "2 " << "3 ";

    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (int i = 0; i < 6; ++i) {
        buttons[i] = new QPushButton(this);
        QString btnText = buttonsList.at(i);
        if(i<=2){
            btnText.append(tr("min"));
            buttons[i]->setText(btnText);
            m_hor_minbtnLayout->addWidget(buttons[i]);
        }
        else{
            btnText.append(tr("hr"));
            buttons[i]->setText(btnText);
            m_hor_hrbtnLayout->addWidget(buttons[i]);
        }
        // buttons[i]->setFlat(true);
        buttons[i]->setFixedSize(112,28);
        buttons[i]->setFont(QFont("Ubuntu",-1,400));
        buttons[i]->setStyleSheet(
            "QPushButton {"
            "background-color: rgba(35, 31, 32, 0.1);"
            "border-radius: 10px;"
            "}"
            );
        connect(buttons[i], &QPushButton::clicked, signalMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));

        signalMapper->setMapping(buttons[i], i);
    }

    // Connect signalMapper's mappedInt signal to handleButtonClicked slot
    connect(signalMapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mappedInt), this, &ReminderWidget::addbuttonbackground);

    custom_time_button = new QPushButton(tr("Custom Time"));
    custom_time_button->setFixedHeight(28);
    custom_time_button->setStyleSheet(
        "QPushButton {"
        "background-color:  rgba(35, 31, 32, 0.1);"
        "border-radius: 10px;"
        "}"
        );

    custom_widget = new QWidget(this);
    QVBoxLayout * custom_time_layout = new QVBoxLayout();
    custom_time_layout->setContentsMargins(0,0,0,0);
    QLabel * custom_time_label = new QLabel(tr("Enter custom time"));
//    custom_time_label->setAutoFillBackground(true);
    custom_widget->setStyleSheet(     //15, 94, 169
        " QWidget {"
        "background-color: #dfe9f0;"
        "}"
        );

    QHBoxLayout * time_imput_layout = new QHBoxLayout();

    QLineEdit * input_time_lineedit = new QLineEdit();
    input_time_lineedit->setFixedSize(180,28);
    input_time_lineedit->setAlignment(Qt::AlignCenter);
    QIntValidator *validator = new QIntValidator(1,480,this);
    input_time_lineedit->setValidator(validator);
    input_time_lineedit->setStyleSheet("QLineEdit { margin: 0px;  background-color : white; border: none; border-top-left-radius: 5px; border-bottom-left-radius: 5px;}");

    QComboBox * time_combo_box = new QComboBox();
    time_combo_box->addItem(tr("mins"));
    time_combo_box->addItem(tr("hrs"));

    time_combo_box->setFixedSize(144,28);

    // Set background color and text color using style sheet
    time_combo_box->setStyleSheet("QComboBox {"
                            "background-color: #0F5EA9;"
                            "color: white;"
                            "border-top-right-radius: 5px;"
                            "border-bottom-right-radius: 5px;"
                            "margin: 0px;"
                            "padding-left : 45px;"
                            "padding-bottom : 3px;"
                            "}"
                            "QComboBox::drop-down {"
                            "border: none;"
                            "width: 0px;"
                            "}"
                            "QComboBox::down-arrow {"
                            "image: url(://imgs/downarrow.png);"
                            "width: 16px;"
                            "height: 16px;"
                            "padding-right : 75px;"
                            // "image-position: right center;"
                            "}");

    QHBoxLayout * done_btn_layout = new QHBoxLayout();
    done_btn_layout->setAlignment(Qt::AlignRight);
    done_btn_layout->setContentsMargins(5,5,2,5);
    QPushButton * done_button = new QPushButton(tr("Done"));
    done_button->setFixedSize(30,15);
    done_button->setFlat(true);
    done_button->setStyleSheet("color: #0F5EA9; padding-right: 0px; border :0px;margin :0px; font-size: 13px;");
    done_btn_layout->addWidget(done_button);

    QFrame* h_line3 =new QFrame(this);
    h_line3->setFrameShape(QFrame::HLine);
    h_line3->setFrameShadow(QFrame::Sunken);
    h_line3->setStyleSheet("color: #414040;");

    QHBoxLayout * setReminderBtn_layout = new QHBoxLayout();
    setReminderBtn_layout->setAlignment(Qt::AlignHCenter);

    set_reminder_button = new QPushButton(tr("Set Reminder"));
    set_reminder_button->setFixedSize(176,42);
    set_reminder_button->setFont(QFont("Ubuntu",-1,400));
    set_reminder_button->setStyleSheet(
        "QPushButton {"
        "background-color: #D2232A;"
        "border-radius: 6px;"
        "color: white;"
        "}"
        );

    update_widget = new QWidget();
    QHBoxLayout * reset_update_btnLayout = new QHBoxLayout();
    QPushButton * reset_reminder_btn = new QPushButton(tr("Reset"));
    QPushButton * update_reminder_btn = new QPushButton(tr("Update"));

    reset_reminder_btn->setFixedSize(124,42);
    reset_reminder_btn->setFlat(true);
    reset_reminder_btn->setStyleSheet("color :#D2232A; border: 1px solid #D2232A; border-radius : 5px;");
    update_reminder_btn->setFixedSize(124,42);
    update_reminder_btn->setFlat(true);
    update_reminder_btn->setStyleSheet("color :white; border-radius : 5px; background-color: #D2232A;");

    work_tasktitle_hor_layout->addWidget(work_label);
    work_tasktitle_hor_layout->addWidget(task_title_label);

    m_hor_worktitleLayout->addLayout(work_tasktitle_hor_layout);
    m_hor_worktitleLayout->addStretch();
    m_hor_worktitleLayout->addWidget(d_taskActiveTimeInReminder);

    m_hor_remindTimeLayout->addWidget(d_taskRemindLabel);
    m_hor_remindTimeLayout->addStretch();
    m_hor_remindTimeLayout->addWidget(d_taskReminderTimeLabel);

    time_imput_layout->setContentsMargins(10,0,0,0);
    time_imput_layout->setSpacing(0);
    time_imput_layout->addWidget(input_time_lineedit);
    time_imput_layout->addWidget(time_combo_box);

    custom_time_layout->setContentsMargins(0,0,10,0);
    custom_time_layout->addStretch();
    custom_time_layout->addStretch();
    custom_time_layout->setSpacing(0);
    custom_time_layout->addWidget(custom_time_label);
    custom_time_layout->addLayout(time_imput_layout);
    custom_time_layout->addLayout(done_btn_layout);

    QColor color(15, 94, 169, 36);
    QPalette pal = custom_widget->palette();
    pal.setBrush(QPalette::Window, QBrush(color));
    custom_widget->setPalette(pal);
    // custom_widget->setAttribute(Qt::WA_TranslucentBackground);
    // custom_widget->setStyleSheet("background-color: red;");
    custom_widget->setFixedSize(348,110);
    custom_widget->move(30,220);
    custom_widget->setStyleSheet("margin:10px; ");
    custom_widget->setLayout(custom_time_layout);
    custom_widget->setVisible(false);
    custom_widget->setAutoFillBackground(true);
//     custom_widget->setStyleSheet(     //15, 94, 169
//         "QWidget > QWidget {"
//         "background-color: rgba(15, 94, 169, 0.1);"
//         "}"
//         );

    setReminderBtn_layout->addWidget(set_reminder_button);

    reset_update_btnLayout->setContentsMargins(0,0,0,0);
    reset_update_btnLayout->addWidget(reset_reminder_btn);
    // reset_update_btnLayout->addStretch();
    reset_update_btnLayout->addWidget(update_reminder_btn);

    update_widget->setLayout(reset_update_btnLayout);
    update_widget->setVisible(false);

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
    m_reminderLayout->addWidget(h_line3);
    m_reminderLayout->addLayout(setReminderBtn_layout);
    m_reminderLayout->addWidget(update_widget);

    // set_reminder_button->setVisible(false);
    // update_widget->setVisible(true);
    this->setLayout(m_reminderLayout);
    // this->show();
    remindercountdownTime = QTime(0,0,0);

    rmdNetworkMgr = MyNetworkManager::instance();

    // signals and slots
    connect(custom_time_button,&QPushButton::clicked,this,[=]{
        qDebug() << "custom button clicked ";
        if (lastClickedIndex <=5) {
            buttons[lastClickedIndex]->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(35, 31, 32, 0.1);"
                "border-radius: 10px;"
                "}"
                );
        }
        custom_time_button->setStyleSheet(
            "QPushButton {"
            "background-color: #0F5EA9;"
            "border-radius: 10px;"
            "color: white;"
            "}"
            );
        if(custom_widget->isHidden()){
            custom_widget->setVisible(true);
            this->setFixedSize(408,421);
            qDebug() << "this size after custom" << this->size();
        }
        else{
            custom_widget->setVisible(false);
            this->setFixedSize(408,350);
        }
    });

    connect(input_time_lineedit,&QLineEdit::editingFinished,this,[=]{
        input_time = input_time_lineedit->text().toInt(&ok);
        qDebug() << "lineedit editing finished " << input_time;
        // if(input_time > 480){
        //     qDebug() << "in put value is greater ";
        //     notify.setText("Please enter a valid min value");
        //     notify.exec();
        //     input_time_lineedit->clear();
        // }

        if(lastClickedIndex <=5){
            // buttons[lastClickedIndex]->setStyleSheet("");
            buttons[lastClickedIndex]->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(35, 31, 32, 0.1);"
                "border-radius: 10px;"
                "}"
                );
        }
    });

    connect(done_button,&QPushButton::clicked,this,[=]{
        qDebug() << "done_button clicked ";
        if(input_time != 0){
            this->setFixedSize(408,350);
            custom_time_button->setText(QString::number(input_time) +time_combo_box->currentText());
            // qDebug() << "in put time " << input_time <<
            if(time_combo_box->currentText() == "mins"){
                if(input_time < 60){
                    remindercountdownTime = QTime(0,input_time,0);
                }else if(input_time > 60){
                    remindercountdownTime = QTime(input_time/60,input_time%60,0);
                }else
                    remindercountdownTime = QTime(1,0,0);
            }
            else{
                if(input_time < 24)
                    remindercountdownTime = QTime(input_time,0,0);
            }
            qDebug() << "input time " << remindercountdownTime.toString("hh:mm:ss");
            reminderTimeSecs = -(remindercountdownTime.secsTo(QTime(0,0,0)));
            qDebug() << "reminder time in secs " << reminderTimeSecs;
            input_time_lineedit->clear();
            input_time = 0;
            custom_widget->setVisible(false);
        }else{
            notify.setText("Set a value for timer");
            notify.exec();
        }
    });

    connect(set_reminder_button,&QPushButton::clicked,this,[=]{
        qDebug() << "set_reminder_button clicked ";
        toAddRemainingTimeOfTask(tokenStr, taskIdStr);
        custom_time_button->setText(tr("Custom Time"));
        time_combo_box->setCurrentText(tr("mins"));
        d_taskReminderTimeLabel->setText(remindercountdownTime.toString("hh:mm:ss"));
        this->hide();
        set_reminder_button->setVisible(false);
        if(lastClickedIndex <=5){
            // buttons[lastClickedIndex]->setStyleSheet("");
            buttons[lastClickedIndex]->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(35, 31, 32, 0.1);"
                "border-radius: 10px;"
                "}"
                );
        }
        qDebug() << "after button clear";
        emit displayReminderTime(remindercountdownTime);
    });

    connect(reset_reminder_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "reset reminder btn clicked ";
        if(lastClickedIndex <=5){
            // buttons[lastClickedIndex]->setStyleSheet("");
            buttons[lastClickedIndex]->setStyleSheet(
                "QPushButton {"
                "background-color: rgba(35, 31, 32, 0.1);"
                "border-radius: 10px;"
                "}"
                );
        }
        this->hide();
        emit resetReminderSignal();
    });

    connect(update_reminder_btn,&QPushButton::clicked,this,[=]{
        qDebug() << "update_reminder_btn clicked ";
        custom_time_button->setText(tr("Custom Time"));
        time_combo_box->setCurrentText(tr("mins"));
        if(remindercountdownTime != QTime(0,0,0)){
            this->hide();
            emit displayReminderTime(remindercountdownTime);
        }else{
            qDebug() << "in else of QTime";
            if(lastClickedIndex <=5){
                // buttons[lastClickedIndex]->setStyleSheet("");
                buttons[lastClickedIndex]->setStyleSheet(
                    "QPushButton {"
                    "background-color: rgba(35, 31, 32, 0.1);"
                    "border-radius: 10px;"
                    "}"
                    );
            }
            QMessageBox notify;
            notify.setText("Set a vlaue for Timer");
            notify.exec();
        }
    });
    // this->setFixedSize(408,350);
    // qDebug() << "this size " << this->size();
}

void ReminderWidget::addbuttonbackground(int index)
{
    custom_time_button->setStyleSheet(
        "QPushButton {"
        "background-color:  rgba(35, 31, 32, 0.1);"
        "border-radius: 10px;"
        // "color: white;"
        "}"
        );

    if(custom_widget->isVisible()){
        custom_widget->setVisible(false);
        this->setFixedSize(408,350);
    }

    qDebug() << "Button" << index << "clicked";
    if (lastClickedIndex != index && lastClickedIndex <=5) {
        buttons[lastClickedIndex]->setStyleSheet(
            "QPushButton {"
            "background-color: rgba(35, 31, 32, 0.1);"
            "border-radius: 10px;"
            "}"
            );
    }

    // buttons[index]->setStyleSheet("background-color: #0F5EA9; color: white;");
    buttons[index]->setStyleSheet(
        "QPushButton {"
        "background-color: #0F5EA9;"
        "border-radius: 10px;"
        "color: white;"
        "}"
        );
    lastClickedIndex = index;

    bool ok = true;
    QString timetext = buttons[lastClickedIndex]->text();
    qDebug() << "timetext " << timetext;
    int button_time = 0;
    if(timetext.contains(" min")){
        timetext.remove(" min");
        button_time = timetext.toInt(&ok);
        remindercountdownTime = QTime(0,button_time,0);
    }
    else{
        timetext.remove(" hr");
        button_time = timetext.toInt(&ok);
        remindercountdownTime = QTime(button_time,0,0);
    }
    qDebug() << remindercountdownTime.toString("hh:mm:ss");
    reminderTimeSecs = -(remindercountdownTime.secsTo(QTime(0,0,0)));
    qDebug() << "reminder time in secs " << reminderTimeSecs;

}

void ReminderWidget::SetUpdateReminder()
{
    qDebug() << "in SetUpdateReminder slot of reminderwidget   ";
    remindercountdownTime = QTime(0,0,0);
    if(lastClickedIndex <=5){
        // buttons[lastClickedIndex]->setStyleSheet("");
        buttons[lastClickedIndex]->setStyleSheet(
            "QPushButton {"
            "background-color: rgba(35, 31, 32, 0.1);"
            "border-radius: 10px;"
            "}"
            );
    }
}

void ReminderWidget::toAddRemainingTimeOfTask(QString token, QString task_id)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/add-remaining-time");
    qDebug() << "Reminder time in seconds " << reminderTimeSecs;
    QJsonObject jsonObject;
    jsonObject["remaining_time"] = reminderTimeSecs;
    jsonObject["task_id"] = task_id;

    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = rmdNetworkMgr->networkManager->post(request, jsonData);
    connect(reply, &QNetworkReply::finished, this, [reply](){
        if(reply->error() == QNetworkReply::NoError && reply->isReadable()){
            QByteArray response = reply->readAll();
            qDebug() <<"AddRemainingTimeOfTask Task Response "<<response;
            // this->deleteLater();
            // QJsonDocument jsonDoc = QJsonDocument::fromJson(response);

            // QJsonObject jsonObj = jsonDoc.object();

            // QString message = jsonObj.value("message").toString();

            // // Check if the message contains "Project task created successfully"
            // if (message == "Project task created successfully") {
            //     // Display a message box
            //     QMessageBox::information(this, "Task Created", message);
            // } else {
            //     qDebug() << "Message does not contain the expected text!"; https://track.dev.empmonitor.com/api/v3/project/finish-project-task
            // }
        } else {
            qDebug() << "Network reply error " << reply->errorString();
        }
    });
}

void ReminderWidget::getTokenAndTaskIdForReminderTimeSec(QString tokenValue, QString taskId)
{
    tokenStr = tokenValue;
    taskIdStr = taskId;
}

