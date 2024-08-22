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
    CreateTask * create;
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
    QString token = "45f9e4414332e8a0190601642b08bc15:1809c86ee5ea347d536cf7c6c180717b8cc0d177fa5c4993cabe2098fb538d5afe52cf3131894b77ccaaf162b21a64a54fb80769e04b6df8471a6ee07fa5833e2aed5c6409880f50b72df5290f90ed050b84c76cce7f2b58ae83e6686da051ab6bbc49aae3900ca34d15937deb3c2395ca621380c952d9986e9d79443196ad2a08b6324c07e9e00e9fae487cacf8423f7f27ea1c7ef8227ccb9ed6209a5942f9ce4fc8628d5f34a9eebbb5c2b0582b6a4fbb7ced97d4a40a782954cc0be5ba1ca6c8389718daebb47ef20dd2b6552909e18e2bef695bb115618e12eeb9d0e8e26d843764d9485186498e2fe2720b97aa81c572a681b4e69d47aabbbb19647965d0a9cfa892e1273827e81f7e9966ddaeac5e076dc7daa1725211e6d808b1549d";

    // MyNetworkManager * networkManager;

    QString task_id;

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
