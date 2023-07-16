#pragma once
#include "package_descriptor.h"
#include "package_descriptor_file.h"

class package_descriptor_mail :
    public package_descriptor
{
private:
    string m_user_name;

public:
    package_descriptor_mail(string address_sender, string address_recipient, descriptor_message* descriptor_message,
        string user_name) : package_descriptor(address_sender, address_recipient, descriptor_message), m_user_name(user_name) {
    }

    string get_user_name() {
        return m_user_name;
    }

    type_package get_type_package() override {
        return type_package::mail;
    }

    void show_info() override;

    package_descriptor_file* convert(type_code t_code, info_type t_info);
};

