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

    static QString currentFolderSelected;

    QString token = "7d5ed83b64b04ffbeb8cab10c1db0bc8:962438eb10e9cfee075799c62bbb0e157bfb3ab145916e4ee46dde10c3dc514710d3ec60624c26d1d4936b53edeb4702ec6f05554bad3a2d9ed6f815622a200a52365abd3681b2cd911de27581c0f41549d77bce15477610770c6a9763b861460340031c09f0d9ef1be661ee48eb6efda0211f5bbe0d25105fc812e57d45ea2bacdb5ea5d2623dc608fa51153af3756835c1ac39f5cb309428593c18140a444d4beb632e94b5be9bdc10c7feca6915e7126a1fd94cdef0b1092e5c099902c8aa177543bf8aeb9aa258d4dcbb234344f96356a02354c4240b03ba735add580647f9898570cb7675f9507d75b4d7db8f5aeb0b4521d39eeb87ead8a0fe3bc863bdbcedb21f7648bf7c86d1826ccaa8cb45712ea15c03bdab78f750e05e3919eacf";
    QJsonArray dataArray;
    void fetchProjectData(const QString &authToken, int skip, int limit);
    // void fetchTasksForMobileList(const QString &authToken, int skip, int limit, const QString &searchText,
    //                              const QString &task_id, const QString &project_id, const QString &folder_name,
    //                              const QString &start_date, const QString &end_date, const QString &sort_by);
    bool fetchTasksForMobileList(const QString &authToken, int skip);

    //project id, title, description we will get here
    void getAllProjects(const QString &authToken);

    // creating a task using create task page
    void createTasks(const QString &authToken, const QString &title, const QString &folder_name, const QString &project_id, const bool &is_started);
    void updateTasks(const QString &authToken, const QString &title, const QString &task_id, const QString &folder_name, const QString &project_id, const bool &is_started);
    void deleteTaskApi(const QString &authToken,const QString &taskid);
    void completedTaskApi(const QString &authToken,const QString &taskid);
    void startTaskApi(const QString &authToken,const QString &taskid);
    void stopTaskApi(const QString &authToken,const QString &taskid);
    void addRemainingTimeApi(const QString &authToken, const QString &taskid, int remainingTime);

    // filtering api's
    void allTasksInSeletedFolder(const QString &authToken,const QString &folder_name, int skip, int limit);
    void allTasksInSeletedProject(const QString &authToken,const QString &project_id, int skip, int limit);
    void allTasksInSeletedSearchKeyword(const QString &authToken,const QString &searchItem, int skip, int limit);
    void allTasksInSeletedProjectAndFolder(const QString &authToken,const QString &project_id,const QString &folder_name, int skip, int limit);
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

    void onErrorStatusPopop(const int statusCode);

    void testslot();

private:
    explicit MyNetworkManager(QObject *parent = nullptr);
    MyNetworkManager(const MyNetworkManager&) = delete;
    MyNetworkManager& operator=(const MyNetworkManager&) = delete;
    static MyNetworkManager* m_instance;
};

#endif // MYNETWORKMANAGER_H
