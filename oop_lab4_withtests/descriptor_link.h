#pragma once
#include "descriptor.h"
#include <string>
#include "type_protocol.h"
using namespace std;

class descriptor_link :
    public descriptor
{
private:
    type_protokol m_protokol;
    string m_server_name;

public:
    descriptor_link(type_protokol protokol, string server_name) : m_protokol(protokol), m_server_name(server_name) {}

    type_protokol get_type_protokol() {
        return m_protokol;
    }

    string get_server_name() {
        return m_server_name;
    }

    void show_info() override;
};

