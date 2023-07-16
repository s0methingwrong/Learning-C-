#pragma once
#include "package_descriptor.h"
#include "descriptor_link.h"
#include "descriptor_message.h"
#include "type_code.h"
#include "info_type.h"

class package_descriptor_hypertext :
    public package_descriptor
{
private:
    int m_count_link;
    descriptor_link** m_links;
    type_code m_code;
    info_type m_info_type;

public:
    package_descriptor_hypertext(string address_sender, string address_recipient, descriptor_message* descriptor_message,
        type_code code, info_type info_type, int count_link, descriptor_link** links) : package_descriptor(address_sender, address_recipient,
            descriptor_message), m_count_link(count_link), m_links(links), m_code(code), m_info_type(info_type) {
    }

    type_code get_type_code() {
        return m_code;
    }

    info_type get_info_type() {
        return m_info_type;
    }

    int get_count_link() {
        return m_count_link;
    }

    descriptor_link** get_links() {
        return m_links;
    }

    type_package get_type_package() override {
        return type_package::hypertext;
    }

    void show_info() override;
};

