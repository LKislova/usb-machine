#include "usbconnection.h"

UsbConnection::UsbConnection(QObject *parent) : QObject(parent) {
    this->context = context;
    libusb_init(&this->context);
    libusb_set_debug(context, 2);
}

UsbConnection::~UsbConnection(){
    libusb_exit(context);
}

void UsbConnection::print_info(){
    libusb_device **list;
    ssize_t size_devices = libusb_get_device_list(context, &list);
    for (int i = 0; i < size_devices; i++) {
        libusb_device_descriptor desc;
        libusb_config_descriptor *config_desc = NULL;
        int error_config = 0;
        libusb_get_device_descriptor(list[i], &desc);

        if (desc.idVendor == (uint16_t) VENDOR_ID &&
                desc.idProduct == (uint16_t) PRODUCT_ID) {
            libusb_device_handle *handler;
            int error = libusb_open(list[i], &handler);
            int interface = 0;
            int alternate_settings = 0;

            if (error) {
                printf("Can not open device.\n");
                break;
            }
            error_config = libusb_get_active_config_descriptor(
                        list[i], &config_desc);
            //if (error_config) {
            //    continue;
            //}
            printf("\nbegin descriptor\n");
            printf("\tport: %d\n", libusb_get_port_number(list[i]));
            printf("\tbus_num: %d\n", libusb_get_bus_number(list[i]));
            printf("\taddress: %d\n", libusb_get_device_address(list[i]));
            printf("\tspeed: %d\n", libusb_get_device_speed(list[i]));
            printf("\tClass: %d\n", desc.bDeviceClass);
            printf("\tSubClass: %d\n", desc.bDeviceSubClass);
            printf("\tDeviceProtocol: %d\n", desc.bDeviceProtocol);
            printf("\tidVendor: %d\n", desc.idVendor);
            printf("\tidProduct: %d\n", desc.idProduct);
            printf("\tiManufacturer: %d\n", desc.iManufacturer);
            printf("\tiProduct: %d\n", desc.iProduct);
            printf("\tiSerialNumber: %d\n", desc.iSerialNumber);
            printf("\tbMaxPacketSize0: %d\n", desc.bMaxPacketSize0);
            printf("\tbNumConfigurations: %d\n", desc.bNumConfigurations);
            printf("\tconfigDescriptor:\n");
            if (error_config) {
                if (error_config == LIBUSB_ERROR_NOT_FOUND) {
                    printf("Error config not founds\n");
                } else {
                    printf("Error in config %d\n", error_config);
                }
            } else {
                printf("\tiConfiguration: %d\n", config_desc->iConfiguration);
                printf("\tbNumInterface: %d\n", config_desc->bNumInterfaces);
                printf("\tbmAttributes: %d\n", config_desc->bmAttributes);
                for (int i_interface = 0; i_interface < config_desc->bNumInterfaces; i_interface++) {
                    for (int i_altinterface = 0;
                         i_altinterface < config_desc->interface[i_interface].num_altsetting;
                        i_altinterface++) {
                        libusb_interface_descriptor alt_settings = config_desc->interface[i_interface].altsetting[i_altinterface];
                        printf("\tbInterfaceClass[%d][%d]: %d\n", i_interface, i_altinterface,
                            alt_settings.bInterfaceClass);
                        interface = i_interface;
                        alternate_settings = i_altinterface;


                        printf("\tbInterfaceNumber[%d][%d]: %d\n", i_interface, i_altinterface,
                            alt_settings.bInterfaceNumber);
                        printf("\tbInterfaceProtocol[%d][%d]: %d\n", i_interface, i_altinterface,
                            alt_settings.bInterfaceProtocol);
                        printf("\textra[%d][%d]: %s\n", i_interface, i_altinterface,
                            alt_settings.extra);
                        for (int i_ep = 0; i_ep < alt_settings.bNumEndpoints; i_ep++) {
                            libusb_endpoint_descriptor ep_desc = alt_settings.endpoint[i];
                            printf("\t\tbEndpointAddress[%d][%d][%d]: %d (in=%d / out=%d)\n",
                                i_interface, i_altinterface, i_ep,
                                ep_desc.bEndpointAddress, LIBUSB_ENDPOINT_IN, LIBUSB_ENDPOINT_OUT);
                            printf("\t\tbDescriptorType[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                                ep_desc.bDescriptorType);
                            printf("\t\tbmAttributes[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                                ep_desc.bmAttributes);
                            printf("\t\textra[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                                ep_desc.extra_length);
                            printf("\t\tbSynchAddress[%d][%d][%d]: %d\n", i_interface, i_altinterface, i_ep,
                                ep_desc.bSynchAddress);
                        }
                    }
                }
                libusb_free_config_descriptor(config_desc);
                error = libusb_claim_interface(handler, interface);
                //error = libusb_set_interface_alt_setting(handler, interface, alternate_settings);

                if (error) {
                    printf("Error set interface.\n");
                    break;
                }
                int actual_length = 0;
                unsigned char data[] = "A";
                int r = 0;

//                r = libusb_interrupt_transfer(handler, LIBUSB_ENDPOINT_IN, data, 2, &actual_length, 0);
//                if (r == 0 && actual_length == sizeof(data)) {
//                    // results of the transaction can now be found in the data buffer
//                    // parse them here and report button press
//                } else {
//                    printf("Can not send data LIBUSB_ENDPOINT_IN. %d\n", r);
//                }

//                r = libusb_bulk_transfer(handler, CDC_IN_EP, data, sizeof(data), &actual_length, 0);
//                if (r == 0 && actual_length == sizeof(data)) {
//                    // results of the transaction can now be found in the data buffer
//                    // parse them here and report button press
//                } else {
//                    printf("Can not send data CDC_IN_EP. %d\n", r);
//                }

                r = libusb_bulk_transfer(handler, CDC_OUT_EP, data, sizeof(data), &actual_length, 0);
                if (r == 0 && actual_length == sizeof(data)) {
                    // results of the transaction can now be found in the data buffer
                    // parse them here and report button press
                } else {
                    printf("Can not send data CDC_OUT_EP. %d\n", r);
                }

                libusb_release_interface(handler, interface);
                libusb_close(handler);

            }
        }
    }
    libusb_free_device_list(list, 1);
}
