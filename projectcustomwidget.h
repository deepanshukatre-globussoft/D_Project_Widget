#ifndef PROJECTCUSTOMWIDGET_H
#define PROJECTCUSTOMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QByteArray>
#include <QScrollArea>
#include <QTextEdit>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QFrame>
#include <QSignalMapper>
#include <QSystemTrayIcon>
#include <QGraphicsDropShadowEffect>
#include <QFocusEvent>

#include "reminderwidget.h"
#include "mynetworkmanager.h"
#include "createtask.h"
// #include "widget.h"

struct FolderData {
    QString id;   // "_id"
    QString name; // "name"
};

struct ProjectData {
    QString id;    // "_id"
    QString title; // "title"
};

struct Task {
    QString taskId;               // "_id"
    int assignedUser;          // "assigned_user"
    int status;                // "status"
    QDateTime taskFinishedTime;  // "task_finished_time"
    QDateTime taskRemainingTime; // "task_remaining_time"
    QString name;              // "name"
    QDateTime createdAt;       // "createdAt"
    FolderData folderData;     // "folder_data"
    ProjectData projectData;   // "project_data"
    int activeTime;            // "active_time"
};


class ProjectCustomWidget : public QWidget
{
    Q_OBJECT
public:
    ProjectCustomWidget(QWidget *parent = nullptr);
    ProjectCustomWidget(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);

    QHBoxLayout * p_FirstLayout;
    QHBoxLayout * p_SecondLayout;
    QHBoxLayout * p_ThirdLayout;
    QHBoxLayout * p_ForthLayout;

    QVBoxLayout * d_containerLayout;
    QWidget * d_containerWidget;

    QVBoxLayout * m_HMainLayout;

    // // set reminder widget
    // QWidget * d_reminderWidget;
    // QVBoxLayout * m_reminderLayout;
    QLabel * d_taskReminderTimeInReminder;
    // QLabel * d_taskReminderTimeLabel;

    QLabel *d_taskNameLabel;
    QLabel *d_projectNameLabel;

    Task m_task;
    void setProjectTaskDetails(QJsonObject jsonObject);
private:
    QLabel *d_projectStatuslabel;
    QPushButton *d_startTaskButton;
    QPushButton *d_editTaskButton;

    QHBoxLayout * startbtn_layout;
    QLabel * start_label;
    QLabel * start_icon;
    QPixmap start_pic;

    QPushButton *completeBtn ;
    QPushButton *deleteBtn;
    QPushButton *d_setReminderbtn;
    QLabel *d_taskActiveTimeLabel;
    QWidget * reminder_widget;

    bool is_started = false;
    QTimer * m_startTimer;
    QTime countdownTime;
    QTimer * m_startReminderTimer;
    QTime remindercountdownTime;
    QSystemTrayIcon *trayIcon;

    ReminderWidget * rmd_wid;
    QString token = "6fa89948c9bcb27c6adbbf5b4635b53a:61a2e8a4e06f0c833c0f99d1e1699a6b8c02e6216c7819e8d920b624df4d1535e897e03bbac27712419109bba1eb36c35d77a71edc11b371f64505878873b46034bbdf80fe45b621e638b373159aa4e1dfc16e2655d14aea60a1fbe688e59fcc84fe63d03dfa9e6dbd44d414dd917dc9dbe4075ec40ad7cd713598a8f3bbf05f39a9a123a28a3f98f31e5ebe71a550c739605d3b3a5d0a2fbd33c3fd5cd17d162c124668d5b86d7d96013938add9a0dc0f2055e36e018a1a257c040441e71f16016f941ac4f82a31c5ddee1de81aab69f5da8e6c54fe3859ea65e948c193cf9bb8299520b8f686b65219fc4e34a6180457c5a75949dc3aada27a4caa0e48cd3431c84f3042592156f90e3a0da8dbb360ba658b4fd2c0166518616c45ae3291d9";

    MyNetworkManager * networkMgr;

    QString task_id;
    QString project_id;


signals:
    void sendData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void sendUpdateReminder();
public slots:
    void receiveData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskId, const QString& projectId);
    void updateStartTimer();
    void startOrPauseTaskAction();

    void updateReminderTimer();
    // void getTimer(QTime get_reminder_time);
    void toDeleteTask();
    // bool toStartTask();
    void toStopTask();
    void toFinishTask();
};

#endif // PROJECTCUSTOMWIDGET_H
