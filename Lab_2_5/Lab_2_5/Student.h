#ifndef STUDENT_H

#define STUDENT_H

#include "Person.h"

using group_valid = validation::Validator<std::string, int, us>;

using mark_valid = validation::Validator<std::string, float, us>;

struct Student : public Person
{
#pragma region Get Set

	int GetGroup() const;

	float GetMark() const;

	//Set

	void SetGroup(int group);

	void SetMark(float mark);

	const group_valid& GetGroupValidator() const;

	const mark_valid& GetMarkValidator() const;

#pragma endregion

#pragma region Ctor

	Student();

	Student(const int id, const us& surename, const us& name, const us& lastname,
		int age, int group, float mark, age_valid *age_validator = nullptr, 
		group_valid* group_validator= nullptr, mark_valid* mark_validator = nullptr);

	Student(const Student& other);

#pragma endregion

#pragma region Operators for input output

	friend std::istream& operator >> (std::istream& is, Student& s)
	{
		Person temp;

		is >> temp;

		s.SetId(temp.GetId());
		s.SetSurename(temp.GetSurename());
		s.SetName(temp.GetName());
		s.SetLastname(temp.GetLastname());
		s.SetAge(temp.GetAge());

		//group input

		std::string temp_inp;

		us error_msg;

		for (; ;)
		{
			std::cout << us("Введіть групу студента: (числа мають більше 0)") << std::endl;

			is >> temp_inp;

			if (s.m_mark_validator.validate(temp_inp, error_msg))
			{
				break;
			}
			else
			{
				std::cout << error_msg << std::endl;
			}
		}

		s.m_group = std::stoi(temp_inp);

		for (; ;)
		{
			std::cout << us("Введіть оцінку студента: (В форматі: 0.00)") << std::endl;

			is >> temp_inp;

			if (s.m_mark_validator.validate(temp_inp, error_msg))
			{
				break;
			}
			else
			{
				std::cout << error_msg << std::endl;
			}
		}

		return is;
	}

	friend std::ostream& operator <<(std::ostream& os, Student& s)
	{
		os << reinterpret_cast<Person&>(s);

		os << " " << s.GetGroup() << " " << s.GetMark();

		return os;
	}

#pragma endregion

#pragma region Operators for read and write

	friend std::ifstream& operator >> (std::ifstream& ifs, Student& s)
	{
		std::vector<us> words;

		us row;

		char delim[] = { ' ' };

		while (!ifs.eof())
		{
			us::getLine(ifs, row);

			if (row.getLength() > 0)
			{
				us::Split(row, words, delim);

				s.SetId(std::stoi(words[0].to_string()));
				s.SetSurename(words[1]);
				s.SetName(words[2]);
				s.SetLastname(words[3]);
				s.SetAge(std::stoi(words[4].to_string()));
				s.m_group = std::stoi(words[5].to_string());
				s.m_mark = std::stof(words[6].to_string());
			}
		}

		return ifs;
	}

	friend std::ofstream& operator << (std::ofstream& ofs, Student& s)
	{
		ofs << s.GetId() << " " << s.GetSurename() << " " << s.GetName() << " " << s.GetLastname() << " " << s.GetAge() << s.m_group << " " << s.m_mark << std::endl;

		return ofs;
	}

#pragma endregion



#pragma region Logical operators

	bool operator == (const Student& r) const;

	bool operator != (const Student& r) const;

#pragma endregion

#pragma region Assignment operator

	Student& operator = (const Student& other);

#pragma endregion



private:
#pragma region State

	int m_group;

	float m_mark;

	///Validation

	group_valid m_group_validator;

	mark_valid m_mark_validator;

#pragma endregion

};

#endif // !STUDENT_H

