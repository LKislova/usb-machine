#include "codehighlighter.h"

CodeHighlighter::CodeHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
    /*
    QString digit("\b[\d]+\b");
    QString var("\b([a-eg-rt-wA-EG-RT-W]{1}\w*)\b");
    QString mainVar("X-ZFSx-zfs");
    */
    HighlightRule constant;
    HighlightRule digit;
    HighlightRule var;
    HighlightRule mainVar;
    HighlightRule comment;
    HighlightRule function;

    digit.format.setForeground(Qt::blue);
    constant.format.setForeground(Qt::darkBlue);
    var.format.setForeground(Qt::darkGreen);
    function.format.setForeground(Qt::magenta);
    //var.format.setFontWeight(QFont::Bold);

    mainVar.format.setForeground(Qt::darkRed);
    mainVar.format.setFontWeight(QFont::Bold);

    comment.format.setForeground(Qt::green);

    constant.regexp = tr("pi|e");
    digit.regexp = tr("\\b[\\d]+\\b");
    var.regexp = tr("\\b([a-eg-rt-wA-EG-RT-W_]{1}[\\w_]*|[a-zA-Z_]{1}[\\w_]+)\\b");
    mainVar.regexp = tr("\\b[fsx-zFSX-Z]{1}\\b");
    comment.regexp = tr("\\s*(;.*)\\b");
    function.regexp = tr("(sin)|(cos)|(tan)|(asin)|(acos)|(atan)|(log)|(log10)"
                         "|(exp)|(sinh)|(cosh)|(tanh)|(asinh)|(acosh)|(atanh)"
                         "|(fasb)|(sqrt)|(pow)");

    rules << digit << constant << var << mainVar << comment << function;
}

void CodeHighlighter::highlightBlock(const QString &text) {
    foreach (HighlightRule i, rules) {
        setFormatForRegExp(text, i.regexp, i.format);
    }
}

void CodeHighlighter::setFormatForRegExp(const QString &text,
        const QString& regexp, const QTextCharFormat& format) {
    QRegExp expression(regexp);
    int index = expression.indexIn(text);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, format);
        index = expression.indexIn(text, index + length);
    }
}
