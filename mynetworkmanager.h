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

    QString token = "bba0d6557e361414a6f82a0884dab45c:2be8310172b1513985e41a017c3123ed68a93e89391044afc609e53c65b148e3f6da64eb50086625f13a49733078cfc0bc255a85a73449dde480f989ae0b930bed37978b04e759827ec0e06fdd348afacfe1c5ca00ad68f4d615a4b7098a61d430cb0649ace78eb94e797ea3a8b31ce45595191f3aa725c97daccc3467455950cde682c68a7f48ef9db4cbb6d6d8dd8ce9508561dd818e1e2281101830936f2fe73838246f37e875e2a234e765404f00734881d57d14e0caec3346a6a8dd274824ffa6ec4f88c61656299f785c9d9feb9a6ea479e130c38aced99e43975863a895ff07489d5b86079b6dd3095aa02f7f265085643e74639e0de69c0a10b033e74a74cd2ea3714b4ca0ac1af99992442fdf8acc78f02d0b0246f83f24cbcd09e3";

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
    void updateTasks(const QString &authToken,const QString &title,const QString &task_id,const QString &folder_name,const QString &project_id);
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



    void testslot();

private:
    explicit MyNetworkManager(QObject *parent = nullptr);
    MyNetworkManager(const MyNetworkManager&) = delete;
    MyNetworkManager& operator=(const MyNetworkManager&) = delete;
    static MyNetworkManager* m_instance;
};

#endif // MYNETWORKMANAGER_H
