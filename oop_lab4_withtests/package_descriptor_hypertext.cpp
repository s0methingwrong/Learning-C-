#include "package_descriptor_hypertext.h"

void package_descriptor_hypertext::show_info()
{
	package_descriptor::show_info();
	if (m_count_link > 0) {
		cout << "—сылки: " << endl;
		for (int i = 0; i < m_count_link; i++)
		{
			cout << i + 1 << ". ";
			m_links[i]->show_info();
		}
	}
}
