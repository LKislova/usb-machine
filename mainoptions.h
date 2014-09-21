#ifndef MAINOPTIONS_H
#define MAINOPTIONS_H

#include <QtWidgets>

class MainOptions : public QWidget {
    Q_OBJECT
public:
    explicit MainOptions(QWidget *parent = 0);
    double getDimension();
    void setDimension(double d);
private:
    QVBoxLayout *mainLayout;
    void createMainLayout();
    QRadioButton *buttonMM ;
    QRadioButton *buttonSM ;
    QRadioButton *buttonM ;
signals:

public slots:

};

#endif // MAINOPTIONS_H
