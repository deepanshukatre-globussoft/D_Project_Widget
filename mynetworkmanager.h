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
#include <QMessageBox>

class MyNetworkManager : public QObject
{
    Q_OBJECT
public:
//    void createTask(const QString &authToken, const QString &data);
    static MyNetworkManager* instance();
    QNetworkAccessManager *networkManager;

    QString token = "6b52374aa22159ebd0c6da2292b4be41:6e8e67545005fb408234c632323e925a986ecbaed7e6a867d2466319c5b179144e51590c7a64c7086d5ec1dca39f8d9b21c7cc8d288da1648c3d40fbeae553c2ea737500e819b83fc94de770766e03111fd8aca541b262ca0a816faec8e069d2ee0a76737f0429942f0bd56142f0cbb1102dca0c400637db6edff0ff6ac7bf4ce52ca1d4f0c740f869ed1755ee7553c15c5317f9ca4702e01d0952a0dcd106c318f53096afa7b6fb6b62c7dd959e8f5c6951319d40f8c6a403aa8a879a3df1b2211d68261491e1f1719897190011c57a7d16346f76e71e7e9391637afb6cabad57a092f42e366193c97034e3d25f2cac7579e0f837ca884bc979cec64d821144025471ee5515b39d87160c4c0604650746c97486434f1228ee9555657b90575e";
    QJsonArray dataArray;
    void fetchProjectData(const QString &authToken, int skip, int limit);
    void fetchTasksForMobileList(const QString &authToken, int skip, int limit, const QString &searchText,
                                 const QString &task_id, const QString &project_id, const QString &folder_name,
                                 const QString &start_date, const QString &end_date, const QString &sort_by);
    bool fetchTasksForMobileList(const QString &authToken, int skip);

    //project id, title, description we will get here
    void getAllProjects(const QString &authToken);

    // creating a task using create task page
    void createTasks(const QString &authToken,const QString &title,const QString &folder_name,const QString &project_id);
    void deleteTaskApi(const QString &authToken,const QString &taskid);
    void completedTaskApi(const QString &authToken,const QString &taskid);
    void startTaskApi(const QString &authToken,const QString &taskid);
    void stopTaskApi(const QString &authToken,const QString &taskid);

    // filtering api's
    void allTasksInSeletedFolder(const QString &authToken,const QString &folder_name, int skip, int limit);
    void allTasksInSeletedProject(const QString &authToken,const QString &project_id, int skip, int limit);
    void allTasksInSeletedSearchKeyword(const QString &authToken,const QString &searchItem, int skip, int limit);
signals:
    void projectDataFetched(const QJsonArray &dataArray);
    void taskDataFetched(int count);
    void sendingTasksFromAPIdataSignal(QJsonArray dataArray);
    void deleteConfigurationsignal();
    void initConfigurationsignal();

    void dataSenderToComboBoxProjectList(const QJsonArray& projectIdAndNameList);

    void taskStartDataSignal(const QString& taskid,bool success,const QString& time);


public slots:
    void onProjectDataFetched(QNetworkReply *reply);
    void onTasksDataFetched(QNetworkReply *reply);

    void onProjectIdAndNameDataFetched(QNetworkReply *reply);



    void testslot();

private:
    explicit MyNetworkManager(QObject *parent = nullptr);
    MyNetworkManager(const MyNetworkManager&) = delete;
    MyNetworkManager& operator=(const MyNetworkManager&) = delete;
    static MyNetworkManager* m_instance;
};

#endif // MYNETWORKMANAGER_H
