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
    QComboBox *projectComboBox;
    QComboBox *folderComboBox;
    QPushButton *createBtn;
    QString TaskId = "111";
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

    QWidget *taskWidget;
    QVBoxLayout *taskLayout;
    QLabel *taskLabel;

    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *cancelBtn;

    QString hiddenFieldId;

    bool isStarted = false;
    QString token = "7d5ed83b64b04ffbeb8cab10c1db0bc8:962438eb10e9cfee075799c62bbb0e157bfb3ab145916e4ee46dde10c3dc514710d3ec60624c26d1d4936b53edeb4702ec6f05554bad3a2d9ed6f815622a200a52365abd3681b2cd911de27581c0f41549d77bce15477610770c6a9763b861460340031c09f0d9ef1be661ee48eb6efda0211f5bbe0d25105fc812e57d45ea2bacdb5ea5d2623dc608fa51153af3756835c1ac39f5cb309428593c18140a444d4beb632e94b5be9bdc10c7feca6915e7126a1fd94cdef0b1092e5c099902c8aa177543bf8aeb9aa258d4dcbb234344f96356a02354c4240b03ba735add580647f9898570cb7675f9507d75b4d7db8f5aeb0b4521d39eeb87ead8a0fe3bc863bdbcedb21f7648bf7c86d1826ccaa8cb45712ea15c03bdab78f750e05e3919eacf";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
