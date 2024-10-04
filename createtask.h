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

    QString token = "6b52374aa22159ebd0c6da2292b4be41:6e8e67545005fb408234c632323e925a986ecbaed7e6a867d2466319c5b179144e51590c7a64c7086d5ec1dca39f8d9b21c7cc8d288da1648c3d40fbeae553c2ea737500e819b83fc94de770766e03111fd8aca541b262ca0a816faec8e069d2ee0a76737f0429942f0bd56142f0cbb1102dca0c400637db6edff0ff6ac7bf4ce52ca1d4f0c740f869ed1755ee7553c15c5317f9ca4702e01d0952a0dcd106c318f53096afa7b6fb6b62c7dd959e8f5c6951319d40f8c6a403aa8a879a3df1b2211d68261491e1f1719897190011c57a7d16346f76e71e7e9391637afb6cabad57a092f42e366193c97034e3d25f2cac7579e0f837ca884bc979cec64d821144025471ee5515b39d87160c4c0604650746c97486434f1228ee9555657b90575e";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
