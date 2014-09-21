#ifndef MODELING_H
#define MODELING_H

#include <QtWidgets>
#include "jenia.h"
#include "parsertypes.h"
#include "track.h"

class ModelingWidget : public QWidget {

Q_OBJECT

public:
    ModelingWidget();
    void plotLine(lines_t* line);

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *controlsLayout;
    QPushButton *okButton;
    QLineEdit *projectionWidget;
    QPushButton *replotButton;
    Jenia *plotWidget;
    Track *track;
    lines_t* line;

public slots:
    void changeProjection();

};

#endif // MODELING_H
