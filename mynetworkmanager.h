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


    QString token = "30765ca695d7dbb06b2e77101711097c:f1ab3a8a390bcacd69ad89df5d3130a77e5de779babc6102c9f616eac600cc460237644a69bde909f69ffa23de44c363d68c8d2ef3d7dbd4d7e3c2b639b687e70ae644f8007a40066669b1fd1f615aa786d3abbcafae05bdb0b536194216d0675d4499929b2f1a56578c23dc017e21408011cf3de8d672e2b5055aa4dfd87437146b3246cf2a2aedf4e7ff0db663ed33bfefcdb6878fd95cf225c70154cb07aab869cc51f585654b1004197f222723259cf660f765b2dc9fe0ba96b5486672f77af419d6bc87b3abba776827143c4e59b9e1a1aefdae758fe0cce534c67fdee39774a071aec4047e7619d449d71e86598335e4c3288b5b43701a6457491751523cc32eacac9d851b05d16a6eade16d3c34552b08b5a9d6531739aa66d47dce94";
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
