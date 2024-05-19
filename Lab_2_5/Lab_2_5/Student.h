#ifndef STUDENT_H

#define STUDENT_H

#include "Person.h"

struct Student : public Person
{
#pragma region Get Set

	int GetGroup() const;

	float& GetMark();

#pragma endregion

#pragma region Ctor

	Student(const us& name, const us& surename, const us& lastname, int age, int group, float mark);

#pragma endregion


private:
#pragma region State

	int m_group;

	float m_mark;

#pragma endregion

};

#endif // !STUDENT_H

