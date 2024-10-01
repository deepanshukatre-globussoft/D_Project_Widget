#ifndef CREATETASK_H
#define CREATETASK_H

#include "mynetworkmanager.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>

class CreateTask : public QWidget
{
    Q_OBJECT
public:
    explicit CreateTask(QWidget *parent = nullptr);

    MyNetworkManager *netMgrObj;
    QLineEdit *nameLineEdit;
    QPushButton *createBtn;
private:
    void setupUI();
    void populateComboBoxes();

    QVBoxLayout *createTaskMainLayout;


    QWidget *nameWidget;
    QVBoxLayout *nameLayout;
    QLabel *nameLabel;

    QWidget *projectWidget;
    QVBoxLayout *projectLayout;
    QLabel *projectLabel;
    QComboBox *projectComboBox;

    QWidget *taskWidget;
    QVBoxLayout *taskLayout;
    QLabel *taskLabel;
    QComboBox *taskComboBox;

    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *cancelBtn;

    QString hiddenFieldId;

    QString token = "4e7813545426ef67f6c633d898400185:69ec0fde80c83dbe2ddf02f7fc251ca293407e0753c1340ec8be73da80696381afbb68cb4da30663d6bb101766ba9eee1a933b451f1bbb49ca3ca789df42bc9ed9c8616cd6f6bececf45d715764bb6240811157a656302df2e8f153932309e6c580732f077717b42050110f6070c92c5833106ef0ca808abfc9bde9f98a2f04bfb741a77338d19532222f8bef51b8b7aea8908c0587f134c41f3be43c91c5db4f2a9b043a3b5c6596e1652b3ad145a2dfb9714e2aa8b0310ad5ffd559e6d2e16810f208963c715ec7337e6051d0e9c8dd474efac9579f6c74e71c89b67498e7fe5d1e501634137df6df9d57ec3dc882e2d4d3bde96353dd39241170ce80b6facc344b2a024da9a945a0e3530a44c8f66cd2ba8ab40dbf991ef6c65ea4b96a0db";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
