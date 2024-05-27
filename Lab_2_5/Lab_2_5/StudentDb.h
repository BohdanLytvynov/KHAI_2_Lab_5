#ifndef STUDENTDB_H

#define STUDENTDB_H
#include"Student.h"
#include"../File_data_base/file_db.h"
#include"../File_data_base/Idata_provider.h"
#include<fstream>

struct student_db_provider : public Idata_provider<Student>
{
	std::vector<Student> ReadFromSource() override;

	void SaveToSource(const std::vector<Student>& data_set) const override;

#pragma region ctor

	student_db_provider(const std::string& path, std::ifstream* ifs, 
		std::ofstream* ofs);

#pragma endregion


private:
	std::ifstream* m_inp_file_stream;

	std::ofstream* m_out_file_stream;

	mutable char m_input_output;

	std::string m_path;
};


struct student_db : file_data_base<Student>
{
#pragma region Ctor
	student_db(Idata_provider<Student>* dataProvider, 
		std::function<void(Student*, const Student&)> edit_proc);
	
#pragma endregion

#pragma region Function

	void Add(const Student& entity) override;

#pragma endregion


};

#endif // !STUDENTDB_H

