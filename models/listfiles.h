#ifndef LISTFILES_H
#define LISTFILES_H

#include <QObject>

class ListFiles : public QObject
{
    Q_OBJECT

    Q_PROPERTY (QStringList listFiles READ listFiles NOTIFY listFilesChanged)

public:
    explicit ListFiles(QObject *parent = nullptr);

    Q_INVOKABLE void appendNewFiles(const QString path);

    QStringList listFiles() const { return _list_files; }

signals:
    void listFilesChanged();

private:
    QStringList _list_files;

};

#endif // LISTFILES_H
