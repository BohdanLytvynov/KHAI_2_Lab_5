#include "Student.h"

using s = Student;

#pragma region Get Set Definitions

int s::GetGroup() const
{
	return m_group;
}

float s::GetMark() const
{
	return m_mark;
}

void s::SetGroup(int group)
{
	m_group = group;
}

void s::SetMark(float mark)
{
	m_mark = mark;
}

#pragma endregion

#pragma region Ctor

s::Student() {}

s::Student(const int id, const us& surename, const us& name, const us& lastname,
	int age, int group, float mark, age_valid* age_validator,
	group_valid* group_validator, mark_valid* mark_validator) :
	Person(id, surename, name, lastname, age, age_validator)
{
	if (group_validator == nullptr)
	{		
		m_group_validator = group_valid(us("������� ��� ������� ������ �����!"), 
			[](const std::string& inp) -> int
			{
				return std::stoi(inp);
			},
			[](const int& inp, us& error) -> bool
			{
				if (inp < 0)
				{
					error = "����� ������ �� ���� ���� ������ 0!";

					return false;
				}

				return true;
			});
	}
	else
	{
		m_group_validator = *group_validator;
	}

	if (mark_validator == nullptr)
	{
		m_mark_validator = mark_valid(us("������� ��� ������� ������ ��������!"),
			[](const std::string& inp)-> float
			{
				return std::stof(inp);
			},
			[](const float& inp, us& error) -> bool
			{
				if (inp < 0)
				{
					error = "������ �� ���� ���� ��\"����!";
					return false;
				}

				return true;
			});
	}
	else
	{
		m_mark_validator = *mark_validator;
	}

	if (group < 0)
	{
		throw std::runtime_error("Incorrect group number! ");
	}

	if (mark < 0)
	{
		throw std::runtime_error("Incorrect mark! Mark should be greater 0");
	}

	m_group = group;

	m_mark = mark;
}

#pragma endregion

