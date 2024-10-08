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

    QString token = "b1f5cbe8d7ec66f41271fcb683cc62f5:eaef53a051d0856eca0015bc82667377e9464620ff02e4587959e98c35c7bf5fb6f8813349b17f5c20d61c14330d076f7ef3d149229e4ec0654a4b037d4e5c09baa41efe16dfb0c26379aefdb43f084cb2703a35874a1defb069d4e1d37ecd5266a1d5111e2ce071a18184ea6a98c08f56285a49b4d90615641af2aaf15aa343c4ac65fa06f7de24ff4bbea42b4285ed79369172e84acb63d9eacb3ebbaffe027d986e5901a3430aafd8803d335097bc752528090e86221db9d10f12594f13e8044ad68b0e036c75217fbd9ce5aab6a9231511d3910f6a57fb5e143a516e21a4ef9b22cc6ec2329d891b011ba5ecf260dad662888995648b422c39efe948ffb32b70400f64baa3b48bebc908202edf8d8af388d768266a3709a3cf83ad3e5599";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
