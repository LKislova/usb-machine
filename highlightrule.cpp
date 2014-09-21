#include "highlightrule.h"

HighlightRule::HighlightRule(
        QString regexp, QTextCharFormat format)
{
    this->regexp = regexp;
    this->format = format;
}
