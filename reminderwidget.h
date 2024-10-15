#ifndef REMINDERWIDGET_H
#define REMINDERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QFrame>
#include <QSignalMapper>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QProcess>
#include <QPainter>

#include <mynetworkmanager.h>

class ReminderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReminderWidget(QWidget *parent = nullptr);

    QVBoxLayout * m_reminderLayout;
    QLabel * d_taskActiveTimeInReminder;
    QLabel * d_taskReminderTimeLabel;
    QPushButton * set_reminder_button;

    QLabel * work_label;
    QLabel * task_title_label;
    QWidget * update_widget;
    QPushButton * custom_time_button;
    QWidget * custom_widget;

    QTime remindercountdownTime;
    QPushButton *buttons[6];
    int lastClickedIndex = 10;
    QStringList buttonsList;
    int input_time = 0;
    bool ok = true;

public slots:
    void addbuttonbackground(int index);
    void SetUpdateReminder();
    void toAddRemainingTimeOfTask(QString token, QString task_id);
    void getTokenAndTaskIdForReminderTimeSec(QString tokenValue,QString taskId);

private:
    QSystemTrayIcon *trayIcon;
    QMessageBox notify;

    MyNetworkManager *rmdNetworkMgr;
    static int reminderTimeSecs;

    QString tokenStr;
    QString taskIdStr;


signals:
    void displayReminderTime(QTime reminder_time);
    void resetReminderSignal();
    void updateReminderSignal();
};

#endif // REMINDERWIDGET_H
