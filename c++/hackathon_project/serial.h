#ifndef SERIAL_H
#define SERIAL_H
#include <windows.h>
#include <inttypes.h>
#include <iostream>
bool writeStuff(std::vector<uint8_t>& nums) {
    HANDLE h_Serial;
    h_Serial = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (h_Serial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            //serial port not found. Handle error here.
            std::cout << "Plug in TI-84\n";
            return false;
        }
        //any other error. Handle error here.
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
        //handle error here
        return false;
    }
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 60;
    timeout.ReadTotalTimeoutConstant = 60;
    timeout.ReadTotalTimeoutMultiplier = 15;
    timeout.WriteTotalTimeoutConstant = 60;
    timeout.WriteTotalTimeoutMultiplier = 8;
    if (!SetCommTimeouts(h_Serial, &timeout)) {
        //handle error here
        return false;
    }
    DWORD dwRead = 0;
    char sBuff[76800];
    for(int i = 0; i < nums.size(); i++) {
        sBuff[i] = (char)nums[i];
    }
    WriteFile(h_Serial, sBuff, 76800, &dwRead, NULL);
    return true;
};
#endif