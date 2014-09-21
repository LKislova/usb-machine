#include "machineoptions.h"

MachineOptions::MachineOptions(QWidget *parent) :
        QWidget(parent) {
    machineLayout = new QVBoxLayout(this);

    setParent(parent);
    createMachineLayout();
    setLayout(machineLayout);
}

void MachineOptions::createMachineLayout() {
    QLabel *xlable = new QLabel(tr("Длина рабочей зоны по оси X"));
    QLabel *ylable = new QLabel(tr("Длина рабочей зоны по оси Y"));
    QLabel *zlable = new QLabel(tr("Длина рабочей зоны по оси Z"));
    QLabel *flable = new QLabel(tr("Радиус поворота вокруг оси F"));
    QLabel *blankLable = new QLabel(tr("Максимальный размер заготовки"));

    xAreaEdit = new QLineEdit();
    yAreaEdit = new QLineEdit();
    zAreaEdit = new QLineEdit();
    fAreaEdit = new QLineEdit();
    blankAreaEdit = new QLineEdit();
    xChildLay = new QHBoxLayout();
    yChildLay = new QHBoxLayout();
    zChildLay = new QHBoxLayout();
    fChildLay = new QHBoxLayout();
    blankChildLay = new QHBoxLayout();

    makeTempLayout(xChildLay, xlable, xAreaEdit, machineLayout);
    makeTempLayout(yChildLay, ylable, yAreaEdit, machineLayout);
    makeTempLayout(zChildLay, zlable, zAreaEdit, machineLayout);
    makeTempLayout(fChildLay, flable, fAreaEdit, machineLayout);
    makeTempLayout(blankChildLay, blankLable, blankAreaEdit, machineLayout);
}

void MachineOptions::makeTempLayout(QHBoxLayout *child,
        QLabel *lable, QLineEdit* edit, QBoxLayout* parent) {
    edit->setValidator(new QDoubleValidator());

    child->addSpacing(1);
    child->addWidget(lable);
    child->addSpacing(1);
    child->addWidget(edit);
    child->addSpacing(1);

    parent->addLayout(child);
}

double MachineOptions::getXArea(){
    return xAreaEdit->text().toDouble();
}
double MachineOptions::getYArea(){
    return yAreaEdit->text().toDouble();
}
double MachineOptions::getZArea(){
    return zAreaEdit->text().toDouble();
}
double MachineOptions::getFArea(){
    return fAreaEdit->text().toDouble();
}
double MachineOptions::getBlankArea(){
    return blankAreaEdit->text().toDouble();
}

void MachineOptions::setXArea(double x){
    xAreaEdit->setText(tr("%1").arg(x));
}
void MachineOptions::setYArea(double y){
    yAreaEdit->setText(tr("%1").arg(y));
}
void MachineOptions::setZArea(double z){
    zAreaEdit->setText(tr("%1").arg(z));
}
void MachineOptions::setFArea(double f){
    fAreaEdit->setText(tr("%1").arg(f));
}
void MachineOptions::setBlankArea(double blank){
    blankAreaEdit->setText(tr("%1").arg(blank));
}
