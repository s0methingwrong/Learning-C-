#pragma once
#include "descriptor.h"
class descriptor_message :
    public descriptor
{
private:
    unsigned int m_len_message;
    char* m_message;

public:
    descriptor_message(unsigned int len_message, char* message) : m_len_message(len_message), m_message(message){}

    char* get_message() {
        return m_message;
    }

    void show_info() override;
};

