#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    ProjectMainLayout = new QVBoxLayout;
    ProjectMainLayout->setContentsMargins(20,20,20,20);
    ProjectMainLayout->setAlignment(Qt::AlignLeft);

    containerWidget = new QWidget(this);
    containerLayout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(containerLayout);

    ProjectCustomWidget *customWidgetProject1 = new ProjectCustomWidget();
    ProjectCustomWidget *customWidgetProject2 = new ProjectCustomWidget();
    ProjectCustomWidget *customWidgetProject3 = new ProjectCustomWidget();
    ProjectCustomWidget *customWidgetProject4 = new ProjectCustomWidget();

    QSpacerItem *spacer = new QSpacerItem(10,5);

//    ProjectMainLayout->addWidget(customWidgetProject1); //  for loop use karna hain
//    ProjectMainLayout->addSpacerItem(spacer);
//    ProjectMainLayout->addWidget(customWidgetProject2);
//    ProjectMainLayout->addSpacerItem(spacer);
//    ProjectMainLayout->addWidget(customWidgetProject3);
//    ProjectMainLayout->addSpacerItem(spacer);
//    ProjectMainLayout->addWidget(customWidgetProject4);
//        containerWidget->setStyleSheet("background-color: blue;");

    containerLayout->addWidget(customWidgetProject1); //  for loop use karna hain
    containerLayout->addSpacerItem(spacer);
    containerLayout->addWidget(customWidgetProject2);
    containerLayout->addSpacerItem(spacer);
    containerLayout->addWidget(customWidgetProject3);
    containerLayout->addSpacerItem(spacer);
    containerLayout->addWidget(customWidgetProject4);


    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(650,400); // Adjust size dk


    ProjectMainLayout->addWidget(containerWidget);

    setLayout(ProjectMainLayout);
    setFixedSize(650,400);

}

Widget::~Widget()
{
}

