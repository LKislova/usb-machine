#include "mainoptions.h"

MainOptions::MainOptions(QWidget *parent)
    : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);
    setParent(parent);
    createMainLayout();
    setLayout(mainLayout);
}
void MainOptions::createMainLayout(){
    QLabel *lable = new QLabel(tr("Размерность координат станка, размеров и отступов для фрез"));

    buttonMM = new QRadioButton("Миллиметры", this);
    buttonSM = new QRadioButton("Сантиметры", this);
    buttonM = new QRadioButton("Метры", this);
    mainLayout->addWidget(lable);
    mainLayout->addWidget(buttonMM);
    mainLayout->addWidget(buttonSM);
    mainLayout->addWidget(buttonM);

 }
double MainOptions::getDimension(){
    if (buttonMM->isChecked()){
      return 1e-3;
    }
    if (buttonSM->isChecked()){
      return 1e-2;
    }
    if (buttonM->isChecked()){
      return 1;
    }
    return 0.0;
}

void MainOptions::setDimension(double d){
    if (d==1e-3){
        buttonMM->setChecked(true);
    }
    if (d==1e-2){
        buttonSM->setChecked(true);
    }
    if (d==1){
        buttonM->setChecked(true);
    }
}

