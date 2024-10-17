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
    QComboBox *projectComboBox;

    QWidget *taskWidget;
    QVBoxLayout *taskLayout;
    QLabel *taskLabel;
    QComboBox *taskComboBox;

    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *cancelBtn;

    QString hiddenFieldId;

    bool isStarted = false;
    QString token = "0800068e6089f9913a7b17213635e548:687a325872a50fae44b3a54d5bd91764eba5a4dafa9b75499749376bcc6b462fdfb62b98ad0590ec467c0706739db03fe69e4fa8bcceb0950eed3cd120c3cf37839c0d7eaa7b252f5ca29760f25220d91c051ac17de4ca387d3b82a035fd5d394693eb2e25553a6ec30394ac473fdd6c313019fa9cef84c4907e3388f71b724c3bd93f7bdec9bb0515e14c0b4be85db96be9b85dc07958faf15897c20908619c5e5e99fcb458740290765c20fb451ad0297294e1b364207cd36f22de53a98eee092af7eab3bfd12282d98c959e2f3f5194eb4176cb7f011b1c879fb6d1c914dfa7adf33da36868498b89cec79455feb6e45763cbea82cbe15f4770d6271554170bd4281c4e7b48aedfbceea4fd3e41249a21a3201c034022395b83e7e9f5eb65";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
