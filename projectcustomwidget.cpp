#include "projectcustomwidget.h"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(0,0,0,0);
    m_HMainLayout->setAlignment(Qt::AlignLeft);

    d_containerWidget = new QWidget(this);
    d_containerLayout = new QVBoxLayout(d_containerWidget);
//    d_containerWidget->setLayout(d_containerLayout);

    QSpacerItem *spacer = new QSpacerItem(5,3);

    d_projectStatuslabel = new QLabel("Project Status ", this);  // shyad public karke access dena hoga
    d_startTaskButton = new QPushButton("start", this);
    d_editTaskButton = new QPushButton("edit", this);
    //==================================================
    d_projectNameLabel =  new QLabel("Project Name",this);
    //==================================================
    d_taskNameLabel = new QLabel("Task Title",this);
    //==================================================
    d_setReminderbtn = new QPushButton("Set reminder",this);
    d_taskActiveTimeLabel = new QLabel("00:00:00",this);

    p_FirstLayout = new QHBoxLayout;
    p_FirstLayout->addWidget(d_projectStatuslabel);
    p_FirstLayout->addStretch();
    p_FirstLayout->addWidget(d_startTaskButton);
    p_FirstLayout->addWidget(d_editTaskButton);


    p_SecondLayout = new QHBoxLayout;
    p_SecondLayout->addWidget(d_projectNameLabel,Qt::AlignLeft);

    p_ThirdLayout = new QHBoxLayout;
    p_ThirdLayout->addWidget(d_taskNameLabel,Qt::AlignLeft);

    p_ForthLayout = new QHBoxLayout;
    p_ForthLayout->addWidget(d_setReminderbtn);
    p_ForthLayout->addStretch();
    p_ForthLayout->addWidget(d_taskActiveTimeLabel);


    d_containerLayout->addLayout(p_FirstLayout);
    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_SecondLayout);
    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ThirdLayout);
    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ForthLayout);

    d_containerWidget->setLayout(d_containerLayout);

    setFixedSize(600,100);
    m_HMainLayout->addWidget(d_containerWidget);

//    m_HMainLayout->addSpacerItem(spacer);
//    m_HMainLayout->addLayout(p_SecondLayout);


    setLayout(m_HMainLayout);

//    this->setStyleSheet("background-color: blue;");
}
