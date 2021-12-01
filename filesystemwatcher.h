#pragma once

#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>

class FileSystemWatcher : public QObject
{
        Q_OBJECT
    public:
        explicit FileSystemWatcher(QObject *parent = nullptr);
        void addWatchingPath(const QString &path);
        void addWatchingFile(const QString &fileName);

    signals:

    private slots:
        void fileChanged(const QString &path);
        void directoryChanged(const QString &path);

    private:
        QStringList m_WatchingFileNames;
        QFileSystemWatcher m_FileSysWatcher;

};

