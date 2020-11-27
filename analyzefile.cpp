#include "analyzefile.h"

#include <QIODevice>
#include <QTextStream>
#include <QtDebug>
AnalyzeFile::AnalyzeFile() :
    _in_multiline_comment(false),
    _lines(0),
    _lines_no_empty(0),
    _lines_no_comments(0)
{}


void AnalyzeFile::start_analyzing_file(const QString path)
{
    _file.setFileName(path);
    try_to_open_file();
}


void AnalyzeFile::try_to_open_file()
{
    if (_file.open(QIODevice::ReadOnly))
        analyze_file();
    else
    {
        qWarning("AnalyzeFile::try_to_open_file: Could not open file: %s",
                 qUtf8Printable(_file.fileName()));
        return;
    }
}


void AnalyzeFile::analyze_file()
{
    QTextStream in(&_file);
    while (!in.atEnd())
    {
        _line = in.readLine();
        _line = _line.simplified();

        _lines++;

        if (_line.length() > 0)
            _lines_no_empty++;
        else
            continue;

        if (!check_if_starts_comment())
            _lines_no_comments++;

        if (_in_multiline_comment)
            continue;

        if (check_if_include())
            continue;
    }

    qDebug("AnalyzeFile::analyze_file: Finished analyzing file: %s",
           qUtf8Printable(_file.fileName()));
}


bool AnalyzeFile::check_if_starts_comment()
{
    if (_in_multiline_comment)
    {
        if (_line.indexOf("*/") == -1)
            return true;
        else if (_line.indexOf("*/") != -1 && _line.indexOf("*/") == _line.size() - 2)
        {
            _in_multiline_comment = false;
            return true;
        }
        else
        {
            _line = _line.right(_line.size() - _line.indexOf("*/") - 2);
            _line = _line.simplified();
            _in_multiline_comment = false;
            return false;
        }
    }
    else
    {
        if (_line.size() < 2)
            return false;

        if (_line.indexOf("//") == 0)
            return true;
        else if (_line.indexOf("/*") == 0)
        {
            _in_multiline_comment = true;
            return true;
        }

       return false;
    }
}


bool AnalyzeFile::check_if_include()
{
    if (_line.indexOf("#include") == 0)
    {
        _line = _line.mid(8);
        _line.replace("<", "");
        _line.replace(">", "");
        _line.replace("\"", "");
        _line = _line.simplified();
        _includes.append(_line);
        return true;
    }

    return false;
}
