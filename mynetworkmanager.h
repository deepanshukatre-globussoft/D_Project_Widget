#ifndef MYNETWORKMANAGER_H
#define MYNETWORKMANAGER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include<QJsonDocument>
#include<QJsonObject>
#include <QObject>
#include <QUrlQuery>
#include <QJsonArray>

class MyNetworkManager : public QObject
{
    Q_OBJECT
public:
//    void createTask(const QString &authToken, const QString &data);
    static MyNetworkManager* instance();
    QNetworkAccessManager *networkManager;

    QJsonArray dataArray;
    void fetchProjectData(const QString &authToken, int skip, int limit);
    void fetchTasksForMobileList(const QString &authToken, int skip, int limit, const QString &searchText,
                                 const QString &task_id, const QString &project_id, const QString &folder_name,
                                 const QString &start_date, const QString &end_date, const QString &sort_by);
    bool fetchTasksForMobileList(const QString &authToken, int skip);

signals:
    void projectDataFetched(const QJsonArray &dataArray);
//    void taskDataFetched(const QJsonArray &dataArray);
    void taskDataFetched(const QString &id, const QString &title, const QString &folderName, const QString &projectTitle);

    void deleteConfigurationsignal();
    void initConfigurationsignal();

public slots:
    void onProjectDataFetched(QNetworkReply *reply);
    void onTasksDataFetched(QNetworkReply *reply);

    void testslot();

private:
    explicit MyNetworkManager(QObject *parent = nullptr);
    MyNetworkManager(const MyNetworkManager&) = delete;
    MyNetworkManager& operator=(const MyNetworkManager&) = delete;
    static MyNetworkManager* m_instance;
};

#endif // MYNETWORKMANAGER_H
