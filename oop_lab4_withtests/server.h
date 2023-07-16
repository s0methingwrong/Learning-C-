#pragma once
#include "package_descriptor.h"
#include "type_package.h"
#include <vector>
#include <set>
#include "my_vector.h"

class server
{
private:
	string m_name;
	string m_address;
	my_vector<package_descriptor*> m_packages;

public:
	server(string name, string address) : m_name(name), m_address(address) {}

	void add(package_descriptor* package);
	package_descriptor* find_package(string address_recipient, type_package type);
	bool remove_package(string address_recipient, type_package type);

	string get_name() const;
	string get_address() const;

	void show();
	void show_senders();
};

