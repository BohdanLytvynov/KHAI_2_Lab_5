#ifndef PERSON_H

#define PERSON_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include"ukrString.h"
#include"Validator.h"

using us = strings::ukrString;

using age_valid = validation::Validator<std::string, int, us>;

struct Person
{

#pragma region Get Set

	const int& GetId() const;

	us& GetName();

	us& GetSurename();

	us& GetLastname();

	int& GetAge();

	const age_valid& GetAgeValidator() const;

#pragma endregion

#pragma region Operators for input and output

    friend std::istream& operator >> (std::istream& is, Person& p)
	{
		std::cout << us("¬вед≥ть пр≥звище людини:") << std::endl;

		is >> p.m_surename;

		std::cout << us("¬вед≥ть ≥м€ людини:") << std::endl;

		is >> p.m_name;

		std::cout << us("¬вед≥ть по-батьков≥ людини:") << std::endl;

		is >> p.m_lastname;

		std::string age_str;

		us error;

		for (; ;)
		{
			std::cout << us("¬вед≥ть в≥к: (б≥льше 0 та не б≥льше 70))") << std::endl;

			is >> age_str;

			if (p.m_age_validator.validate(age_str, error))
			{
				p.m_age = std::stoi(age_str);

				break;
			}
			else
			{
				std::cout << error << std::endl;
			}
		}
				
		return is;
	}

	friend std::ostream& operator << (std::ostream& os, const Person& p)
	{
		os << p.m_id << " ) " << p.m_surename << " " << p.m_name << " " << p.m_lastname << " " << p.m_age << std::endl;
	}

#pragma endregion

#pragma region Operators for read write to file

	friend std::ofstream& operator << (std::ofstream& outf, const Person& p)
	{
		outf << p.m_id << " " << p.m_surename << " " << p.m_name << " " << p.m_lastname << " " << p.m_age;

		return outf;
	}

	friend std::ifstream& operator >> (std::ifstream& inf, Person& p)
	{
		us temp;

		std::vector<us> words;

		char delim[] = { ' ' };

		while (!inf.eof())
		{
			us::getLine(inf, temp);

			if (temp.getLength() > 0)
			{
				us::Split(temp, words, delim);

				p.m_id = std::stoi(words[0].to_string());
				p.m_surename = words[1];
				p.m_name = words[2];
				p.m_lastname = words[3];
				p.m_age = std::stoi(words[4].to_string());							
			}
		}

		return inf;
	}

#pragma endregion

#pragma region Logic operators

	bool operator == (const Person& r) const;
	
	bool operator != (const Person& r) const;
	
#pragma endregion

#pragma region Assignment operator

	Person& operator = (const Person& other);

#pragma endregion


#pragma region Ctor

	Person(const int id, const us& name, const us& surename, const us& lastname, int age,
		age_valid* age_vlidator = nullptr);
		
	Person(const Person& other);
	

#pragma endregion


private:
#pragma region State
	int m_id;
	
	us m_name;

	us m_surename;

	us m_lastname;

	int m_age;

	//Validation

	age_valid m_age_validator;

#pragma endregion

};

#endif // !PERSON_H

