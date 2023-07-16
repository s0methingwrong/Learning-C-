#include "package_descriptor.h"

void package_descriptor::show_info()
{
	cout << "Адрес отправителя: " << m_address_sender << endl;
	cout << "Адрес получателя: " << m_address_recipient << endl;
	cout << "Описатель сообщения: ";
	m_descriptor_message->show_info();
}
