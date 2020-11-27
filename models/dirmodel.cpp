#include "dirmodel.h"

DirModel::DirModel(QObject *parent) :
    QObject(parent),
    _current_file(QString()),
    _current_path(QDir::homePath() + QDir::separator()),
    _dir(_current_path),
    _is_current_dir(false)
{
    _dir_list.append(_dir.entryList(QDir::NoDot | QDir::Dirs));
    _dir_list.append(_dir.entryList({"*.h", "*.cpp"}, QDir::Files));
    emit dirListChanged();

    connect(this, &DirModel::currentFileChanged, this, &DirModel::checkIfCurrentIsDir);
}


void DirModel::openCurrentDir()
{
    const QString path = _current_path + _current_file;
    QFileInfo fi(_current_path);

    if (!fi.exists())
    {
        qWarning("DirModel::openCurrentDir: File: %s does not exists",
                 qUtf8Printable(path));
        return;
    }

    if (fi.isDir())
    {
        _dir.cd(_current_file);

        _dir_list.clear();
        _dir_list.append(_dir.entryList(QDir::NoDot | QDir::Dirs));
        _dir_list.append(_dir.entryList({"*.h", "*.cpp"}, QDir::Files));
        emit dirListChanged();

        _current_path = _dir.path() + QDir::separator();
        emit currentPathChanged();

        _current_file = _dir_list.at(0);
        emit currentFileChanged();

        return;
    }

    qWarning("DirModel::openCurrentDir: File: %s is not a directory",
             qUtf8Printable(path));
}


void DirModel::setCurrentFile(QString current)
{
    if (_current_file != current)
    {
        _current_file = current;
        emit currentFileChanged();
    }
}


void DirModel::checkIfCurrentIsDir()
{
    QFileInfo fi(_current_path + _current_file);
    bool is_dir = false;
    if (fi.isDir())
        is_dir = true;

    if (is_dir != _is_current_dir)
    {
        _is_current_dir = is_dir;
        emit isCurrentDirChanged();
    }
}
