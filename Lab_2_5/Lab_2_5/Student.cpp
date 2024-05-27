#include "Student.h"

using s = Student;

#pragma region Get Set Definitions
//Get
int s::GetGroup() const
{
	return m_group;
}

float s::GetMark() const
{
	return m_mark;
}
//Set
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

s::Student(age_valid* age_validator,
	group_valid* group_validator, mark_valid* mark_validator) : Person(age_validator) 
{
	if (group_validator == nullptr)
	{
		m_group_validator = group_valid(us("Помилка при введені номера групи!"),
			[](const std::string& inp) -> int
			{
				return std::stoi(inp);
			},
			[](const int& inp, us& error) -> bool
			{
				if (inp < 0)
				{
					error = "Номер группи не може бути меньше 0!";

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
		m_mark_validator = mark_valid(us("Помилка при введені оцінки студента!"),
			[](const std::string& inp)-> float
			{
				return std::stof(inp);
			},
			[](const float& inp, us& error) -> bool
			{
				if (inp < 0)
				{
					error = "Оцінка не може бути від\"ємна!";
					return false;
				}

				return true;
			});
	}
	else
	{
		m_mark_validator = *mark_validator;
	}
}

s::Student(const int id, const us& surename, const us& name, const us& lastname,
	int age, int group, float mark, age_valid* age_validator,
	group_valid* group_validator, mark_valid* mark_validator) :
	Person(id, surename, name, lastname, age, age_validator)
{
	if (group_validator == nullptr)
	{		
		m_group_validator = group_valid(us("Помилка при введені номера групи!"), 
			[](const std::string& inp) -> int
			{
				return std::stoi(inp);
			},
			[](const int& inp, us& error) -> bool
			{
				if (inp < 0)
				{
					error = "Номер группи не може бути меньше 0!";

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
		m_mark_validator = mark_valid(us("Помилка при введені оцінки студента!"),
			[](const std::string& inp)-> float
			{
				return std::stof(inp);
			},
			[](const float& inp, us& error) -> bool
			{
				if (inp < 0)
				{
					error = "Оцінка не може бути від\"ємна!";
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

Student::Student(const Student& other) : Person(other)
{
	this->m_group = other.m_group;
	this->m_mark = other.m_mark;

	this->m_group_validator = other.m_group_validator;
	this->m_mark_validator = other.m_mark_validator;
}

#pragma endregion

#pragma region Logical operators

bool Student::operator==(const Student& r) const
{
	return r.GetId() == r.GetId();
}

bool Student::operator!=(const Student& r) const
{
	return r.GetId() != r.GetId();
}

#pragma endregion

#pragma region Assignment operator

Student& Student::operator=(const Student& other)
{
	this->operator=(other);

	m_group = other.m_group;

	m_mark = other.m_mark;

	m_group_validator = other.m_group_validator;

	m_mark_validator = other.m_mark_validator;

	return *this;
}

#pragma endregion



