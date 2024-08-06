#include "projectcustomwidget.h"
#include "qdebug.h"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(0,0,0,0);
    m_HMainLayout->setAlignment(Qt::AlignLeft);


    this->setObjectName("customProjectItemWidget") ;
    d_containerWidget = new QWidget(this);
    d_containerLayout = new QVBoxLayout(d_containerWidget);

    d_containerWidget->setObjectName("projectContainerObject");

    QSpacerItem *spacer = new QSpacerItem(5,3);

    d_projectStatuslabel = new QLabel("Project Status ", this);  // shyad public karke access dena hoga
    d_startTaskButton = new QPushButton("start", this);
    d_editTaskButton = new QPushButton("edit", this);
    QFont font;
    font.setFamily("arial"); // Set font family
    font.setPointSize(8);  // Set font size
//    font.setItalic(true); // Set font style (not italic)
    d_editTaskButton->setFont(font);

    d_editTaskButton->setObjectName("myPushBtn");  // Set object name
    //==================================================
    d_projectNameLabel =  new QLabel("Project Name",this);
    //==================================================
    d_taskNameLabel = new QLabel("Task Title",this);
    //==================================================
    d_setReminderbtn = new QPushButton("Set reminder",this);
    d_setReminderbtn->setObjectName("reminderbtnObj");
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
//    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ThirdLayout);
//    d_containerLayout->addSpacerItem(spacer);
    d_containerLayout->addLayout(p_ForthLayout);

    d_containerWidget->setLayout(d_containerLayout);

    setFixedSize(600,100);
    m_HMainLayout->addWidget(d_containerWidget);

//    m_HMainLayout->addSpacerItem(spacer);
//    m_HMainLayout->addLayout(p_SecondLayout);


    setLayout(m_HMainLayout);

}

ProjectCustomWidget::ProjectCustomWidget(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    d_taskActiveTimeLabel->setText(taskActiveTime);
}

void ProjectCustomWidget::receiveData(const QString &projectStatus, const QString &projectName, const QString &taskName, const QString &taskActiveTime)
{
    qDebug()<<"received data  "<<taskName;
//    if(projectStatus == "current task"){
//        d_projectStatuslabel->s
//    }
    d_projectStatuslabel->setText(projectStatus);
    d_projectNameLabel->setText(projectName);
    d_taskNameLabel->setText(taskName);
    d_taskActiveTimeLabel->setText(taskActiveTime);
}
