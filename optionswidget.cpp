#include "optionswidget.h"

OptionsWidget::OptionsWidget(QWidget *parent, QSettings * settings)
        : QDialog(parent){
    setParent(parent);
    this->settings = settings;

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));
    apply = new QPushButton(tr("Apply"));
    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(ok);
    buttonsLayout->addSpacing(0);
    buttonsLayout->addWidget(apply);
    buttonsLayout->addSpacing(0);
    buttonsLayout->addWidget(cancel);
    buttonsLayout->addSpacing(0);
    connect(apply, SIGNAL(clicked()),this,SLOT(writeSettings()));
    connect(ok, SIGNAL(clicked()),this,SLOT(closeAndWriteSettings()));
    connect(cancel, SIGNAL(clicked()),this,SLOT(closeAndReadSettings()));

    /*

    mainLayout = new QVBoxLayout(this);
    editorLayout = new QVBoxLayout(this);
    unitsLayout = new QVBoxLayout(this);
    compileLayout = new QVBoxLayout(this);
    warningsLayout = new QVBoxLayout(this);

    createMachineLayout();


    editorLayout->addLayout(buttonsLayout);
    unitsLayout->addLayout(buttonsLayout);
    compileLayout->addLayout(buttonsLayout);
    warningsLayout->addLayout(buttonsLayout);
    machineLayout->addLayout(buttonsLayout);*/

    machineWidget = new MachineOptions(this);
    mainWidget= new MainOptions(this);
    tabWidget = new QTabWidget(this);
 
    //tabWidget->addTab(editorLayout, tr("Редактор"));
    tabWidget->addTab(machineWidget, tr("Станок"));
    tabWidget->addTab(mainWidget, tr("Основное"));
    //tabWidget->addTab(compileLayout, tr("Компиляция"));
    //tabWidget->addTab(warningsLayout, tr("Аварийные"));
    layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->addLayout(buttonsLayout);
    setLayout(layout);
    readSettings();

    setWindowTitle(tr("Настройки"));
}
void OptionsWidget::readSettings() {
    double dim = settings->value("dimension", 1).toDouble();
    double xArae = settings->value("x_arae", 1).toDouble();
    double yArae = settings->value("y_arae", 1).toDouble();
    double zArae = settings->value("z_arae", 1).toDouble();
    double fArae = settings->value("f_arae", 1).toDouble();
    double blankArae = settings->value("blank_arae", 1).toDouble();

    mainWidget->setDimension(dim);
    machineWidget->setXArea(xArae);
    machineWidget->setYArea(yArae);
    machineWidget->setZArea(zArae);
    machineWidget->setFArea(fArae);
    machineWidget->setBlankArea(blankArae);
}

void OptionsWidget::closeAndWriteSettings() {
    writeSettings();
    hide();
}

void OptionsWidget::closeAndReadSettings() {
    readSettings();
    hide();
}

void OptionsWidget::writeSettings() {
    settings->setValue("dimension", mainWidget->getDimension());

    settings->setValue("x_arae", machineWidget->getXArea());
    settings->setValue("y_arae", machineWidget->getYArea());
    settings->setValue("z_arae", machineWidget->getZArea());
    settings->setValue("f_arae", machineWidget->getFArea());
    settings->setValue("blank_arae", machineWidget->getBlankArea());
}
