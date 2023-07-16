#include "server.h"

void server::add(package_descriptor* package)
{
	m_packages.push_back(package);
}

package_descriptor* server::find_package(string address_recipient, type_package type)
{
	for (int i = 0; i < m_packages.count(); i++)
	{
		if (m_packages[i]->get_address_recipient() == address_recipient && m_packages[i]->get_type_package() == type) {
			return m_packages[i];
		}
	}
	return nullptr;
}

bool server::remove_package(string address_recipient, type_package type)
{
	for (int i = 0; i < m_packages.count(); i++)
	{
		if (m_packages[i]->get_address_recipient() == address_recipient && m_packages[i]->get_type_package() == type) {
			m_packages.remove_at(i);
			return true;
		}
	}
	return false;
}

string server::get_name() const
{
	return m_name;
}

string server::get_address() const
{
	return m_address;
}

void server::show()
{
	for (int i = 0; i < m_packages.count(); i++) {
		m_packages[i]->show_info();
		cout << endl;
	}
}

void server::show_senders()
{
	set<string> senders;
	for (int i = 0; i < m_packages.count(); i++) {
		senders.insert(m_packages[i]->get_address_sender());
	}

	for (string s : senders) {
		cout << s << endl;
	}
}
