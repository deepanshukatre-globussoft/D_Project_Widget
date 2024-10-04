#include "taskmodelclass.h"

#include "qdebug.h"
TaskModelClass::TaskModelClass(QObject *parent)
    : QObject{parent}
{

}

TaskModelClass::TaskModelClass(const QString &taskid, int taskStatus, const QString &taskName,
                                   const QString &m_taskActiveTime, const QString &taskFolderName,
                                   const QString &taskProjectId, const QString &taskProjectName, QObject *parent)
    : QObject(parent),
    m_taskid(taskid),
    m_taskStatus(taskStatus),
    m_taskName(taskName),
    m_taskActiveTime(m_taskActiveTime),
    m_taskFolderName(taskFolderName),
    m_taskProjectId(taskProjectId),
    m_taskProjectName(taskProjectName)
{
//    qDebug()<<"****** ";
//    qDebug() << "TaskModelClass created with values:";
//    qDebug() << "Task ID:" << m_taskid;
//    qDebug() << "Task Status:" << m_taskStatus;
//    qDebug() << "Task Name:" << m_taskName;
//    qDebug() << "Task Folder ID:" << m_taskFolderId;
//    qDebug() << "Task Folder Name:" << m_taskFolderName;
//    qDebug() << "Task Project ID:" << m_taskProjectId;
//    qDebug() << "Task Project Name:" << m_taskProjectName;

}

TaskModelClass::TaskModelClass(const QString &taskid, int taskStatus, const QString &taskName,
                               const QString &m_taskActiveTime, const QString &m_taskRemainingTime,
                               const QString &taskFolderName, const QString &taskProjectId,const QString &m_taskFinishedTime,
                               const QString &taskProjectName, QObject *parent):
    QObject(parent),
    m_taskid(taskid),m_taskStatus(taskStatus),
    m_taskName(taskName),m_taskActiveTime(m_taskActiveTime),
    m_taskRemainingTime(m_taskRemainingTime),m_taskFinishedTime(m_taskFinishedTime),
    m_taskFolderName(taskFolderName),m_taskProjectId(taskProjectId),
    m_taskProjectName(taskProjectName)
{

}
