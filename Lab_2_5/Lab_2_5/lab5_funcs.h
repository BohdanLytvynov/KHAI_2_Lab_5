#ifndef LAB5_FUNCS_H

#define LAB5_FUNCS_H

#include"../include/ukrString.h"
#include"functional"

namespace lab5_functions
{
	template<class T>
	static T Input(const strings::ukrString& msg, std::function<T(std::string& str)> converter,
		std::function<bool(std::string& str, strings::ukrString& error)> validator = nullptr)
	{
		strings::ukrString error;

		std::string str;

		do
		{
			std::cout << msg << std::endl;

			std::getline(std::cin, str);

			if (!validator)
				break;

			if (validator(str, error))
				break;
			else
				std::cout << error << std::endl;

		} while (true);

		return converter(str);
	}

	auto edit_proc = [](Student* curr, const Student& newStudent)->void
		{
			if (curr->GetSurename() != newStudent.GetSurename())
				curr->SetSurename(newStudent.GetSurename());

			if (curr->GetName() != newStudent.GetName())
				curr->SetName(newStudent.GetName());

			if (curr->GetLastname() != newStudent.GetLastname())
				curr->SetLastname(newStudent.GetLastname());

			if (curr->GetAge() != newStudent.GetAge())
				curr->SetAge(newStudent.GetAge());

			if (curr->GetGroup() != newStudent.GetGroup())
				curr->SetGroup(newStudent.GetGroup());

			if (curr->GetMark() != newStudent.GetMark())
				curr->SetMark(newStudent.GetMark());
		};

	auto to_int_converter = [](std::string& str)->int
		{
			return std::stoi(str);
		};

	void Display(std::vector<Student>& students)
	{
		for (auto& s : students)
		{
			std::cout << s;
		}
	}

#pragma region Predicates for Sorting

	static bool Pred_Surename(const Student& r, const Student& l)
	{
		return r.GetSurename().to_string() > l.GetSurename().to_string();
	}

	static bool Pred_Name(const Student& r, const Student& l)
	{
		return r.GetName().to_string() > l.GetName().to_string();
	}

	static bool Pred_Lastname(const Student& r, const Student& l)
	{
		return r.GetLastname().to_string() > l.GetLastname().to_string();
	}

	static bool Pred_Age(const Student& r, const Student& l)
	{
		return r.GetAge() > l.GetAge();
	}

	static bool Pred_Group(const Student& r, const Student& l)
	{
		return r.GetGroup() > l.GetGroup();
	}

	static bool Pred_Group(const Student& r, const Student& l)
	{
		return r.GetMark() > l.GetMark();
	}

#pragma endregion

}



#endif // !LAB5_FUNCS_H

