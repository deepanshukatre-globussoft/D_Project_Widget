#ifndef REMINDERWIDGET_H
#define REMINDERWIDGET_H

#include "mynetworkmanager.h"
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

class ReminderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReminderWidget(QWidget *parent = nullptr);

    QVBoxLayout * m_reminderLayout;
    QLabel * d_taskActiveTimeInReminder;
    QLabel * d_taskReminderTimeLabel;
    QPushButton * set_reminder_button;

    QWidget * update_widget;
    QPushButton * custom_time_button;
    QWidget * custom_widget;

    QTime remindercountdownTime;
    QPushButton *buttons[6];
    int lastClickedIndex = 10;
    QStringList buttonsList;
    int input_time = 0;
    bool ok = true;
    QString taskIdForReminder;

    MyNetworkManager *netMgrObj;

    void setTaskIdForReminder(const QString &newTaskIdForReminder);

    QString token = "bba0d6557e361414a6f82a0884dab45c:2be8310172b1513985e41a017c3123ed68a93e89391044afc609e53c65b148e3f6da64eb50086625f13a49733078cfc0bc255a85a73449dde480f989ae0b930bed37978b04e759827ec0e06fdd348afacfe1c5ca00ad68f4d615a4b7098a61d430cb0649ace78eb94e797ea3a8b31ce45595191f3aa725c97daccc3467455950cde682c68a7f48ef9db4cbb6d6d8dd8ce9508561dd818e1e2281101830936f2fe73838246f37e875e2a234e765404f00734881d57d14e0caec3346a6a8dd274824ffa6ec4f88c61656299f785c9d9feb9a6ea479e130c38aced99e43975863a895ff07489d5b86079b6dd3095aa02f7f265085643e74639e0de69c0a10b033e74a74cd2ea3714b4ca0ac1af99992442fdf8acc78f02d0b0246f83f24cbcd09e3";

public slots:
    void addbuttonbackground(int index);
    void SetUpdateReminder();

private:
    QSystemTrayIcon *trayIcon;
    QMessageBox notify;

signals:
    void displayReminderTime(QTime reminder_time);
    void resetReminderSignal();
    void updateReminderSignal();
};

#endif // REMINDERWIDGET_H
