#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QObject>
#include <QDir>

class DirModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList dirList READ dirList NOTIFY dirListChanged)
    Q_PROPERTY(QString currentFile READ currentFile WRITE setCurrentFile NOTIFY currentFileChanged)
    Q_PROPERTY(QString currentPath READ currentPath NOTIFY currentPathChanged)
    Q_PROPERTY(bool isCurrentDir READ isCurrentDir NOTIFY isCurrentDirChanged)

public:
    explicit DirModel(QObject *parent = nullptr);
    DirModel(const DirModel&) = delete;
    ~DirModel() {}

    Q_INVOKABLE void openCurrentDir();

    QStringList dirList() const { return _dir_list; }
    QString currentFile() const { return _current_file; }
    QString currentPath() const { return _current_path; }
    bool isCurrentDir() const { return _is_current_dir; }

    void setCurrentFile(QString current);

signals:
    void dirListChanged();
    void currentFileChanged();
    void currentPathChanged();
    void isCurrentDirChanged();

private slots:
    void checkIfCurrentIsDir();

private:
    QStringList _dir_list;
    QString _current_file;
    QString _current_path;
    QDir _dir;
    bool _is_current_dir;
};

#endif // DIRMODEL_H
