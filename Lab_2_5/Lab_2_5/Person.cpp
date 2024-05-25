#include "Person.h"

using p = Person;

#pragma region Get Set

const int& p::GetId() const
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

int& p::GetAge()
{
	return m_age;
}

const age_valid& p::GetAgeValidator() const
{
	return m_age_validator;
}

#pragma endregion

#pragma region Ctor definition

p::Person(const int id, const us& name, const us& surename, const us& lastname, int age,
	age_valid* age_validator):
	m_id(id), m_name(name), m_surename(surename), m_lastname(lastname)	
{	
	m_name.use_for_input();

	m_surename.use_for_input();

	m_lastname.use_for_input();
	
	if (age < 0 && age > 100)
		throw std::runtime_error("Incorrect range for age variable!");
	else
	{
		m_age = age;
	}

	if (age_validator == nullptr)
	{		
		auto valid_age_range = [](const int& inp, strings::ukrString& error)-> bool
			{
				if (inp <= 0 && inp > 70)
				{
					error = "Невірний діапазон чисел!";

					return false;
				}

				return true;
			};

		auto age_converter = [](const std::string& inp) -> int
			{
				return std::stoi(inp);
			};

		m_age_validator = age_valid(us("Помилка при конвертуванні до числа!"),
			age_converter, valid_age_range);
	}
	else
		m_age_validator = *age_validator;
}

p::Person(const p& other)
{
	m_id = other.m_id;
	m_name = other.m_name;
	m_surename = other.m_surename;
	m_lastname = other.m_lastname;
	m_age = other.m_age;
	m_age_validator = other.m_age_validator;	
}

#pragma endregion

#pragma region Logical Operators

bool p::operator==(const p& r) const
{
	return m_id == r.m_id;
}

bool p::operator!=(const p& r) const
{
	return !(this->operator==(r));
}

#pragma endregion

#pragma region Assignment operator

p& p::operator=(const p& other)
{
	this->m_id = other.m_id;
	this->m_surename = other.m_surename;
	this->m_name = other.m_name;
	this->m_lastname = other.m_lastname;
	this->m_age = other.m_age;
	this->m_age_validator = other.m_age_validator;

	return *this;
}

#pragma endregion




