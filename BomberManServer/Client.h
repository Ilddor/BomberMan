#pragma once

#include <Windows.h>
#include <string>

class CClient
{
public:
	SOCKET m_socket;
	std::string m_name;
	bool m_ready;
	bool m_connected;
	int m_id;

	CClient(): m_ready(false), m_name("No Name"), m_connected(true) {};
};