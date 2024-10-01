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

    QString token = "f8a0b2386437b16f779142b19cdd9f56:c98860891d4885096e1ce9c1bde477d9f6601c606d4acf15544caa2807a3e1f46ebf72b114ab415562e066d2d70747fc33ba10fa529132678969b4c130847e8b21f700207516f9588958f1546e4ca4870db959b69a81bfa2da9be19370c0d68f4a9e0790afaa6d2440429e8395b428c67f48434ef787166736523e315f4652ec1d896aa973963bb0d88b2f09251fece60f4899f561aac579d3babd4c778724af9c62499a8974700afdd7e3a28c7a9a59d3cd2e623ccd29a5d714bc3fce98c35de36825c0b491c80b085e98d192c50d129e98e84ca555bdb7fbad744e5190c7f2103a0fffd4eebe41ce7721d5165a82e25b8a82010c40fad33e7ae2f70c2576c78cfbb9963e655a222ef23e232cd611ce4e2af72b320ab15103251fbbb949aedf";

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
signals:
    void projectDataFetched(const QJsonArray &dataArray);
    void taskDataFetched(int count);
    void sendingTasksFromAPIdataSignal(QJsonArray dataArray);
    void deleteConfigurationsignal();
    void initConfigurationsignal();

    void dataSenderToComboBoxProjectList(const QJsonArray& projectIdAndNameList);


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
