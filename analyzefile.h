#ifndef ANALYZEFILE_H
#define ANALYZEFILE_H

#include <QString>
#include <QFile>

class AnalyzeFile
{
public:
    AnalyzeFile();

    void start_analyzing_file(const QString path);

    unsigned lines() const { return _lines; }
    unsigned lines_no_empty() const { return _lines_no_empty; }
    unsigned lines_no_comments() { return _lines_no_comments; }

private:
    void try_to_open_file();
    void analyze_file();
    bool check_if_starts_comment();

    bool _in_multiline_comment;

    unsigned _lines;
    unsigned _lines_no_empty;
    unsigned _lines_no_comments;

    QFile _file;
    QString _line;
};

#endif // ANALYZEFILE_H
