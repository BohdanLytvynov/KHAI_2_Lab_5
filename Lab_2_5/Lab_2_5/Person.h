#ifndef PERSON_H

#define PERSON_H

#include"ukrString.h"

using us = strings::ukrString;

struct Person
{
#pragma region Get Set

	int GetId() const;

	us& GetName();

	us& GetSurename();

	us& GetLastname();

#pragma endregion

#pragma region Ctor

	Person(const us& name, const us& surename, const us& lastname, int age);
		
#pragma endregion


private:
#pragma region State
	int m_id;

	static int m_curr_id;

	us m_name;

	us m_surename;

	us m_lastname;

	int m_age;
#pragma endregion

};

#endif // !PERSON_H

