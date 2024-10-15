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

    QMessageBox notify;
    bool isStarted = false;

    QString tokenStr = "6fa89948c9bcb27c6adbbf5b4635b53a:61a2e8a4e06f0c833c0f99d1e1699a6b8c02e6216c7819e8d920b624df4d1535e897e03bbac27712419109bba1eb36c35d77a71edc11b371f64505878873b46034bbdf80fe45b621e638b373159aa4e1dfc16e2655d14aea60a1fbe688e59fcc84fe63d03dfa9e6dbd44d414dd917dc9dbe4075ec40ad7cd713598a8f3bbf05f39a9a123a28a3f98f31e5ebe71a550c739605d3b3a5d0a2fbd33c3fd5cd17d162c124668d5b86d7d96013938add9a0dc0f2055e36e018a1a257c040441e71f16016f941ac4f82a31c5ddee1de81aab69f5da8e6c54fe3859ea65e948c193cf9bb8299520b8f686b65219fc4e34a6180457c5a75949dc3aada27a4caa0e48cd3431c84f3042592156f90e3a0da8dbb360ba658b4fd2c0166518616c45ae3291d9";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();

signals:
    void sendToCreateTask(QString taskName, QString projectName, QString folderName, bool isStarted);
    void sendToUpdateTask(QString taskName, QString projectId, QString folderId, QString folderName, bool isStarted);

};

#endif // CREATETASK_H
