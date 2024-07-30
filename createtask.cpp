#include "createtask.h"

enum class TaskStatus {
    Current,
    Next,
    Future,
    completed
};
CreateTask::CreateTask(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
    populateComboBoxes();
}

void CreateTask::setupUI()
{
    createTaskMainLayout = new QVBoxLayout(this);

    createTaskLabel = new QLabel("Create Task", this);
    createTaskMainLayout->addWidget(createTaskLabel);

    nameWidget = new QWidget(this);
    nameLayout = new QVBoxLayout(nameWidget);
    nameLabel = new QLabel("Name", nameWidget);
    nameLineEdit = new QLineEdit(nameWidget);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);
    createTaskMainLayout->addWidget(nameWidget);

    projectWidget = new QWidget(this);
    projectLayout = new QVBoxLayout(projectWidget);
    projectLabel = new QLabel("Project", projectWidget);
    projectComboBox = new QComboBox(projectWidget);
    projectLayout->addWidget(projectLabel);
    projectLayout->addWidget(projectComboBox);
    createTaskMainLayout->addWidget(projectWidget);

    taskWidget = new QWidget(this);
    taskLayout = new QVBoxLayout(taskWidget);
    taskLabel = new QLabel("Task", taskWidget);
    taskComboBox = new QComboBox(taskWidget);
    taskLayout->addWidget(taskLabel);
    taskLayout->addWidget(taskComboBox);
    createTaskMainLayout->addWidget(taskWidget);

    buttonWidget = new QWidget(this);
    buttonLayout = new QHBoxLayout(buttonWidget);
    createTaskButton = new QPushButton("Create Task", buttonWidget);
    cancelButton = new QPushButton("Get Task", buttonWidget);
    buttonLayout->addWidget(createTaskButton);
    buttonLayout->addWidget(cancelButton);
    createTaskMainLayout->addWidget(buttonWidget);

    setLayout(createTaskMainLayout);

    connect(cancelButton, &QPushButton::clicked, this, &CreateTask::onCancelClicked);
    connect(createTaskButton, &QPushButton::clicked, this, &CreateTask::onCreateTaskClicked);



}

void CreateTask::populateComboBoxes()
{
    QList<QString> projectNames = {"Project A", "Project B", "Project C", "Project D"};

    // Populate project combo box using a for loop
    for (int i = 0; i < projectNames.size(); ++i) {
        projectComboBox->addItem(projectNames[i], i);
    }

    // Populate task combo box with explicit values
//    taskComboBox->addItem("Current", static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem(QIcon("://imgs/blue_icon.png"),"current", static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem(QIcon("://imgs/red_circle.png"),"Future", static_cast<int>(TaskStatus::Future));
    taskComboBox->addItem(QIcon("://imgs/yellow_circle.png"),"Next", static_cast<int>(TaskStatus::Next));
    taskComboBox->addItem(QIcon("://imgs/green_circle.png"),"completed", static_cast<int>(TaskStatus::completed));
}

void CreateTask::onCancelClicked()
{
    QString token = "783274e810b3f1a52676fe27f4d2e838:efb52ea9f8240c01532d3bee22c329516eba13379b1101369d332ae4e8dad4447e5d666d01aacf0d258b3010fb685e85df6361301d197db4bd7be4a1634b8cf326a8c3f0d7b3e21d1db7c9d6f38bc2bb2e9c130abf8053d93ae99cddb38d4d774b8e4c475052429b000d0351ca32edf968d27247182cc295d38002b031c4ba5ac5b23b3b24c8fc0b94c2e44cd033f3eebdbb554ce66a4f0acbe58b9161a9ca55859dd871dbd73e1c7ec19f943220e1e55b77559bc36742afb1df138d9bc0f89c6534d10fda675229aa0e3cbe10247f2c27a78c16dadac63d01ca3309c80c8acf90ed7cf063651f3dba7423627bfdc9fdf4ece6db8dc72185e1f515a81196551afc430c7bd603ad3b5d146da7f0ce25f71159d27a748982fca4d5d8f390e52012";

    //    netMgrObj->fetchProjectData(const QString &authToken, int skip, int limit);
    netMgrObj.fetchProjectData(token,0,10);
}

void CreateTask::onCreateTaskClicked()
{


    QString lineEditText = nameLineEdit->text();
    QString comboBox1Text = taskComboBox->currentText();
    QString comboBox2Text = projectComboBox->currentText();

    QString message = QString("Submit Button Clicked:\nLine Edit: %1\nComboBox 1: %2\nComboBox 2: %3")
                          .arg(lineEditText, comboBox1Text, comboBox2Text);

    QMessageBox::information(this, "Submitted Data", message);

}
