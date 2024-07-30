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
class CreateTask : public QWidget
{
    Q_OBJECT
public:
    explicit CreateTask(QWidget *parent = nullptr);

private:
    void setupUI();
    void populateComboBoxes();

    QVBoxLayout *createTaskMainLayout;

    QLabel *createTaskLabel;

    QWidget *nameWidget;
    QVBoxLayout *nameLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;

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
    QPushButton *createTaskButton;
    QPushButton *cancelButton;

    MyNetworkManager netMgrObj;
private slots:
    void onCancelClicked();
    void onCreateTaskClicked();

};

#endif // CREATETASK_H
