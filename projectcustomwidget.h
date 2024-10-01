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
    QString token = "4e7813545426ef67f6c633d898400185:69ec0fde80c83dbe2ddf02f7fc251ca293407e0753c1340ec8be73da80696381afbb68cb4da30663d6bb101766ba9eee1a933b451f1bbb49ca3ca789df42bc9ed9c8616cd6f6bececf45d715764bb6240811157a656302df2e8f153932309e6c580732f077717b42050110f6070c92c5833106ef0ca808abfc9bde9f98a2f04bfb741a77338d19532222f8bef51b8b7aea8908c0587f134c41f3be43c91c5db4f2a9b043a3b5c6596e1652b3ad145a2dfb9714e2aa8b0310ad5ffd559e6d2e16810f208963c715ec7337e6051d0e9c8dd474efac9579f6c74e71c89b67498e7fe5d1e501634137df6df9d57ec3dc882e2d4d3bde96353dd39241170ce80b6facc344b2a024da9a945a0e3530a44c8f66cd2ba8ab40dbf991ef6c65ea4b96a0db";

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
