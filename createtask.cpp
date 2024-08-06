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
    netMgrObj =  MyNetworkManager::instance();
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
    QString token = "2346252ac9794f017f20664aad9a8a60:9c105694f52112bf40aa4ee280739b8ce8bb31e75fc74cac81d93885eb8758c15216f7db5caf88ef8543b8f383c6877cfd86009d607a488f7cc74cf6dfbc09d9efc8c4ace5e9938bfbb7978dc45ba3c411dbe273cb9c9e037403f5870fd9c57b6ac8a32aaf3bdca43fa0fe9500e62cc7edfde6ddac6ae0f8199d48597a01ce150ffd1175124e7ea15c6238546eff707485d12ff6547b13a58c5a2a98bfb87912c36fa4468290b83cab690a62a5e70ed6df5944a460a61dffd71583cc3b416769ccda67e6e163746e11ebb868adda9f66ff9d603cbf37288af822b4bc069b07ea5f13bd0792e2dd93945fd4f1b84034c59476e86678db1ac2426f60e619ba18576d68d8bc20eb9a63f52fbda6755ccc8332edab64a3d7f4791ff79b5776fcf752";
    qDebug() << "NetworkManager netMgrObj:" << netMgrObj;
//    netMgrObj->fetchProjectData(token,0,10);
    netMgrObj->fetchTasksForMobileList(token,10);
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
