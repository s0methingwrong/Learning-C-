#pragma once
#include <iostream>
#include "descriptor_message.h"
#include "type_package.h"
using namespace std;

class package_descriptor
{
private:
	string m_address_sender;
	string m_address_recipient;
	descriptor_message* m_descriptor_message;

public:
	package_descriptor(string address_sender, string address_recipient, descriptor_message* descriptor_message) :
		m_address_sender(address_sender), m_address_recipient(address_recipient), m_descriptor_message(descriptor_message) {}

	string get_address_sender() {
		return m_address_sender;
	}

	string get_address_recipient() {
		return m_address_recipient;
	}

	descriptor_message* get_descriptor_message() {
		return m_descriptor_message;
	}

	virtual type_package get_type_package() = 0;
	virtual void show_info();
};

