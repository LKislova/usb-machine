#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "highlightrule.h"

class CodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    CodeHighlighter(QObject *parent = 0);
    void highlightBlock(const QString &text);

private:
    struct HighlightRule {
        QString regexp;
        QTextCharFormat format;
    };

    QList<HighlightRule> rules;
    void setFormatForRegExp(const QString &text,
            const QString& regexp, const QTextCharFormat& format);

public slots:

};

#endif // CODEHIGHLIGHTER_H
