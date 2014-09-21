#ifndef MACHINEOPTIONS_H
#define MACHINEOPTIONS_H

#include <QtWidgets>

class MachineOptions : public QWidget
{
    Q_OBJECT
public:
    explicit MachineOptions(QWidget *parent = 0);

    double getXArea();
    double getYArea();
    double getZArea();
    double getFArea();
    double getBlankArea();

    void setXArea(double x);
    void setYArea(double y);
    void setZArea(double z);
    void setFArea(double f);
    void setBlankArea(double blank);

private:
    QVBoxLayout* machineLayout;
    QHBoxLayout *xChildLay;
    QHBoxLayout *yChildLay;
    QHBoxLayout *zChildLay;
    QHBoxLayout *fChildLay;
    QHBoxLayout *blankChildLay;

    QLineEdit* xAreaEdit;
    QLineEdit* yAreaEdit;
    QLineEdit* zAreaEdit;
    QLineEdit* fAreaEdit;
    QLineEdit* blankAreaEdit;


    void createMachineLayout();
    void makeTempLayout(QHBoxLayout *child,
            QLabel *lable, QLineEdit* edit, QBoxLayout* parent);

signals:

public slots:

};

#endif // MACHINEOPTIONS_H
