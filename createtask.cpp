#include "createtask.h"

enum class FolderStatus {
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

    //    connect(projectComboBox, QOverload<int>::of(&QComboBox::activated), this, &CreateTask::onComboBoxActivated);

    connect(netMgrObj,&MyNetworkManager::dataSenderToComboBoxProjectList,this,&CreateTask::ondataSenderToComboBoxProjectList);

    netMgrObj->getAllProjects(token);

}

CreateTask::~CreateTask()
{
    this->close();
}

void CreateTask::setupUI()
{
    setFixedSize(338,310);
    this->setWindowTitle(tr("Create Task"));
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    createTaskMainLayout = new QVBoxLayout(this);
    createTaskMainLayout->setContentsMargins(22,22,22,22);


    //    createTaskLabel = new QLabel(tr("Create Task"), this);
    //    createTaskMainLayout->addWidget(createTaskLabel);
    QString styleSheet = QString(
        "QComboBox {"
        "border-radius: 5px;"
        "border: 0.5px solid #231F2033;"
        "padding-left :10px;"
        "}"
        "QComboBox::drop-down {"
        "border: none;"
        "width: 0px;"
        "}"
        "QComboBox::down-arrow {"
        "image: url(://imgs/ep_arrow.svg);"
        "padding-right : 55px;"
        "}");

    nameWidget = new QWidget(this);
    nameLayout = new QVBoxLayout(nameWidget);
    nameLabel = new QLabel("Title", nameWidget);
    nameLineEdit = new QLineEdit(nameWidget);
    // nameLineEdit->setFocusPolicy(Qt::NoFocus);

    //    nameLabel->setFont(font);
    nameLineEdit->setPlaceholderText("Enter Title");
    nameLineEdit->setFixedSize(290,37);
    // nameLineEdit->setFont(font);
    nameLineEdit->setStyleSheet("padding: 10px;  border: 0.5px solid #231F2033; border-radius:5px;");

    nameLayout->setContentsMargins(0,0,0,0);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    createTaskMainLayout->addWidget(nameWidget);

    projectWidget = new QWidget(this);
    projectLayout = new QVBoxLayout(projectWidget);
    projectLabel = new QLabel("Project", projectWidget);
    projectComboBox = new QComboBox(projectWidget);

    //    projectLabel->setFont(font);

    projectComboBox->setFixedSize(290,37);
    //    projectComboBox->setFont(font);
    projectComboBox->setStyleSheet(styleSheet);

    projectLayout->setContentsMargins(0,0,0,0);
    projectLayout->addWidget(projectLabel);
    projectLayout->addWidget(projectComboBox);
    projectWidget->setLayout(projectLayout);
    createTaskMainLayout->addStretch();
    createTaskMainLayout->addWidget(projectWidget);

    taskWidget = new QWidget(this);
    taskLayout = new QVBoxLayout(taskWidget);
    taskLabel = new QLabel(tr("Folder"), taskWidget);
    taskComboBox = new QComboBox(taskWidget);

    //    taskLabel->setFont(font);

    taskComboBox->setFixedSize(290,37);
    //    taskComboBox->setFont(font);
    taskComboBox->setStyleSheet(styleSheet);

    taskLayout->setContentsMargins(0,0,0,0);
    taskLayout->addWidget(taskLabel);
    taskLayout->addWidget(taskComboBox);
    createTaskMainLayout->addStretch();
    createTaskMainLayout->addWidget(taskWidget);

    QWidget * checkbox_widget = new QWidget(this);
    QVBoxLayout *checkbox_layout = new QVBoxLayout(checkbox_widget);
    QCheckBox * check_box = new QCheckBox(this);
    check_box->setText(tr("Start Task Now"));
    // check_box->setStyleSheet("color: 1px solid rgba(35, 31, 32, 0.2)");
    // check_box->setStyleSheet("QCheckBox::indicator {"
    //                         "width: 16px;"
    //                         "height: 16px;"
    //                         "border: 1px solid rgba(35, 31, 32, 0.2);"
    //                         "color: red;"
    //                         "}"
    //                         "QCheckBox::indicator:checked {"
    //                         "    border: 0.5px solid red;"  // Optional: set background color when checked"
    //                         "color: red;"
    //                         "}");

    checkbox_layout->setContentsMargins(0,0,0,0);
    checkbox_layout->addWidget(check_box);
    checkbox_widget->setLayout(checkbox_layout);
    createTaskMainLayout->addStretch();
    createTaskMainLayout->addWidget(checkbox_widget);
    createTaskMainLayout->addStretch();

    buttonWidget = new QWidget(this);
    buttonLayout = new QHBoxLayout(buttonWidget);
    cancelBtn = new QPushButton("Cancel", buttonWidget);
    createBtn = new QPushButton("Create Task", buttonWidget);

    cancelBtn->setFixedSize(135,37);
    cancelBtn->setFlat(true);
    //    cancelBtn->setFont(font);
    cancelBtn->setStyleSheet("color :#D2232A; border: 1px solid #D2232A; border-radius : 5px;");
    createBtn->setFixedSize(135,37);
    createBtn->setFlat(true);
    //    createBtn->setFont(font);
    createBtn->setStyleSheet("color :white; border-radius : 5px; background-color: #D2232A;");

    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->addWidget(cancelBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(createBtn);
    buttonWidget->setFixedSize(290,42);
    createTaskMainLayout->addWidget(buttonWidget);

    setLayout(createTaskMainLayout);

    connect(cancelBtn, &QPushButton::clicked, this, &CreateTask::onCancelClicked);
    connect(createBtn, &QPushButton::clicked, this, &CreateTask::onCreateTaskClicked);

}

void CreateTask::populateComboBoxes()
{
    taskComboBox->addItem(QIcon("://imgs/blue_icon.png"),"Current Task", static_cast<int>(FolderStatus::Current));
    taskComboBox->addItem(QIcon("://imgs/red_circle.png"),"Future Task", static_cast<int>(FolderStatus::Future));
    taskComboBox->addItem(QIcon("://imgs/yellow_circle.png"),"Next Task", static_cast<int>(FolderStatus::Next));
//    taskComboBox->addItem(QIcon("://imgs/green_circle.png"),"Finished Task", static_cast<int>(FolderStatus::completed)); // user should not create already completed task
}

void CreateTask::onCancelClicked()
{
    this->close();
    //    qDebug() << "NetworkManager netMgrObj:" << netMgrObj;
    ////    netMgrObj->fetchProjectData(token,0,10);
    //    netMgrObj->fetchTasksForMobileList(token,10);
    //    netMgrObj->deleteTaskApi(token,"66fa93cf86b90850bce0ae7d");

}

void CreateTask::onCreateTaskClicked()
{
    QString lineEditText = nameLineEdit->text();

    if (nameLineEdit->text().isEmpty()) {
        nameLineEdit->setStyleSheet("border: 1px solid red;");
        QMessageBox::warning(this, "Input Error", "Task title field is mandatory!");
        return;
    } else {
        nameLineEdit->setStyleSheet("");  // Reset to default style if valid
    }

    QString comboBox1Text = taskComboBox->currentText();
    //    QString comboBox2Text = projectComboBox->currentText();

    QVariant hiddenFieldData = projectComboBox->currentData();

    if (hiddenFieldData.isValid()) {
        hiddenFieldId = hiddenFieldData.toString();
        //        qDebug() << "Selected Project Title:" << comboBox2Text;
        //        qDebug() << "Selected Project ID (Hidden Field):" << hiddenFieldId;
    } else {
        qDebug() << "No hidden data found for the selected item.";
    }

    if(this->windowTitle().contains("Edit")){
        qDebug()<<"update is called"<< this->TaskId;
        netMgrObj->updateTasks(token,lineEditText,this->TaskId,comboBox1Text,hiddenFieldId);
    }else{
        netMgrObj->createTasks(token,lineEditText,comboBox1Text,hiddenFieldId);
    }
    this->close();
    //    QString message = QString("Submit Button Clicked:\nLine Edit: %1\nComboBox 1: %2\nComboBox 2: %3")
    //                          .arg(lineEditText, comboBox1Text, comboBox2Text);

    //    QMessageBox::information(this, "Submitted Data", message);

}

void CreateTask::onComboBoxActivated(int index)
{
    qDebug()<<"comboox is activated" << index;

}

void CreateTask::ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList)
{
    //    qDebug()<<"comboox is activated" << projectIdAndNameList;

    for (const QJsonValue& value : projectIdAndNameList) {
        QJsonObject projectObject = value.toObject();
        QString projectId = projectObject.value("_id").toString();   // Extract _id
        QString projectTitle = projectObject.value("title").toString(); // Extract title

        projectComboBox->addItem(projectTitle, projectId); // title, hidden _id

        qDebug() << "Project ID:" << projectId;
        qDebug() << "Project Title:" << projectTitle;
    }
}
