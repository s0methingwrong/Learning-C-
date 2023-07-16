#pragma once
#include "package_descriptor.h"
#include "type_code.h"
#include "info_type.h"
#include "package_descriptor_hypertext.h"
#include "descriptor_link.h"

class package_descriptor_hypertext;

class package_descriptor_file :
    public package_descriptor
{
private:
    type_code m_code;
    info_type m_info_type;

public:
    package_descriptor_file(string address_sender, string address_recipient, descriptor_message* descriptor_message,
        type_code code, info_type info_type) : package_descriptor(address_sender, address_recipient, descriptor_message),
        m_code(code), m_info_type(info_type) {}

    type_code get_type_code() {
        return m_code;
    }

    info_type get_info_type() {
        return m_info_type;
    }

    type_package get_type_package() override {
        return type_package::file;
    }

    void show_info() override;

    package_descriptor_hypertext* convert(int count_links, descriptor_link** links);
};


