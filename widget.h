#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mynetworkmanager.h"
#include "projectcustomwidget.h"
#include <QJsonArray>

#include <QList>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
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
    QString token = "783274e810b3f1a52676fe27f4d2e838:efb52ea9f8240c01532d3bee22c329516eba13379b1101369d332ae4e8dad4447e5d666d01aacf0d258b3010fb685e85df6361301d197db4bd7be4a1634b8cf326a8c3f0d7b3e21d1db7c9d6f38bc2bb2e9c130abf8053d93ae99cddb38d4d774b8e4c475052429b000d0351ca32edf968d27247182cc295d38002b031c4ba5ac5b23b3b24c8fc0b94c2e44cd033f3eebdbb554ce66a4f0acbe58b9161a9ca55859dd871dbd73e1c7ec19f943220e1e55b77559bc36742afb1df138d9bc0f89c6534d10fda675229aa0e3cbe10247f2c27a78c16dadac63d01ca3309c80c8acf90ed7cf063651f3dba7423627bfdc9fdf4ece6db8dc72185e1f515a81196551afc430c7bd603ad3b5d146da7f0ce25f71159d27a748982fca4d5d8f390e52012";

private:
    QPushButton *refreshbtn;
    QPushButton *updatebtn;
    void onProjectDataFetched(const QJsonArray &dataArray);
    void onTaskDataFetched(const QString &id, const QString &title, const QString &folderName, const QString &projectTitle);
private slots:
        void onEmptySignal(); // Test slot for empty signal
};
#endif // WIDGET_H
