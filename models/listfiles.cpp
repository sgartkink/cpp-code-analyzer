#include "listfiles.h"

#include <QFileInfo>
#include <QDirIterator>

ListFiles::ListFiles(QObject *parent) :
    QObject(parent)
{}


void ListFiles::appendNewFiles(const QString path)
{
    QFileInfo fi(path);

    if (!fi.exists())
    {
        qWarning("ListFiles::appendNewFiles: File: %s does not exists",
                 qUtf8Printable(path));
        return;
    }

    if (fi.isFile())
    {
        if (!_list_files.contains(path))
        {
            _list_files.append(path);
            emit listFilesChanged();
        }
    }
    else if (fi.isDir())
    {
        QDirIterator it {path, {"*.h", "*.cpp"}, QDir::Files, QDirIterator::Subdirectories};
        bool changed = false;

        while (it.hasNext())
        {
            QDir dir {it.next()};
            if (!_list_files.contains(dir.path()))
            {
                _list_files.append(dir.path());
                changed = true;
            }
        }

        if (changed)
            emit listFilesChanged();
    }
    else
        qWarning("ListFiles::appendNewFiles: File: %s is neither file nor dir",
                 qUtf8Printable(path));
}
