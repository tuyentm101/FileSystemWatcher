#include <QCoreApplication>
#include "filesystemwatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileSystemWatcher fileSysWatcher;

    fileSysWatcher.addWatchingPath(QDir::currentPath());
    fileSysWatcher.addWatchingFile(QDir::currentPath() + QDir::separator() + "abc.txt");
    fileSysWatcher.addWatchingFile(QDir::currentPath() + QDir::separator() + "test.txt");

    return a.exec();
}
