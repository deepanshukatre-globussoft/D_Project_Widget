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

    QTime remindercountdownTime;
    QPushButton *buttons[6];
    int lastClickedIndex = 10;
    QStringList buttonsList;
    int input_time = 0;
    bool ok = true;

public slots:
    void addbuttonbackground(int index);
    void SetUpdateReminder();

private:
    QSystemTrayIcon *trayIcon;

signals:
    void displayReminderTime(QTime reminder_time);
    void resetReminderSignal();
    void updateReminderSignal();
};

#endif // REMINDERWIDGET_H
