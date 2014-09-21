#include "modeling.h"

ModelingWidget::ModelingWidget() : QWidget(){
    mainLayout = new QHBoxLayout();
    controlsLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *beatyButtonLayout = new QVBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addLayout(beatyButtonLayout);
    buttonLayout->addStretch(1);
    projectionWidget = new QLineEdit(tr("xyz"));
    replotButton = new QPushButton(tr("Установить проекцию"));

    okButton = new QPushButton(tr("OK"));

    beatyButtonLayout->addWidget(replotButton);
    beatyButtonLayout->addWidget(okButton);
    plotWidget = new Jenia();

    mainLayout->addWidget(plotWidget, 1);
    mainLayout->addLayout(controlsLayout);

    controlsLayout->addWidget(projectionWidget);
    controlsLayout->addLayout(buttonLayout);
    controlsLayout->addStretch(1);
    setLayout(mainLayout);
    connect(okButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(replotButton, SIGNAL(clicked()), this, SLOT(changeProjection()));

    setWindowTitle(tr("Моделирование трактории движения"));
}

void ModelingWidget::plotLine(lines_t* line) {
    this->line = line;

    changeProjection();
}

void ModelingWidget::changeProjection() {

    track = new Track(line, projectionWidget->text(), *plotWidget);
    track->setMesh(100, 3);
    track->setDomain(0.0, line->size() - 1, 0.0, 1.0);
    track->create();

    plotWidget->updateProjection(track->getX1(), track->getY1(), track->getZ1());

    plotWidget->updateLine();
}
