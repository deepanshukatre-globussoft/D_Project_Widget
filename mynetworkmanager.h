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

class MyNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkManager(QObject *parent = nullptr);
//    void createTask(const QString &authToken, const QString &data);
    QJsonArray dataArray;

    void fetchProjectData(const QString &authToken, int skip, int limit);
private:
    QNetworkAccessManager *networkManager;
signals:
    void projectDataFetched(const QJsonArray &dataArray);
    void mytestNetworksignal();

private slots:
    void onProjectDataFetched(QNetworkReply *reply);
    void testslot();
};

#endif // MYNETWORKMANAGER_H
