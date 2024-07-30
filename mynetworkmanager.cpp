#include "mynetworkmanager.h"
//#include "widget.h"
MyNetworkManager::MyNetworkManager(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager(this);
    connect(this,&MyNetworkManager::mytestNetworksignal,this,&MyNetworkManager::testslot);
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
                    emit mytestNetworksignal();
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
}

void MyNetworkManager::testslot()
{
    qDebug() << "testslot: " ;
}
