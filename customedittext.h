#ifndef CUSTOMEDITTEXT_H
#define CUSTOMEDITTEXT_H

#include "QtWidgets"

class CustomEditText : public QPlainTextEdit {
public:
    CustomEditText(QWidget* parent);
    QAction* getCutAction();
    QAction* getCopyAction();
    QAction* getPasteAction();

private:
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;

};

#endif // CUSTOMEDITTEXT_H
