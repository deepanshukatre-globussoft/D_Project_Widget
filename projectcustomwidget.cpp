#include "projectcustomwidget.h"

ProjectCustomWidget::ProjectCustomWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout * m_HMainLayout = new QVBoxLayout;
    m_HMainLayout->setContentsMargins(0,0,0,0);
    m_HMainLayout->setAlignment(Qt::AlignLeft);

    label = new QLabel("Label", this);  // shyad public karke access dena hoga
    button = new QPushButton("Button", this);
    textEdit = new QTextEdit(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);
    layout->addWidget(textEdit);

    setFixedSize(600,100);

    setLayout(layout);
}
