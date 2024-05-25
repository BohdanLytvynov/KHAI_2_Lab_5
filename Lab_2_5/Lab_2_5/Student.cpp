#include "Student.h"

using s = Student;

#pragma region Get Set Definitions

int s::GetGroup() const
{
	return m_group;
}

float& s::GetMark()
{
	return m_mark;
}

#pragma endregion

#pragma region Ctor

s::Student(const int id, const us& name, const us& surename, const us& lastname, int age, int group, float mark) :
	Person(id, name, surename, lastname, age), m_group(group), m_mark(mark)
{

}

#pragma endregion

