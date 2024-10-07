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

    ~CreateTask();
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

    QString token = "bf53e5323d1376b449659f98cde5cffd:bc360e76839ffc4e5b26fc4ce69f3d47668c34affed8cae5d1f6b06c33e63ad910de52edc97583bcec522635acb999a379fbcafa272163a1989fb2f3593bcb77d320fe87c2591bacbbbe567a0de3e90f21b31d7d6d26c40dfff4c157551536cf4ac5954678224b4448c22f33905d9acebde915a21e35e84fbf372e409da26eec5c76470f1a36b0e4d7725ac7b7e85efc1fc4f8a890f7969481352cbed1c65c22bcd30ee6920bd9ed5a5edf7fe89ed176a724a1260731a0831889edc635fb36bf55eb4b7329f08df91754ec7216a2fb2dd080a0948437c723c0fa3834c64409436bd8e67cfbef80969b6e2d5c63941d925262d92d7f0e5f45d3d18378632f34953c1784752426f6f90913be5264f74aac57c78bf17f9fa10575395a0d79e06b46";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
