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


    QString token = "bf53e5323d1376b449659f98cde5cffd:bc360e76839ffc4e5b26fc4ce69f3d47668c34affed8cae5d1f6b06c33e63ad910de52edc97583bcec522635acb999a379fbcafa272163a1989fb2f3593bcb77d320fe87c2591bacbbbe567a0de3e90f21b31d7d6d26c40dfff4c157551536cf4ac5954678224b4448c22f33905d9acebde915a21e35e84fbf372e409da26eec5c76470f1a36b0e4d7725ac7b7e85efc1fc4f8a890f7969481352cbed1c65c22bcd30ee6920bd9ed5a5edf7fe89ed176a724a1260731a0831889edc635fb36bf55eb4b7329f08df91754ec7216a2fb2dd080a0948437c723c0fa3834c64409436bd8e67cfbef80969b6e2d5c63941d925262d92d7f0e5f45d3d18378632f34953c1784752426f6f90913be5264f74aac57c78bf17f9fa10575395a0d79e06b46";
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
