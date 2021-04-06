//
// Created by xela on 5/3/18.
//

#pragma once

#include "common/basic_types.h"
#include "fstream"
#include "string"

class HIDDevice {
public:
    HIDDevice(const std::string& path, UInt32 dataSize);
    virtual ~HIDDevice();

protected:
    size_t m_dataSize;
    char* m_data;
    void update();

private:
    int m_fd;
};
