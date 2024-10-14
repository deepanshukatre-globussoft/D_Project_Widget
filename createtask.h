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

    QString token = "30765ca695d7dbb06b2e77101711097c:f1ab3a8a390bcacd69ad89df5d3130a77e5de779babc6102c9f616eac600cc460237644a69bde909f69ffa23de44c363d68c8d2ef3d7dbd4d7e3c2b639b687e70ae644f8007a40066669b1fd1f615aa786d3abbcafae05bdb0b536194216d0675d4499929b2f1a56578c23dc017e21408011cf3de8d672e2b5055aa4dfd87437146b3246cf2a2aedf4e7ff0db663ed33bfefcdb6878fd95cf225c70154cb07aab869cc51f585654b1004197f222723259cf660f765b2dc9fe0ba96b5486672f77af419d6bc87b3abba776827143c4e59b9e1a1aefdae758fe0cce534c67fdee39774a071aec4047e7619d449d71e86598335e4c3288b5b43701a6457491751523cc32eacac9d851b05d16a6eade16d3c34552b08b5a9d6531739aa66d47dce94";

private slots:
    void onCancelClicked();
    void onCreateTaskClicked();
    void onComboBoxActivated(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);

};

#endif // CREATETASK_H
