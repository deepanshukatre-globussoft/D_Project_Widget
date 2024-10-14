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


    QString token = "30765ca695d7dbb06b2e77101711097c:f1ab3a8a390bcacd69ad89df5d3130a77e5de779babc6102c9f616eac600cc460237644a69bde909f69ffa23de44c363d68c8d2ef3d7dbd4d7e3c2b639b687e70ae644f8007a40066669b1fd1f615aa786d3abbcafae05bdb0b536194216d0675d4499929b2f1a56578c23dc017e21408011cf3de8d672e2b5055aa4dfd87437146b3246cf2a2aedf4e7ff0db663ed33bfefcdb6878fd95cf225c70154cb07aab869cc51f585654b1004197f222723259cf660f765b2dc9fe0ba96b5486672f77af419d6bc87b3abba776827143c4e59b9e1a1aefdae758fe0cce534c67fdee39774a071aec4047e7619d449d71e86598335e4c3288b5b43701a6457491751523cc32eacac9d851b05d16a6eade16d3c34552b08b5a9d6531739aa66d47dce94";
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
