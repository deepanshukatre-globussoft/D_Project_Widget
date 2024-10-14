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



    QString token = "30765ca695d7dbb06b2e77101711097c:f1ab3a8a390bcacd69ad89df5d3130a77e5de779babc6102c9f616eac600cc460237644a69bde909f69ffa23de44c363d68c8d2ef3d7dbd4d7e3c2b639b687e70ae644f8007a40066669b1fd1f615aa786d3abbcafae05bdb0b536194216d0675d4499929b2f1a56578c23dc017e21408011cf3de8d672e2b5055aa4dfd87437146b3246cf2a2aedf4e7ff0db663ed33bfefcdb6878fd95cf225c70154cb07aab869cc51f585654b1004197f222723259cf660f765b2dc9fe0ba96b5486672f77af419d6bc87b3abba776827143c4e59b9e1a1aefdae758fe0cce534c67fdee39774a071aec4047e7619d449d71e86598335e4c3288b5b43701a6457491751523cc32eacac9d851b05d16a6eade16d3c34552b08b5a9d6531739aa66d47dce94";
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
