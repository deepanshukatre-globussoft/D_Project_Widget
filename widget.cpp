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

//    customWidgetProject1->setStyleSheet("background-color: #f0dfdf;");
//    customWidgetProject2->setStyleSheet("background-color: #0078D4;");
//    customWidgetProject3->setStyleSheet("background-color: #dbc3c4;");

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

