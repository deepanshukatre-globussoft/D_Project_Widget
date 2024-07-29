#include "widget.h"
#include "createtask.h"
#include "qdebug.h"

enum class TaskStatus {
    Current,
    Next,
    Future,
    completed
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    ProjectMainLayout = new QVBoxLayout;
//    ProjectMainLayout->setContentsMargins(20,20,20,20);
    ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    containerLayout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(containerLayout);

    QLabel *headingLabel = new QLabel("Task List",this);
    QFont boldFont("Sans Serif",14) ;
//    boldFont.setBold(true);
    headingLabel->setStyleSheet("color: red;");
    headingLabel->setFont(boldFont);
    headingLabel->setContentsMargins(2, 2, 2, 2);


    ProjectCustomWidget *customWidgetProject1 = new ProjectCustomWidget();
    ProjectCustomWidget *customWidgetProject2 = new ProjectCustomWidget();
    ProjectCustomWidget *customWidgetProject3 = new ProjectCustomWidget();
    ProjectCustomWidget *customWidgetProject4 = new ProjectCustomWidget();

    CreateTask *createTaskObj =  new CreateTask();


    QObject::connect(customWidgetProject1, &ProjectCustomWidget::sendData, customWidgetProject1, &ProjectCustomWidget::receiveData);
    QObject::connect(customWidgetProject2, &ProjectCustomWidget::sendData, customWidgetProject2, &ProjectCustomWidget::receiveData);

        emit customWidgetProject1->sendData("Status: In Progress", "Project Alpha", "Task 1", "01:23:45");
    emit customWidgetProject2->sendData("Status: Completed", "Project Beta", "Task 2", "00:45:30");

    QSpacerItem *spacer = new QSpacerItem(10,5);

//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");
//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

    containerLayout->addWidget(headingLabel);
    containerLayout->addWidget(customWidgetProject1); //  for loop use karna hain
    containerLayout->addSpacerItem(spacer);
    containerLayout->addWidget(customWidgetProject2);
    containerLayout->addSpacerItem(spacer);
    containerLayout->addWidget(customWidgetProject3);
    containerLayout->addSpacerItem(spacer);
    containerLayout->addWidget(customWidgetProject4);
    containerLayout->addWidget(createTaskObj);


    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
//    scrollArea->setFixedSize(630,400); // Adjust size dk


    QList<ProjectCustomWidget *> customWidgets = containerWidget->findChildren<ProjectCustomWidget *>();
    for (ProjectCustomWidget *widget : customWidgets) {
        // Check if the widget is selected
        QPushButton *pushbtn = widget->findChild<QPushButton *>();
        qDebug()<<"pushbtn : "<<pushbtn->text();
//        if (checkBox && checkBox->isChecked()) {
//            delete widget;
//        }
    }



//    ProjectMainLayout->addWidget(containerWidget);
    ProjectMainLayout->addWidget(scrollArea);



    setLayout(ProjectMainLayout);
    setFixedSize(650,400);

}

Widget::~Widget()
{
}

