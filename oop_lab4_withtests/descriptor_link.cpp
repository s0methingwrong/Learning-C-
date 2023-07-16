#include "descriptor_link.h"

void descriptor_link::show_info()
{
	string type_p = m_protokol == type_protokol::ftp ? "FTP" : "Http";
	cout << "Тип протокола: " << type_p << ", Имя сервера: " << m_server_name << endl;
}
