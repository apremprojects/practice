#include <windows.h>
#include <inttypes.h>
#include <iostream>
#include <vector>
#include "serial.h"
bool writeStuff(std::vector<uint8_t> &nums) {
    HANDLE h_Serial;
    h_Serial = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (h_Serial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << "Can't find TI-84(NOT PLUGGED IN)\n";
            return false;
        }
        std::cout << "Error\n";
        return false;
    }
    DCB dcbSerialParam = { 0 };
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(h_Serial, &dcbSerialParam)) {
        //handle error here
        return false;
    }

    dcbSerialParam.BaudRate = CBR_9600;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity = NOPARITY;

    if (!SetCommState(h_Serial, &dcbSerialParam)) {
        std::cout << "Unknown Error\n";
    }

    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 60;
    timeout.ReadTotalTimeoutConstant = 60;
    timeout.ReadTotalTimeoutMultiplier = 15;
    timeout.WriteTotalTimeoutConstant = 60;
    timeout.WriteTotalTimeoutMultiplier = 8;
    if (!SetCommTimeouts(h_Serial, &timeout)) {
        std::cout << "Unknown Error\n";
    }
    char sBuff[76800];
    for (int i = 0; i < nums.size(); i++) {
        sBuff[i] = (char)nums[i];
    }
    DWORD dwRead = 0;
    WriteFile(h_Serial, sBuff, 76800, &dwRead, NULL);
    return true;
}