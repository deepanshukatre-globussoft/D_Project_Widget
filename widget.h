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
    QString token = "2346252ac9794f017f20664aad9a8a60:9c105694f52112bf40aa4ee280739b8ce8bb31e75fc74cac81d93885eb8758c15216f7db5caf88ef8543b8f383c6877cfd86009d607a488f7cc74cf6dfbc09d9efc8c4ace5e9938bfbb7978dc45ba3c411dbe273cb9c9e037403f5870fd9c57b6ac8a32aaf3bdca43fa0fe9500e62cc7edfde6ddac6ae0f8199d48597a01ce150ffd1175124e7ea15c6238546eff707485d12ff6547b13a58c5a2a98bfb87912c36fa4468290b83cab690a62a5e70ed6df5944a460a61dffd71583cc3b416769ccda67e6e163746e11ebb868adda9f66ff9d603cbf37288af822b4bc069b07ea5f13bd0792e2dd93945fd4f1b84034c59476e86678db1ac2426f60e619ba18576d68d8bc20eb9a63f52fbda6755ccc8332edab64a3d7f4791ff79b5776fcf752";

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
    void onTaskDataFetched();
private slots:
    void onEmptySignal(); // Test slot for empty signal
};
#endif // WIDGET_H
