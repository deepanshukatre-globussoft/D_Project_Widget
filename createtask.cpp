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
    setFixedSize(338,310);
    this->setWindowTitle(tr("Create Task"));
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    this->setObjectName("createWidget");
    createTaskMainLayout = new QVBoxLayout(this);
    createTaskMainLayout->setContentsMargins(22,22,22,22);

//    createTaskLabel = new QLabel(tr("Create Task"), this);
//    createTaskMainLayout->addWidget(createTaskLabel);
    QString styleSheet = QString(
        "QComboBox {"
        "background-color: #F8F8F8;"
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

    // QFont label_font("Ubuntu",16,400);

    nameWidget = new QWidget(this);
    nameLayout = new QVBoxLayout(nameWidget);
    nameLabel = new QLabel(tr("Title"), nameWidget);
    nameLineEdit = new QLineEdit(nameWidget);
    // nameLineEdit->setFocusPolicy(Qt::NoFocus);

    nameLineEdit->setPlaceholderText(tr("Enter Title"));
    nameLineEdit->setFixedSize(290,37);
   // nameLineEdit->setFont(font);
    nameLineEdit->setStyleSheet("padding: 10px; background-color: #F8F8F8; border: 0.5px solid #231F2033; border-radius:5px;");

    nameLayout->setContentsMargins(0,0,0,0);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    createTaskMainLayout->addWidget(nameWidget);

    projectWidget = new QWidget(this);
    projectLayout = new QVBoxLayout(projectWidget);
    projectLabel = new QLabel(tr("Project"), projectWidget);
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
    check_box->setStyleSheet("color: 1px solid rgba(35, 31, 32, 0.2)");
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
    cancelBtn = new QPushButton(tr("Cancel"), buttonWidget);
    createBtn = new QPushButton(tr("Create Task"), buttonWidget);

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

    //signals and slots
    connect(check_box,&QCheckBox::stateChanged,[=](int state){
        qDebug() << "Checkbox state:" << state;
        if (state == Qt::Checked) {
            qDebug() << "Checkbox is checked";
            isStarted = true;
        } else if (state == Qt::Unchecked) {
            qDebug() << "Checkbox is unchecked";
            isStarted = false;
        } else {
            qDebug() << "Checkbox is partially checked";
        }
    });

    connect(cancelBtn, &QPushButton::clicked, this, &CreateTask::onCancelClicked);
    connect(createBtn, &QPushButton::clicked, this, &CreateTask::onCreateTaskClicked);

}

void CreateTask::populateComboBoxes()
{
    // QList<QString> projectNames = {"Select Project", "Project A", "Project B", "Project C", "Project D"};

    // // Populate project combo box using a for loop
    // for (int i = 0; i < projectNames.size(); ++i) {
    //     projectComboBox->addItem(projectNames[i], i);
    // }
    // for (auto it = projectMap.begin(); it != projectMap.end(); ++it) {
    //     qDebug() << "Project Name:" << it.key() << ", Project ID:" << it.value();
    // }

    // Populate task combo box with explicit values
//    taskComboBox->addItem("Current", static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem("Select Folder");
    taskComboBox->addItem(QIcon("://imgs/blue_icon.png"),tr("Current Task"), static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem(QIcon("://imgs/red_circle.png"),tr("Future Task"), static_cast<int>(TaskStatus::Future));
    taskComboBox->addItem(QIcon("://imgs/yellow_circle.png"),tr("Next Task"), static_cast<int>(TaskStatus::Next));
    // taskComboBox->addItem(QIcon("://imgs/green_circle.png"),tr("Completed"), static_cast<int>(TaskStatus::completed));
}

void CreateTask::onCancelClicked()
{
    this->deleteLater();
    QString token = "304cbae7bad0452668fe60c820f54818:ad5c6429e43943072a1bd94f773f6c189411fc8fa88eddb2c94f2720c6bdc4ca881832a5488dec07bfaa033083d0585cb2a66666bf39390343a476840d3bb557da39b546c18c71d6d882f5312b0cb6311246e3c1ffdc1182bbcfa6d0dcc8e578b8ed9bc817a66f1e7cf4dc1c7cd84a48117705ab6283a3fa90f64d29f8614ab7f9b77ade98c314eba03b3a6a1959b89756df3c81621bb4445edb44dec41aae0a46237a3f8faf987f8e294150ac3c0427ac6a5e6f9cefaf4a05f6929d5e653fa9c92971ba19e8f8e6d90f4dfb3a956c3123093c362add64c177aea0474284e5305099ba20bd71a217af4b6a6be2abc4b9c92f04be2f0d4d9d956a77eaf7263857e80c9cf879187f84609c04bcfddd82327d1071bc398569ac9fa250d0f3848df6";
    qDebug() << "NetworkManager netMgrObj:" << netMgrObj;
//    netMgrObj->fetchProjectData(token,0,10);
    netMgrObj->fetchTasksForMobileList(token,10);
}

void CreateTask::onCreateTaskClicked()
{
    QString taskText = nameLineEdit->text();
    QString folderText = taskComboBox->currentText();
    QString projectText = projectComboBox->currentText();

    if(!taskText.isEmpty() && folderText != "Select Folder" && projectText != "Select Project"){
        QString message = QString("Submit Button Clicked:\nLine Edit: %1\nComboBox 1: %2\nComboBox 2: %3")
                              .arg(taskText, folderText, projectText);

        // QMessageBox::information(this, "Submitted Data", message);
        this->deleteLater();
        if(createBtn->text() == "Create Task")
            emit sendToCreateTask(taskText, folderText, projectText, isStarted);
        else{
        }
            // emit sendToUpdateTask(taskText,"","",folderText,isStarted);
            // netMgrObj->toUpdateTask("",)
    } else{
        notify.setText("Tasks details should not be empty...!");
        notify.exec();
    }
}
