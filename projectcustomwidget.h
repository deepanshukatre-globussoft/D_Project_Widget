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
    QLabel * d_taskRemainingTime;
    // QLabel * d_taskReminderTimeLabel;

    QString projectTaskStatus;
    QLabel *d_taskNameLabel;
    QLabel * taskFinishedTimeLabel;
    int m_taskStatus;
    CreateTask * edit_task = nullptr;
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

    ReminderWidget * rmd_wid = nullptr;

    QString token = "7d5ed83b64b04ffbeb8cab10c1db0bc8:962438eb10e9cfee075799c62bbb0e157bfb3ab145916e4ee46dde10c3dc514710d3ec60624c26d1d4936b53edeb4702ec6f05554bad3a2d9ed6f815622a200a52365abd3681b2cd911de27581c0f41549d77bce15477610770c6a9763b861460340031c09f0d9ef1be661ee48eb6efda0211f5bbe0d25105fc812e57d45ea2bacdb5ea5d2623dc608fa51153af3756835c1ac39f5cb309428593c18140a444d4beb632e94b5be9bdc10c7feca6915e7126a1fd94cdef0b1092e5c099902c8aa177543bf8aeb9aa258d4dcbb234344f96356a02354c4240b03ba735add580647f9898570cb7675f9507d75b4d7db8f5aeb0b4521d39eeb87ead8a0fe3bc863bdbcedb21f7648bf7c86d1826ccaa8cb45712ea15c03bdab78f750e05e3919eacf";
    MyNetworkManager * networkManager;

    QString task_id;

    QString remainingTime;
    QString activeTime;
    QString FinishedTime;

    QPoint startPos;            // Position of the mouse when pressed
    const int swipeThreshold = 400;  // Minimum swipe distance to trigger the action
    bool isSwipeDetected = false;
    QTimer *taskSpecificTimer;
    QTime ActiveTaskQTime;

    bool drawBorder = false; // Flag to track if the border should be drawn
    void initializeUIOfProjectsAndTasks();

    void onSetReminderFuntionality();

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override ;
    void mouseReleaseEvent(QMouseEvent *event) override ;
    void paintEvent(QPaintEvent *event) override;

signals:
    void sendData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void sendUpdateReminder();

public:
    QString secondsToTimeFormat(int totalSeconds);
    int timeFormatToSeconds(const QString &time);
    void toStartTask(int activeTime);
    void toStopTask();

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
