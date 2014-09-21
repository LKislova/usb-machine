#ifndef USBCONNECTION_H
#define USBCONNECTION_H

#include <QObject>
#include "libusb.h"


#define VENDOR_ID 1155
#define PRODUCT_ID 22336

#define CDC_IN_EP                       0x81  /* EP1 for data IN */
#define CDC_OUT_EP                      0x01  /* EP1 for data OUT */
#define CDC_CMD_EP                      0x82  /* EP2 for CDC commands */

class UsbConnection : public QObject
{
    Q_OBJECT
public:
    UsbConnection(QObject *parent = 0);
    ~UsbConnection();

    void print_info();
private:
    libusb_context *context;

signals:

public slots:

};

#endif // USBCONNECTION_H
