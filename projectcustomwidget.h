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

#include "reminderwidget.h"

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
private:
    QLabel *d_projectStatuslabel;
    QPushButton *d_startTaskButton;
    QPushButton *d_editTaskButton;

    QLabel *d_projectNameLabel;


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
