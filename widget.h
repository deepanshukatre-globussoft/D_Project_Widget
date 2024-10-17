#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include "taskmodelclass.h"
#include <QJsonArray>
#include <QPixmap>
#include <QEvent>
#include "createtask.h"

#include <QList>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    static QList<TaskModelClass*> TaskModelClassContainerList;
    static QList<TaskModelClass*> TaskModelSearchFliterContainerList;
    static QList<TaskModelClass*> TaskModelProjectsFliterContainerList;
    static QList<TaskModelClass*> TaskModelFolderFliterContainerList;
    ~Widget();


public:

    QVBoxLayout *ProjectMainLayout;
    QVBoxLayout *containerLayout;
    QWidget *containerWidget;
    QScrollArea *scrollArea;
    QScrollArea * projectsscrollArea;
    MyNetworkManager *networkManager;


    QList<ProjectCustomWidget *> TasksContainerList ; // this will hold all ui task data
    void initConfiguration();
    void deleteConfiguration();


    QWidget *overlayWidget;
    QString token = "0800068e6089f9913a7b17213635e548:687a325872a50fae44b3a54d5bd91764eba5a4dafa9b75499749376bcc6b462fdfb62b98ad0590ec467c0706739db03fe69e4fa8bcceb0950eed3cd120c3cf37839c0d7eaa7b252f5ca29760f25220d91c051ac17de4ca387d3b82a035fd5d394693eb2e25553a6ec30394ac473fdd6c313019fa9cef84c4907e3388f71b724c3bd93f7bdec9bb0515e14c0b4be85db96be9b85dc07958faf15897c20908619c5e5e99fcb458740290765c20fb451ad0297294e1b364207cd36f22de53a98eee092af7eab3bfd12282d98c959e2f3f5194eb4176cb7f011b1c879fb6d1c914dfa7adf33da36868498b89cec79455feb6e45763cbea82cbe15f4770d6271554170bd4281c4e7b48aedfbceea4fd3e41249a21a3201c034022395b83e7e9f5eb65";
    QWidget *overlayCreatetaskWidget;

    void initialize_UI_Components();
    CreateTask * create_task = nullptr;

protected:
           // void showEvent(QShowEvent  *event) override;
           // void hideEvent(QHideEvent *event) override;
           // void moveEvent(QMoveEvent * event) override;
    bool eventFilter(QObject *watched, QEvent *event)
    {
        if (watched == searchbar_widget && event->type() == QEvent::Paint) {
            QPainter painter(searchbar_widget);
            painter.setPen(QPen(QColor(35, 31, 32, 2), 0.5));
            painter.drawRect(searchbar_widget->rect().adjusted(1,1,-1,-1)); // Adjust for precise border
            return true; // Handle the event
        }
        return QWidget::eventFilter(watched, event);
    }

private:
    QPushButton *refreshbtn;
    QPushButton *updatebtn;
    QPushButton * filter_btn;
    QWidget * searchbar_widget;
    QPushButton *pro_btn[20];
    QLabel *pro_name[20];
    QLabel * projects_label;
    QLabel * folders_label;
    QLabel * dkfolders_label;
    QLabel * current_task_label;
    QLabel * dkcurrent_task_label;
    QLabel * next_task_label;
    QLabel * future_task_label;
    QLabel * completed_task_label;
    QWidget * projects_widget;

    QComboBox *projectComboBox;


    void onProjectDataFetched(const QJsonArray &dataArray);
    void onsendingTasksFromAPIdata(const QJsonArray &dataArray);
    void onTaskDataFetched(int count);
private slots:
    void onEmptySignal(); // Test slot for empty signal
    void projectFilterSelect(int index);
    void ondataSenderToComboBoxProjectList(QJsonArray projectIdAndNameList);


};
#endif // WIDGET_H
