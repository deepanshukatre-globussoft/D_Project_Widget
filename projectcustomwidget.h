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
    QString token = "cba094201826bfcac1cfabfd4712a27f:e036145a11c6cabf024e998d9f9953420c4f14c4f139e1de6c1475f38aca1901a44abf9379a2a31853e45747f6b71e9b68ffe6de5efca8e5be88a9500987a7d5e13d7f101110148068e655102b32dfc97821d220c991dc6779cfe10fe243da20da5dc92cae219b0c57039bb1efc2862e2394eb798ac9ea5c038b7795f87826f4af534d53bde1b515660a07b57b6c8785a975b605fc80fdf723959a9627ab6bdb498a94f2d10bbe6bc827d054f46b99dc31bda1fa8f0b6d9503aca9157494b97bad81b1eb9725f4f7eb9681865318a4ef5a9d0f47942e58da47cb2a0c62b35ca957e5f5257ff86e7d19d3acb6fdd2262deeeaf995e644dc6f439f313e33733f9f756b08e49cecbebbad93ce3728d952b1ffeda24a4009fe87dbf540499a35da87";

    // MyNetworkManager * networkManager;

    QString task_id;

protected:
    void focusInEvent(QFocusEvent *event) override;

    void focusOutEvent(QFocusEvent *event) override;

signals:
    void sendData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void sendUpdateReminder();
public slots:
    void receiveData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void updateStartTimer();

    void updateReminderTimer();
    void getTimer(QTime get_reminder_time);


};

#endif // PROJECTCUSTOMWIDGET_H
