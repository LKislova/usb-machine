#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"
#include "customedittext.h"
#include "optionswidget.h"
#include "codehighlighter.h"
#include "searchwidget.h"
#include "compilator.h"
#include "usbconnection.h"
#include "modeling.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
    void showOptions();
    void bindCurrentText(int i);
    void closeFile(QTextDocument *doc, const QString path);
    void disconnectWidget(CustomEditText* textEdit);
    void find();
    void replace();
    void replaceAll();
    void compile();
    void onFinishCompilation();
    void onModeling();
    void runCode();
    void manualCtrl();
    void machineOff();
    void findInCurrent(QString regexp);
    void replaceInCurrent(QString regexp, QString text);
    void replaceAllInCurrent(QString regexp, QString text);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool maybeSave(QTextDocument * doc);
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    bool saveDocument(QTextDocument * doc, const QString * path);
    void setCurrentFile(const QString &fileName);
    void setCurrentFile(const QString &fileName, const QString &text);
    void bindTextActions();
    QString strippedName(const QString &fullFileName);

    MainWidget *mainWidget;
    QString curFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *compilationMenu;
    QMenu *optionsMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *findAct;
    QAction *replaceAct;
    QAction *optionsAct;
    QAction *compileAction;
    QAction *runAction;
    QAction *modelAction;
    QAction *manualCtrlAction;
    QAction *machineOffAction;
    QAction *aboutAct;
    QAction *aboutQtAct;

    Compilator* compilator;

    OptionsWidget* optionsWidget;

    CodeHighlighter* codeHighlighter;
    SearchWidget* searchwidget;
    UsbConnection* usbConnection;
    ModelingWidget* modelingWidget;
};
//! [0]

#endif
