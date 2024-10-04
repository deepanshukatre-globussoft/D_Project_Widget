#ifndef TASKMODELCLASS_H
#define TASKMODELCLASS_H

#include <QObject>

class TaskModelClass : public QObject
{
    Q_OBJECT
public:
    explicit TaskModelClass(QObject *parent = nullptr);

    explicit TaskModelClass(const QString &taskid, int taskStatus, const QString &taskName,
                            const QString &taskFolderId, const QString &taskFolderName,
                            const QString &taskProjectId, const QString &taskProjectName,
                            QObject *parent = nullptr) ;

    explicit TaskModelClass(const QString &taskid, int taskStatus, const QString &taskName,
                            const QString &m_taskActiveTime, const QString &m_taskRemainingTime,
                            const QString &taskFolderName,const QString &taskProjectId, const QString &m_taskFinishedTime, const QString &taskProjectName,
                            QObject *parent = nullptr) ;

    QString m_taskid;
    int m_taskStatus;
    QString m_taskName;
    QString m_taskActiveTime;
    QString m_taskRemainingTime;
    QString m_taskFinishedTime;
    QString m_taskFolderName;
    QString m_taskProjectId;
    QString m_taskProjectName;

signals:


private:


};

#endif // TASKMODELCLASS_H
