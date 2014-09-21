#ifndef USBTOOL_H
#define USBTOOL_H

#include "libusb.h"
#include <QList>
#include <iostream>

class UsbTool {

public:
    UsbTool();
    ~UsbTool();
    QList<QString>* getDevices();

private:
    libusb_context *usbContex;
};

#endif // USBTOOL_H
