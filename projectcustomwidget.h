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

    QString token = "f8a0b2386437b16f779142b19cdd9f56:c98860891d4885096e1ce9c1bde477d9f6601c606d4acf15544caa2807a3e1f46ebf72b114ab415562e066d2d70747fc33ba10fa529132678969b4c130847e8b21f700207516f9588958f1546e4ca4870db959b69a81bfa2da9be19370c0d68f4a9e0790afaa6d2440429e8395b428c67f48434ef787166736523e315f4652ec1d896aa973963bb0d88b2f09251fece60f4899f561aac579d3babd4c778724af9c62499a8974700afdd7e3a28c7a9a59d3cd2e623ccd29a5d714bc3fce98c35de36825c0b491c80b085e98d192c50d129e98e84ca555bdb7fbad744e5190c7f2103a0fffd4eebe41ce7721d5165a82e25b8a82010c40fad33e7ae2f70c2576c78cfbb9963e655a222ef23e232cd611ce4e2af72b320ab15103251fbbb949aedf";
     MyNetworkManager * networkManager;

    QString task_id;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

signals:
    void sendData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void sendUpdateReminder();
public slots:
    void setTaskProjectsIdNameinProjectCustomWidget(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskid);
    void receiveData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void updateStartTimer();

    void updateReminderTimer();
    void getTimer(QTime get_reminder_time);


};

#endif // PROJECTCUSTOMWIDGET_H
