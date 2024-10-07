#include "mynetworkmanager.h"
//#include "widget.h"


MyNetworkManager* MyNetworkManager::m_instance = nullptr;

MyNetworkManager::MyNetworkManager(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager();
    //    connect(this,&MyNetworkManager::deleteConfigurationsignal,this,&MyNetworkManager::testslot);

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
    //    QUrl url("https://service.dev.empmonitor.com/api/v3/mobile/admin-dashboard/fetch-project-mobile");

    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-task");
    qDebug()<<"fetchTasksForMobileList";
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
    //    QUrl url("https://service.dev.empmonitor.com/api/v3/mobile/admin-dashboard/fetch-project-task-mobile-list");

    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-task");

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
    //    QUrl url("https://service.dev.empmonitor.com/api/v3/mobile/admin-dashboard/fetch-project-task-mobile-list");
    qDebug()<<"fetchTasksForMobileList ++++++++++++++";
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-task-silah");

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

void MyNetworkManager::getAllProjects(const QString &authToken)  // this is used to show data in the all projects combobox
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-silah"); // to get all projects details not tasks
    QUrlQuery query;
    query.addQueryItem("skip", QString::number(0));
    query.addQueryItem("limit", QString::number(10));
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        //        qDebug()<<"getAllProjects finished the request "<<reply->readAll(); // never try to read data twice
        MyNetworkManager::onProjectIdAndNameDataFetched(reply);
    });
}

void MyNetworkManager::createTasks(const QString &authToken, const QString &title, const QString &folder_name, const QString &project_id)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/create-project-tasks");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // Set content type to JSON

    QJsonObject json;
    json["title"] = title;
    json["folder_name"] = folder_name;
    json["project_id"] = project_id;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->post(request,jsonData);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
//        qDebug()<<"getAllProjects finished the request "<<reply->readAll(); // never try to read data twice
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("message")) {
                QString message = jsonObj["message"].toString();
                qDebug() << "Message from API response:" << message;

                QMessageBox::information(nullptr, "Silah TTS", message);
            }else{
                qDebug()<<"data is not in array of not contains array";
                QMessageBox::information(nullptr, "Silah TTS", "Something went wrong");
            }
            this->fetchTasksForMobileList(token,10); // this will reload all tasks after start
        }else{
            qDebug() << "Error for delete task: " << reply->errorString();
            QMessageBox::information(nullptr, "Silah TTS", "Something went wrong "+ reply->errorString());
        }
    });
}

void MyNetworkManager::deleteTaskApi(const QString &authToken, const QString &taskid)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/delete-project-task");
    QUrlQuery query;
    query.addQueryItem("_id", taskid);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // Set content type to JSON

    QNetworkReply *reply = networkManager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        //        qDebug()<<"deleteTaskApi finished the request "<<reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("message")) {
                QString message = jsonObj["message"].toString();
                qDebug() << "Message from API response:" << message;

                // Now you can use the message value, for example in a QMessageBox:
                QMessageBox::information(nullptr, "Silah TTS", message);

            }else{
                qDebug()<<"data is not in array of not contains array";
                QMessageBox::information(nullptr, "Silah TTS", "Something went wrong");
            }

            this->fetchTasksForMobileList(token,10); // this will reload all tasks after delete successfull
        }else{
            qDebug() << "Error for delete task: " << reply->errorString();
            QMessageBox::information(nullptr, "Silah TTS", "Something went wrong "+ reply->errorString());
            this->fetchTasksForMobileList(token,10); // this will reload all tasks after delete unsuccessfull
        }

    });
}

void MyNetworkManager::completedTaskApi(const QString &authToken, const QString &taskid)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/finish-project-task");
    QUrlQuery query;
    query.addQueryItem("task_id", taskid);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // Set content type to JSON

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        //        qDebug()<<"deleteTaskApi finished the request "<<reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("message")) {
                QString message = jsonObj["message"].toString();
                qDebug() << "Message from API response:" << message;
                QMessageBox::information(nullptr, "Silah TTS", message);

            }else{
                qDebug()<<"data is not in array of not contains array";
                QMessageBox::information(nullptr, "Silah TTS", "Something went wrong");
            }

            this->fetchTasksForMobileList(token,10); // this will reload all tasks after complete successfull
        }else{
            qDebug() << "Error for complete task: " << reply->errorString();
            QMessageBox::information(nullptr, "Silah TTS", "Something went wrong "+ reply->errorString());
            this->fetchTasksForMobileList(token,10); // this will reload all tasks after complete unsuccessfull
        }

    });

}

void MyNetworkManager::startTaskApi(const QString &authToken, const QString &taskid)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/start-project-task");
    QUrlQuery query;
    query.addQueryItem("task_id", taskid);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // Set content type to JSON

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        //        qDebug()<<"deleteTaskApi finished the request "<<reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("message")) {
                QString message = jsonObj["message"].toString();
                qDebug() << "Message from API response:" << message;
                QMessageBox::information(nullptr, "Silah TTS", message);

                emit taskStartDataSignal("taskid",true,"00:00:00");
            }else{
                qDebug()<<"data is not in array of not contains array";
                QMessageBox::information(nullptr, "Silah TTS", "Something went wrong");
                emit taskStartDataSignal("taskid",false,"00:00:00");
            }
            this->fetchTasksForMobileList(token,10); // this will reload all tasks after start
        }else{
            qDebug() << "Error for complete task: " << reply->errorString();
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("message")) {
                QString message = jsonObj["message"].toString();
                qDebug() << "Message from API response:" << message;
                QMessageBox::information(nullptr, "Silah TTS", message);
            }else{
                QMessageBox::information(nullptr, "Silah TTS", "Something went wrong "+ reply->errorString()+ "++ "+ reply->error());
            }
