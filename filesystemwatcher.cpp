#include "filesystemwatcher.h"
#include <QDateTime>
#include <QDebug>
#include <QFile>

FileSystemWatcher::FileSystemWatcher(QObject *parent) : QObject(parent)
{
    QObject::connect(&m_FileSysWatcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::fileChanged);
    QObject::connect(&m_FileSysWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::dirChanged);
}

void FileSystemWatcher::addWatchingPath(const QString &path)
{
    m_FileSysWatcher.addPath(path);
}

void FileSystemWatcher::addWatchingFile(const QString &fileName)
{
    m_WatchingFileNames << fileName;
}

void FileSystemWatcher::fileChanged(const QString &path)
{
    if (m_FileSysWatcher.files().contains(path)){
        qInfo() << path << "modified at " << QDateTime::currentDateTime().toString();
    }
}

void FileSystemWatcher::dirChanged(const QString &path)
{
    for (auto &fileName : m_WatchingFileNames){
        QFile file(fileName);

        if (m_FileSysWatcher.directories().contains(path)){
            if (!m_FileSysWatcher.files().contains(fileName) && file.exists()){
                m_FileSysWatcher.addPath(fileName);
                qInfo() << fileName << "created at " << QDateTime::currentDateTime().toString();
            }
            if (m_FileSysWatcher.files().contains(fileName)){
                if (!file.exists()){
                    m_FileSysWatcher.removePath(fileName);
                    qInfo() << fileName << "deleted at " << QDateTime::currentDateTime().toString();
                }
            }
        }
    }
}
