#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>

int main() {
    int res;
    libusb_device **devices;
    libusb_device_handle *device_handle;
    struct libusb_device_descriptor desc;
    
    res = libusb_init(NULL);
    if (res < 0) {
        fprintf(stderr, "libusb_init error: %d\n", res);
        return EXIT_FAILURE;
    }
    
    if (geteuid() != 0) {
        printf("You need to run this program with sudo\n");
        libusb_exit(NULL);
        return EXIT_FAILURE;
    }
    
    ssize_t cnt = libusb_get_device_list(NULL, &devices);
    if (cnt < 0) {
        fprintf(stderr, "libusb_get_device_list error: %zd\n", cnt);
        libusb_exit(NULL);
        return EXIT_FAILURE;
    }
    
    for (ssize_t i = 0; i < cnt; ++i) {
        libusb_device *device = devices[i];
        libusb_get_device_descriptor(device, &desc);
       
        // "Xbox" controller, actually is a fake ps3 controller 
        if (desc.idVendor == 0x045e && desc.idProduct == 0x028e) {
            res = libusb_open(device, &device_handle);
            if (res < 0) {
                fprintf(stderr, "libusb_open error: %d\n", res);
                libusb_free_device_list(devices, 1);
                libusb_exit(NULL);
                return EXIT_FAILURE;
            }
            /*
            libusb_device_handle *device_handle,
            uint8_t bmRequestType: 0xc1 = 11000001 (request to interface),
            uint8_t bRequest,
            uint16_t wValue,
            uint16_t wIndex,
            unsigned char *data,
            uint16_t wLength,
            unsigned int timeout
            */
            res = libusb_control_transfer(device_handle, 0xc1, 0x01, 0x0100, 0x00, NULL, 0, 0);
            if (res < 0) {
                fprintf(stderr, "libusb_control_transfer error: %d\n", res);
            }
            
            libusb_close(device_handle);
            break;
        }
    }
    
    libusb_free_device_list(devices, 1);
    libusb_exit(NULL);
    return EXIT_SUCCESS;
}

