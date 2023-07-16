#include "pch.h"
#include "../NetworkServer/descriptor_link.h"
#include "../NetworkServer/descriptor_link.cpp"
#include "../NetworkServer/descriptor_message.h"
#include "../NetworkServer/descriptor_message.cpp"
#include "../NetworkServer/my_vector.h"
#include "../NetworkServer/server.h"
#include "../NetworkServer/server.cpp"
#include "../NetworkServer/package_descriptor_mail.h"
#include "../NetworkServer/package_descriptor_mail.cpp"
#include "../NetworkServer/package_descriptor_file.h"
#include "../NetworkServer/package_descriptor_file.cpp"
#include "../NetworkServer/package_descriptor_hypertext.h"
#include "../NetworkServer/package_descriptor_hypertext.cpp"
#include "../NetworkServer/package_descriptor.h"
#include "../NetworkServer/package_descriptor.cpp"

TEST(TestDescriptorLink, TestConstructor) {
	descriptor_link* dlink = new descriptor_link(type_protokol::http, "ser");

	EXPECT_EQ(type_protokol::http, dlink->get_type_protokol());
	EXPECT_EQ("ser", dlink->get_server_name());
}

TEST(TestDescriptorMessage, TestConstructor) {
	descriptor_message* dmessage = new descriptor_message(10, "hello");

	EXPECT_TRUE(strcmp(dmessage->get_message(), "hello") == 0);
}

TEST(TestMyVector, TestPushBack) {
	my_vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);

	EXPECT_EQ(2, vec.count());
	EXPECT_EQ(10, vec[0]);
	EXPECT_EQ(20, vec[1]);
}

TEST(TestMyVector, TestRemoveAt) {
	my_vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);

	vec.remove_at(1);

	EXPECT_EQ(2, vec.count());
	EXPECT_EQ(10, vec[0]);
	EXPECT_EQ(30, vec[1]);
}

TEST(TestMyVector, TestRemoveAtIncorrectIndex) {
	my_vector<int> vec;
	vec.push_back(10);

	EXPECT_THROW(vec.remove_at(1), exception);
}

TEST(TestServer, TestConstructor) {
	server ser("My Server", "190.20.10.5");

	EXPECT_EQ("My Server", ser.get_name());
	EXPECT_EQ("190.20.10.5", ser.get_address());
}

TEST(TestServer, TestAddPackage) {
	server ser("My Server", "190.20.10.5");

	package_descriptor_file* pdf1 = new package_descriptor_file("1.1.1.1", "2.2.2.2",
		new descriptor_message(10, "hello"), type_code::ACII, info_type::data);
	package_descriptor_file* pdf2 = new package_descriptor_file("1.1.5.5", "2.2.4.4",
		new descriptor_message(10, "goodbuy"), type_code::ACII, info_type::data);

	ser.add(pdf1);
	ser.add(pdf2);

	EXPECT_TRUE(ser.find_package("2.2.2.2", type_package::file));
	EXPECT_TRUE(ser.find_package("2.2.4.4", type_package::file));
	EXPECT_FALSE(ser.find_package("2.2.4.4", type_package::hypertext));
}

TEST(TestServer, TestRemovePackage) {
	server ser("My Server", "190.20.10.5");

	package_descriptor_file* pdf1 = new package_descriptor_file("1.1.1.1", "2.2.2.2",
		new descriptor_message(10, "hello"), type_code::ACII, info_type::data);
	package_descriptor_file* pdf2 = new package_descriptor_file("1.1.5.5", "2.2.4.4",
		new descriptor_message(10, "goodbuy"), type_code::ACII, info_type::data);

	ser.add(pdf1);
	ser.add(pdf2);

	EXPECT_TRUE(ser.remove_package("2.2.4.4", type_package::file));
	EXPECT_FALSE(ser.find_package("2.2.4.4", type_package::file));
	EXPECT_FALSE(ser.remove_package("12.25.4.4", type_package::file));
}

TEST(TestPackageDescriptorMail, TestConvert) {
	package_descriptor_mail* pdm = new package_descriptor_mail("1.1.1.1", "2.2.2.2",
		new descriptor_message(10, "hello"), "Mika");

	package_descriptor_file* pdf = pdm->convert(type_code::BIN, info_type::control);

	EXPECT_EQ("2.2.2.2", pdf->get_address_recipient());
	EXPECT_EQ("1.1.1.1", pdf->get_address_sender());
	EXPECT_EQ(info_type::control, pdf->get_info_type());
	EXPECT_EQ(type_code::BIN, pdf->get_type_code());
	EXPECT_EQ(type_package::file, pdf->get_type_package());
}