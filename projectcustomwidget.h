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
#include <QTimer>
#include <QTime>
#include <QFrame>
#include <QSignalMapper>
#include <QSystemTrayIcon>
#include <QGraphicsDropShadowEffect>

#include "reminderwidget.h"
#include "mynetworkmanager.h"
#include "createtask.h"
// #include "widget.h"

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
    QLabel * d_taskActiveTimeInReminder;
    // QLabel * d_taskReminderTimeLabel;

    QLabel *d_taskNameLabel;
    CreateTask * edit_task;
private:
    QLabel *d_projectStatuslabel;
    QPushButton *d_startTaskButton;
    QPushButton *d_pauseTaskButton;
    QPushButton *d_editTaskButton;

    QLabel *d_projectNameLabel;

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


    QString token = "bf53e5323d1376b449659f98cde5cffd:bc360e76839ffc4e5b26fc4ce69f3d47668c34affed8cae5d1f6b06c33e63ad910de52edc97583bcec522635acb999a379fbcafa272163a1989fb2f3593bcb77d320fe87c2591bacbbbe567a0de3e90f21b31d7d6d26c40dfff4c157551536cf4ac5954678224b4448c22f33905d9acebde915a21e35e84fbf372e409da26eec5c76470f1a36b0e4d7725ac7b7e85efc1fc4f8a890f7969481352cbed1c65c22bcd30ee6920bd9ed5a5edf7fe89ed176a724a1260731a0831889edc635fb36bf55eb4b7329f08df91754ec7216a2fb2dd080a0948437c723c0fa3834c64409436bd8e67cfbef80969b6e2d5c63941d925262d92d7f0e5f45d3d18378632f34953c1784752426f6f90913be5264f74aac57c78bf17f9fa10575395a0d79e06b46";
    MyNetworkManager * networkManager;

    QString task_id;

    int m_taskStatus;
    QString remainingTime;
    QString activeTime;
    QString FinishedTime;

    QPoint startPos;            // Position of the mouse when pressed
    const int swipeThreshold = 400;  // Minimum swipe distance to trigger the action
    bool isSwipeDetected = false;
    QTimer *taskSpecificTimer;
    QTime ActiveTaskQTime;
    int myIntActiveTime;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override ;
    void mouseReleaseEvent(QMouseEvent *event) override ;

signals:
    void sendData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void sendUpdateReminder();

public:
    QString secondsToTimeFormat(int totalSeconds);
    int timeFormatToSeconds(const QString &time);

public slots:
    void setTaskProjectsIdNameinProjectCustomWidget(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskid);

    void setTaskAllDataInProjectCustomWidget(const QString &taskid, int taskStatus, const QString &taskName,
                                             const QString &m_taskActiveTime, const QString &m_taskRemainingTime,
                                             const QString &taskFolderName, const QString &taskProjectId, const QString &m_taskFinishedTime,
                                             const QString &projectName);

    void receiveData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void updateStartTimer();

    void taskStartDataSlot(const QString& taskid,bool success,const QString& time);
    void updateReminderTimer();
    void getTimer(QTime get_reminder_time);
    void updatetaskSpecificTimer(int intTime);


};

#endif // PROJECTCUSTOMWIDGET_H
