#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "QtWidgets"
#include "QRegExp"
#include "customedittext.h"
#include "DEF.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget * parent);
    CustomEditText* getTextEdit();
    QString getCurrentPath();
    CustomEditText* setCurrentTabName(const QString &name);
    CustomEditText* newTab(const QString &name);
    CustomEditText* newTab(const QString &name, const QString &contant);
    void clearTables();
    void addLine(line_t *line);

private:
    QVBoxLayout * mainLayout;
    QTabWidget * tabWidget;
    QAction * tabAction;
    QSplitter * mainSplitter;
    QSplitter * supportSplitter;
    QList<QString> pathesList;
    QTableWidget* mainVarTable;
    QTableWidget* varTable;

    QString incrementCounterInFileName(const QString &name);
    void createMainVarTable();
    void createVarTable();

public slots:
    void closeTabSlot(QString index);
    void closeTab(int index);
    void disconnectWidgets(int index);

signals:
    void currentChanged(int);
    void disconnectActionsFrom(CustomEditText*);
    void wantToClose(QTextDocument*, QString);
};

#endif // MAINWIDGET_H
