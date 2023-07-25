# Fix PS3/Xbox Controller
## Overview
This project provides a C code solution to enable the use of a cheap videogame controller on Linux systems. The objective is to make the controller work seamlessly within my virtual environments and overcome issues with the xpad driver. The inspirationfor this C code comes from a Python-based solution that worked on Linux.

## How It Works
The C code presented in this project uses the libusb library to perform USB control transfers to the target USB device. The code sends specific control transfer requests (vendor-specific requests) to the controller to configure it.


## Dependencies
- libusb library: Ensure that the libusb library is installed on your Linux system before compile this C code.

## Inspiration from Python Code
The inspiration for this project comes from a Python-based solution created by [dnmodder](https://gist.github.com/dnmodder/de2df973323b7c6acf45f40dc66e8db3). The Python code demonstrated how to interact with the controller.

## How to use
1. Compile the C code using a C compiler such as gcc or clang:

    ```bash
    gcc fix_controller.c -o fix_controller -lusb-1.0
    ```

2. Run this code with sudo privileges:
    ``` bash
    sudo ./fix_controller
    ```

## Disclaimer
This project is designed for personal use within controlled environments where the cheap videogame controller's compatibility with the xpad driver is problematic.
