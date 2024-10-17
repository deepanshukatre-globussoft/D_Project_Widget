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


    QString token = "0800068e6089f9913a7b17213635e548:687a325872a50fae44b3a54d5bd91764eba5a4dafa9b75499749376bcc6b462fdfb62b98ad0590ec467c0706739db03fe69e4fa8bcceb0950eed3cd120c3cf37839c0d7eaa7b252f5ca29760f25220d91c051ac17de4ca387d3b82a035fd5d394693eb2e25553a6ec30394ac473fdd6c313019fa9cef84c4907e3388f71b724c3bd93f7bdec9bb0515e14c0b4be85db96be9b85dc07958faf15897c20908619c5e5e99fcb458740290765c20fb451ad0297294e1b364207cd36f22de53a98eee092af7eab3bfd12282d98c959e2f3f5194eb4176cb7f011b1c879fb6d1c914dfa7adf33da36868498b89cec79455feb6e45763cbea82cbe15f4770d6271554170bd4281c4e7b48aedfbceea4fd3e41249a21a3201c034022395b83e7e9f5eb65";
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



    void testslot();

private:
    explicit MyNetworkManager(QObject *parent = nullptr);
    MyNetworkManager(const MyNetworkManager&) = delete;
    MyNetworkManager& operator=(const MyNetworkManager&) = delete;
    static MyNetworkManager* m_instance;
};

#endif // MYNETWORKMANAGER_H
