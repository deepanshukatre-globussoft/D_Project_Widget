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

    QLabel *d_taskNameLabel;
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

    ReminderWidget * rmd_wid;



    QString token = "0800068e6089f9913a7b17213635e548:687a325872a50fae44b3a54d5bd91764eba5a4dafa9b75499749376bcc6b462fdfb62b98ad0590ec467c0706739db03fe69e4fa8bcceb0950eed3cd120c3cf37839c0d7eaa7b252f5ca29760f25220d91c051ac17de4ca387d3b82a035fd5d394693eb2e25553a6ec30394ac473fdd6c313019fa9cef84c4907e3388f71b724c3bd93f7bdec9bb0515e14c0b4be85db96be9b85dc07958faf15897c20908619c5e5e99fcb458740290765c20fb451ad0297294e1b364207cd36f22de53a98eee092af7eab3bfd12282d98c959e2f3f5194eb4176cb7f011b1c879fb6d1c914dfa7adf33da36868498b89cec79455feb6e45763cbea82cbe15f4770d6271554170bd4281c4e7b48aedfbceea4fd3e41249a21a3201c034022395b83e7e9f5eb65";
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

    bool drawBorder = false; // Flag to track if the border should be drawn
    void initializeUIOfProjectsAndTasks();

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
