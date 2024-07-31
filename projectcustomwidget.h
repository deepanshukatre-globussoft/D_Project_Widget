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

#include "reminderwidget.h"

class ProjectCustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectCustomWidget(QWidget *parent = nullptr);

    QHBoxLayout * p_FirstLayout;
    QHBoxLayout * p_SecondLayout;
    QHBoxLayout * p_ThirdLayout;
    QHBoxLayout * p_ForthLayout;

    QVBoxLayout * d_containerLayout;
    QWidget * d_containerWidget;

    QVBoxLayout * m_HMainLayout;

    // set reminder widget
    QWidget * d_reminderWidget;
    QVBoxLayout * m_reminderLayout;
    QLabel * d_taskActiveTimeInReminder;
    QLabel * d_taskReminderTimeLabel;
private:
    QLabel *d_projectStatuslabel;
    QPushButton *d_startTaskButton;
    QPushButton *d_editTaskButton;

    QLabel *d_projectNameLabel;

    QLabel *d_taskNameLabel;

    QPushButton *d_setReminderbtn;
    QLabel *d_taskActiveTimeLabel;

    bool is_started = false;
    QTimer * m_startTimer;
    QTime countdownTime;

    static bool isAnyTaskStarted;

    ReminderWidget * rmd_wid;


signals:
    void sendData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);

public slots:
    void receiveData(const QString& projectStatus, const QString& projectName, const QString& taskName, const QString& taskActiveTime);
    void updateStartTimer();



};

#endif // PROJECTCUSTOMWIDGET_H
