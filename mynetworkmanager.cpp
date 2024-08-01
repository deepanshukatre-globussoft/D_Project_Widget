#include "mynetworkmanager.h"
//#include "widget.h"


MyNetworkManager* MyNetworkManager::m_instance = nullptr;

MyNetworkManager::MyNetworkManager(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager();
//    connect(this,&MyNetworkManager::mytestNetworksignal,this,&MyNetworkManager::testslot);
}


MyNetworkManager *MyNetworkManager::instance()
{
    if (m_instance == nullptr) {
        m_instance = new MyNetworkManager();
    }
    return m_instance;
}

void MyNetworkManager::fetchProjectData(const QString &authToken, int skip, int limit)
{
    QUrl url("https://service.dev.empmonitor.com/api/v3/mobile/admin-dashboard/fetch-project-mobile");
    QUrlQuery query;
    query.addQueryItem("skip", QString::number(skip));
    query.addQueryItem("limit", QString::number(limit));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply,this](){
        MyNetworkManager::onProjectDataFetched(reply);
    });
    connect(reply, &QNetworkReply::sslErrors, this, [](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            qDebug() << "SSL error:" << error.errorString();
        }
    });
    qDebug() << "network class object "<<this;
}

void MyNetworkManager::fetchTasksForMobileList(const QString &authToken, int skip, int limit, const QString &searchText, const QString &task_id, const QString &project_id, const QString &folder_name, const QString &start_date, const QString &end_date, const QString &sort_by)
{
    QUrl url("https://service.dev.empmonitor.com/api/v3/mobile/admin-dashboard/fetch-project-task-mobile-list");

    QUrlQuery query;
    query.addQueryItem("skip", QString::number(skip));
    query.addQueryItem("limit", QString::number(limit));
    query.addQueryItem("search", searchText);
    query.addQueryItem("task_id", task_id);
    query.addQueryItem("project_id", project_id);
    query.addQueryItem("folder_name", folder_name);
    query.addQueryItem("start_date", start_date);
    query.addQueryItem("end_date", end_date);
    query.addQueryItem("sort_by", sort_by);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply](){
        qDebug()<<reply->readAll();
    });
}

bool MyNetworkManager::fetchTasksForMobileList(const QString &authToken, int skip)
{
    QUrl url("https://service.dev.empmonitor.com/api/v3/mobile/admin-dashboard/fetch-project-task-mobile-list");

    QUrlQuery query;
    query.addQueryItem("skip", QString::number(skip));
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        MyNetworkManager::onTasksDataFetched(reply);
//        qDebug()<<reply->readAll();
    });
    return true;
}


void MyNetworkManager::onProjectDataFetched(QNetworkReply *reply)
{
//    qDebug()<<"fetch data successful " << reply;
//    reply->deleteLater();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj.contains("data") && jsonObj["data"].isArray()) {
             dataArray = jsonObj["data"].toArray();

            for (const QJsonValue &value : dataArray) {
                if (value.isObject()) {
                    QJsonObject projectObj = value.toObject();
                    QString id = projectObj["_id"].toString();
                    QString title = projectObj["title"].toString();
                    QString description = projectObj["description"].toString();
                    QString startDate = projectObj["start_date"].toString();
                    QString endDate = projectObj["end_date"].toString();

//                    qDebug()<<projectObj;
                emit projectDataFetched(dataArray);
                    qDebug()<<"object get and emit signal";
//                    ProjectMainLayout

//                    emit customWidgetProject1->sendData("Status: In Progress", "Project Alpha", "Task 1", "01:23:45");
                    qDebug()<<id;
//                    qDebug()<<title;
//                    qDebug()<<description;
//                    qDebug()<<startDate;
//                    qDebug()<<endDate;

//                    displayText.append("ID: " + id + "\n");
//                    displayText.append("Title: " + title + "\n");
//                    displayText.append("Description: " + description + "\n");
//                    displayText.append("Start Date: " + startDate + "\n");
//                    displayText.append("End Date: " + endDate + "\n\n");
                }
            }

//            textEdit->setText(displayText);
        } else {
//            textEdit->setText("No project data found.");
        }
    } else {
        qDebug() << "Error: " << reply->errorString();
//        textEdit->setText("Failed to fetch data: " + reply->errorString());
    }
//        reply->deleteLater();
}

void MyNetworkManager::onTasksDataFetched(QNetworkReply *reply)
{

    emit deleteConfigurationsignal();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj.contains("data") && jsonObj["data"].isArray()) {
            dataArray = jsonObj["data"].toArray();

            for (const QJsonValue &value : dataArray) {
                if (value.isObject()) {
                    QJsonObject taskObject = value.toObject();
                    QString id = taskObject["_id"].toString();
                    QString title = taskObject["name"].toString();
                    QJsonObject folderObject = taskObject["folder_data"].toObject();
                    QString folderName = folderObject["name"].toString();
                    QJsonObject project_data_Obj = taskObject["project_data"].toObject();
                    QString projectTitle = project_data_Obj["title"].toString();

                    //                    qDebug()<<projectObj;
                    emit taskDataFetched(id,title,folderName,projectTitle);
                    qDebug()<<"onTasksDataFetched emiting taskDataFetched signal";

                    //                    emit customWidgetProject1->sendData("Status: In Progress", "Project Alpha", "Task 1", "01:23:45");
//                    qDebug()<<id;

                }
            }
        } else {

        }
    } else {
        qDebug() << "Error: " << reply->errorString();
    }
    //    reply->deleteLater();

    emit initConfigurationsignal();
}

void MyNetworkManager::testslot()
{
    qDebug() << "testslot: " ;

}