//            this->fetchTasksForMobileList(token,10); // this will reload all tasks after start failed
            emit taskStartDataSignal("taskid",false,"00:00:00");
        }
    });
}

void MyNetworkManager::stopTaskApi(const QString &authToken, const QString &taskid)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/stop-project-task");
    QUrlQuery query;
    query.addQueryItem("task_id", taskid);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // Set content type to JSON

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        //        qDebug()<<"deleteTaskApi finished the request "<<reply->readAll();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("message")) {
                QString message = jsonObj["message"].toString();
                qDebug() << "Message from API response:" << message;
                QMessageBox::information(nullptr, "Silah TTS", message);

            }else{
                qDebug()<<"data is not in array of not contains array";
                QMessageBox::information(nullptr, "Silah TTS", "Something went wrong");
            }

            this->fetchTasksForMobileList(token,10); // this will reload all tasks after stop api
        }else{
            qDebug() << "Error for complete task: " << reply->errorString();
            QMessageBox::information(nullptr, "Silah TTS", "Something went wrong "+ reply->errorString());
            this->fetchTasksForMobileList(token,10); // this will reload all tasks after stop api unuccessfull
        }

    });
}

void MyNetworkManager::allTasksInSeletedFolder(const QString &authToken, const QString &folder_name, int skip, int limit)
{

    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-task-silah");

    QUrlQuery query;
    query.addQueryItem("skip", QString::number(skip));
    query.addQueryItem("limit", QString::number(limit));
    query.addQueryItem("folder_name", folder_name);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        MyNetworkManager::onTasksDataFetched(reply);
    });
}

void MyNetworkManager::allTasksInSeletedProject(const QString &authToken, const QString &project_id, int skip, int limit)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-task-silah");

    QUrlQuery query;
    query.addQueryItem("skip", QString::number(skip));
    query.addQueryItem("limit", QString::number(limit));
    query.addQueryItem("project_id", project_id);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        MyNetworkManager::onTasksDataFetched(reply);
    });
}

void MyNetworkManager::allTasksInSeletedSearchKeyword(const QString &authToken, const QString &searchItem, int skip, int limit)
{
    QUrl url("https://track.dev.empmonitor.com/api/v3/project/get-project-task-silah");

    QUrlQuery query;
    query.addQueryItem("skip", QString::number(skip));
    query.addQueryItem("limit", QString::number(limit));
    query.addQueryItem("search", searchItem);
    url.setQuery(query);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        MyNetworkManager::onTasksDataFetched(reply);
        //        qDebug()<<reply->readAll();
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

                    //                    qDebug()<<projectObj;
                    emit projectDataFetched(dataArray);
                    qDebug()<<"object get and emit signal";
                    //                    ProjectMainLayout

                    //                    emit customWidgetProject1->sendData("Status: In Progress", "Project Alpha", "Task 1", "01:23:45");
                    qDebug()<<id;

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
//    reply->deleteLater();   // need to check
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

            emit sendingTasksFromAPIdataSignal(dataArray); //  to set data in model class list  indirectly for model

            emit taskDataFetched(1);// to set the widgetes with data indirectly for UI
            //            for (const QJsonValue &value : dataArray) {
            //                if (value.isObject()) {
            //                    QJsonObject taskObject = value.toObject();
            //                    QString id = taskObject["_id"].toString();
            //                    QString title = taskObject["name"].toString();
            //                    QJsonObject folderObject = taskObject["folder_data"].toObject();
            //                    QString folderName = folderObject["name"].toString();
            //                    QJsonObject project_data_Obj = taskObject["project_data"].toObject();
            //                    QString projectTitle = project_data_Obj["title"].toString();

            //                    //                    qDebug()<<projectObj;
            //                    qDebug()<<"onTasksDataFetched emiting taskDataFetched signal";

            //                    //                    emit customWidgetProject1->sendData("Status: In Progress", "Project Alpha", "Task 1", "01:23:45");
            ////                    qDebug()<<id;

            //                }
            //            }
        } else {

        }
    } else {
        qDebug() << "Error: " << reply->errorString();
    }
    reply->deleteLater();

    emit initConfigurationsignal();
}

void MyNetworkManager::onProjectIdAndNameDataFetched(QNetworkReply *reply) //work on reply from get all project api
{
    //    qDebug()<<"reply from get all project ++++ "<<reply->readAll();
    if(reply->error() == QNetworkReply::NoError){
        //        QJsonArray dataArray;
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();
        if (jsonObj.contains("data") && jsonObj["data"].isArray()) {
//            qDebug()<<"emitting the signal"<<response;
            dataArray = jsonObj["data"].toArray();
            emit dataSenderToComboBoxProjectList(dataArray);
            //            qDebug()<<"reply from get all project "<<dataArray;
        }
    }else {
        qDebug() << "Error: " << reply->errorString();
    }
    reply->deleteLater();
}

void MyNetworkManager::testslot()
{
    qDebug() << "testslot: " ;

}
