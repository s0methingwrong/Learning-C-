#include "package_descriptor_mail.h"

void package_descriptor_mail::show_info()
{
	package_descriptor::show_info();
	cout << "Имя пользователя: " << m_user_name << endl;
}

package_descriptor_file* package_descriptor_mail::convert(type_code t_code, info_type t_info)
{
	return new package_descriptor_file(get_address_sender(), get_address_recipient(), get_descriptor_message(), t_code, t_info);
}
