#include "customedittext.h"

CustomEditText::CustomEditText(QWidget * parent)
        : QPlainTextEdit(parent){
    setParent(parent);
    cutAction = new QAction(tr("Выре&зать"), this);
    cutAction->setShortcuts(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    connect(this, SIGNAL(copyAvailable(bool)),
            cutAction, SLOT(setEnabled(bool)));
    cutAction->setEnabled(false);

    copyAction = new QAction(tr("&Копировать"), this);
    copyAction->setShortcuts(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    connect(this, SIGNAL(copyAvailable(bool)),
            copyAction, SLOT(setEnabled(bool)));
    copyAction->setEnabled(false);

    pasteAction = new QAction(tr("&Вставить"), this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
}

QAction * CustomEditText::getCutAction(){
    return this->cutAction;
}

QAction * CustomEditText::getCopyAction(){
    return this->copyAction;
}

QAction * CustomEditText::getPasteAction(){
    return this->pasteAction;
}
