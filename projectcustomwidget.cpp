#include "projectcustomwidget.h"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(0,0,0,0);
    m_HMainLayout->setAlignment(Qt::AlignLeft);

    QSpacerItem *spacer = new QSpacerItem(10,5);

    d_projectStatuslabel = new QLabel("Project Name ", this);  // shyad public karke access dena hoga
    d_startTaskButton = new QPushButton("start", this);
    d_editTaskButton = new QPushButton("edit", this);
//    textEdit = new QTextEdit(this);

    p_FirstLayout = new QHBoxLayout;
    p_FirstLayout->addWidget(d_projectStatuslabel);
    p_FirstLayout->addStretch();
    p_FirstLayout->addWidget(d_startTaskButton);
    p_FirstLayout->addWidget(d_editTaskButton);

//    p_SecondLayout = new QHBoxLayout;
//    p_SecondLayout->addWidget(label);
//    p_SecondLayout->addWidget(button);
//    p_SecondLayout->addWidget(textEdit);


    setFixedSize(600,100);
    m_HMainLayout->addLayout(p_FirstLayout);
//    m_HMainLayout->addSpacerItem(spacer);
//    m_HMainLayout->addLayout(p_SecondLayout);


    setLayout(m_HMainLayout);

//    this->setStyleSheet("background-color: blue;");
}
