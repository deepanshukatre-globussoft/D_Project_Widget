#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include "taskmodelclass.h"
#include <QJsonArray>

#include <QList>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    static QList<TaskModelClass*> TaskModelClassContainerList;
    ~Widget();


public:

    QVBoxLayout *ProjectMainLayout;
    QVBoxLayout *containerLayout;
    QWidget *containerWidget;
    QScrollArea *scrollArea;
    MyNetworkManager *networkManager;


    QList<ProjectCustomWidget *> TasksContainerList ;
    void initConfiguration();
    void deleteConfiguration();
    QString token = "dee2efec548e446ad8d772b50c086ce3:4eeec7e072808002bea3da14ecf93a279b476e2afd35db450764d84fe78da3d54140d27b292420aa832536041c2d002a5750c24b335bdaf29a003e06777ecedcc6dfe7444fb11afd05011e84806a1b71f71ebc60a6354b465b7b61a4379a366130c388e74958e2b838ccafcb2029707ce78b97faecd4eb1e929e58d081fa75b281f6b2fa711db6f5844d76a6f4801aabe37c3c868b0c4853bb1244a907c07e89a064698422a726b1f5f1702881c5b39d7e86b894af03c2c087aec41b4c56190c625b6f29b7d76dca268c21c512e62a6038cb4dd673d8a0c50aa33a73b27141b484cb96a0bf293543303e6ed3246b4a979b00695a2ef52df2ef33763fc1d2027eabe7b6a3fda76ecbcf31b085e1775768c8f6bdd80ea1b63903d084b112a18c1f";
private:
    QPushButton *refreshbtn;
    QPushButton *updatebtn;
    void onProjectDataFetched(const QJsonArray &dataArray);
    void onsendingTasksFromAPIdata(const QJsonArray &dataArray);
    void onTaskDataFetched();
private slots:
        void onEmptySignal(); // Test slot for empty signal
};
#endif // WIDGET_H
