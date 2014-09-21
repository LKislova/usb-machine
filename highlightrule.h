#ifndef HIGHLIGHTRULE_H
#define HIGHLIGHTRULE_H

#include <QString>
#include <QTextCharFormat>

class HighlightRule : public QObject
{
public:
    HighlightRule(QString regexp, QTextCharFormat format);
    QString regexp;
    QTextCharFormat format;
};

#endif // HIGHLIGHTRULE_H
