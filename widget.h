#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include "taskmodelclass.h"
#include <QJsonArray>
#include <QPixmap>
#include <QEvent>

#include <QList>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    static QList<TaskModelClass*> TaskModelClassContainerList;
    static QList<TaskModelClass*> TaskModelFliterContainerList;
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
    QString token = "45f9e4414332e8a0190601642b08bc15:1809c86ee5ea347d536cf7c6c180717b8cc0d177fa5c4993cabe2098fb538d5afe52cf3131894b77ccaaf162b21a64a54fb80769e04b6df8471a6ee07fa5833e2aed5c6409880f50b72df5290f90ed050b84c76cce7f2b58ae83e6686da051ab6bbc49aae3900ca34d15937deb3c2395ca621380c952d9986e9d79443196ad2a08b6324c07e9e00e9fae487cacf8423f7f27ea1c7ef8227ccb9ed6209a5942f9ce4fc8628d5f34a9eebbb5c2b0582b6a4fbb7ced97d4a40a782954cc0be5ba1ca6c8389718daebb47ef20dd2b6552909e18e2bef695bb115618e12eeb9d0e8e26d843764d9485186498e2fe2720b97aa81c572a681b4e69d47aabbbb19647965d0a9cfa892e1273827e81f7e9966ddaeac5e076dc7daa1725211e6d808b1549d";
    QWidget *overlayWidget;

protected:
    // void showEvent(QShowEvent  *event) override;
    void hideEvent(QHideEvent *event) override;
    void moveEvent(QMoveEvent * event) override;

private:
    QPushButton *refreshbtn;
    QPushButton *updatebtn;
    QPushButton * filter_btn;
    void onProjectDataFetched(const QJsonArray &dataArray);
    void onsendingTasksFromAPIdata(const QJsonArray &dataArray);
    void onTaskDataFetched(int count);
private slots:
    void onEmptySignal(); // Test slot for empty signal
};
#endif // WIDGET_H
