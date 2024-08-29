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
    QList<QString> projectNames = {"Select Project", "Project A", "Project B", "Project C", "Project D"};

    // Populate project combo box using a for loop
    for (int i = 0; i < projectNames.size(); ++i) {
        projectComboBox->addItem(projectNames[i], i);
    }

    // Populate task combo box with explicit values
//    taskComboBox->addItem("Current", static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem("Select Folder");
    taskComboBox->addItem(QIcon("://imgs/blue_icon.png"),"Current", static_cast<int>(TaskStatus::Current));
    taskComboBox->addItem(QIcon("://imgs/red_circle.png"),"Future", static_cast<int>(TaskStatus::Future));
    taskComboBox->addItem(QIcon("://imgs/yellow_circle.png"),"Next", static_cast<int>(TaskStatus::Next));
    taskComboBox->addItem(QIcon("://imgs/green_circle.png"),"Completed", static_cast<int>(TaskStatus::completed));
}

void CreateTask::onCancelClicked()
{
    QString token = "45f9e4414332e8a0190601642b08bc15:1809c86ee5ea347d536cf7c6c180717b8cc0d177fa5c4993cabe2098fb538d5afe52cf3131894b77ccaaf162b21a64a54fb80769e04b6df8471a6ee07fa5833e2aed5c6409880f50b72df5290f90ed050b84c76cce7f2b58ae83e6686da051ab6bbc49aae3900ca34d15937deb3c2395ca621380c952d9986e9d79443196ad2a08b6324c07e9e00e9fae487cacf8423f7f27ea1c7ef8227ccb9ed6209a5942f9ce4fc8628d5f34a9eebbb5c2b0582b6a4fbb7ced97d4a40a782954cc0be5ba1ca6c8389718daebb47ef20dd2b6552909e18e2bef695bb115618e12eeb9d0e8e26d843764d9485186498e2fe2720b97aa81c572a681b4e69d47aabbbb19647965d0a9cfa892e1273827e81f7e9966ddaeac5e076dc7daa1725211e6d808b1549d";
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
