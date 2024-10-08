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


    QString token = "b1f5cbe8d7ec66f41271fcb683cc62f5:eaef53a051d0856eca0015bc82667377e9464620ff02e4587959e98c35c7bf5fb6f8813349b17f5c20d61c14330d076f7ef3d149229e4ec0654a4b037d4e5c09baa41efe16dfb0c26379aefdb43f084cb2703a35874a1defb069d4e1d37ecd5266a1d5111e2ce071a18184ea6a98c08f56285a49b4d90615641af2aaf15aa343c4ac65fa06f7de24ff4bbea42b4285ed79369172e84acb63d9eacb3ebbaffe027d986e5901a3430aafd8803d335097bc752528090e86221db9d10f12594f13e8044ad68b0e036c75217fbd9ce5aab6a9231511d3910f6a57fb5e143a516e21a4ef9b22cc6ec2329d891b011ba5ecf260dad662888995648b422c39efe948ffb32b70400f64baa3b48bebc908202edf8d8af388d768266a3709a3cf83ad3e5599";
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

    void initializeUIOfProjectsAndTasks();

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
    void updatetaskSpecificTimer(QTime myQTime);


};

#endif // PROJECTCUSTOMWIDGET_H
