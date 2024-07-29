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
    buttonLayout = new QVBoxLayout(buttonWidget);
    createTaskButton = new QPushButton("Create Task", buttonWidget);
    submitButton = new QPushButton("Submit", buttonWidget);
    buttonLayout->addWidget(createTaskButton);
    buttonLayout->addWidget(submitButton);
    createTaskMainLayout->addWidget(buttonWidget);

    setLayout(createTaskMainLayout);

}

void CreateTask::populateComboBoxes()
{
    QList<QString> projectNames = {"Project A", "Project B", "Project C", "Project D"};

    // Populate project combo box using a for loop
    for (int i = 0; i < projectNames.size(); ++i) {
        projectComboBox->addItem(projectNames[i], i);
    }

    // Populate task combo box with explicit values
    taskComboBox->addItem("Current", static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem("Future", static_cast<int>(TaskStatus::Future));
    taskComboBox->addItem("Next", static_cast<int>(TaskStatus::Next));
    taskComboBox->addItem("completed", static_cast<int>(TaskStatus::completed));
}
