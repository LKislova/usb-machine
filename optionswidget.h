#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QtWidgets>
#include "machineoptions.h"
#include "mainoptions.h"
class OptionsWidget : public QDialog {
    Q_OBJECT

public:
    OptionsWidget(QWidget *parent, QSettings* settings);

private:    
    QVBoxLayout* layout;

    QSettings* settings;
    QTabWidget* tabWidget;
    MainOptions *mainWidget;
    MachineOptions* machineWidget;
    QVBoxLayout* unitsLayout;
    QVBoxLayout* compileLayout;
    QVBoxLayout* mainLayout;
    QVBoxLayout* warningsLayout;
    QVBoxLayout* editorLayout;

    QHBoxLayout* buttonsLayout;
    QPushButton* ok;
    QPushButton* cancel;
    QPushButton* apply;

    QTextEdit* xAreaEdit;
    QTextEdit* yAreaEdit;
    QTextEdit* zAreaEdit;
    QTextEdit* fAreaEdit;
    QTextEdit* blankAreaEdit;
public slots:
    void readSettings();
    void writeSettings();
    void closeAndWriteSettings();
    void closeAndReadSettings();

};
#endif // OPTIONSWIDGET_H
