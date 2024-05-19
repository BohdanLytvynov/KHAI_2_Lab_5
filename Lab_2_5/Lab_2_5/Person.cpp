#include "Person.h"

using p = Person;

#pragma region Static definitions

int p::m_curr_id = 0;

#pragma endregion

#pragma region Get Set

int p::GetId() const
{
	return m_id;
}

us& p::GetName()
{
	return m_name;
}

us& p::GetSurename()
{
	return m_surename;
}

us& p::GetLastname()
{
	return m_lastname;
}

#pragma endregion

#pragma region Ctor definition

p::Person(const us& name, const us& surename, const us& lastname, int age):
	m_name(name), m_surename(surename), m_lastname(lastname)
{
	m_id = m_curr_id;

	++m_curr_id;	

	if (age < 0 && age > 100)
		throw std::runtime_error("Incorrect range for age variable!");
	else
	{
		m_age = age;
	}
}

#pragma endregion


