#ifndef PROJECTCUSTOMWIDGET_H
#define PROJECTCUSTOMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QByteArray>
#include <QScrollArea>
#include <QTextEdit>
class ProjectCustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectCustomWidget(QWidget *parent = nullptr);

private:
    QLabel *label;
    QPushButton *button;
    QTextEdit *textEdit;

signals:

};

#endif // PROJECTCUSTOMWIDGET_H
