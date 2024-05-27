#include"StudentDb.h"

#pragma region Ctor Definition


/////////////////////////////////////////////////////////////////////////////
student_db_provider::student_db_provider(const std::string& path,
	std::ifstream* ifs, std::ofstream* ofs)
{
	m_path = path;

	m_input_output = 0;//No streams are in use

	m_inp_file_stream = ifs;

	m_out_file_stream = ofs;
}

#pragma endregion

#pragma region Functions definitions

std::vector<Student> student_db_provider::ReadFromSource()
{
	std::vector<Student> res;

	if (m_input_output != 0)
	{
		m_inp_file_stream->open(m_path);

		m_input_output = 1;

		Student s;

		if (m_inp_file_stream->is_open())
		{
			while (!m_inp_file_stream->eof())
			{
				*m_inp_file_stream >> s;

				res.push_back(s);
			}
		}
		else
		{
			throw std::runtime_error("Fail to open the file for reading!");
		}

		if (m_inp_file_stream->is_open())
			m_inp_file_stream->close();

		m_input_output = 0;
	}
		
	return res;
}

void student_db_provider::SaveToSource(const std::vector<Student>& data_set) const
{
	if (m_input_output != 0)
	{
		m_out_file_stream->open(m_path);

		m_input_output = 2;

		if (m_out_file_stream->is_open())
		{
			for (auto s : data_set)
			{
				*m_out_file_stream << s;
			}
		}
		else
		{
			throw std::runtime_error("Fail to open the file for writing!");
		}

		if (m_out_file_stream->is_open())
			m_out_file_stream->close();

		m_input_output = 0;
	}	
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////

student_db::student_db(Idata_provider<Student>* dataProvider, 
	std::function<void(Student*, const Student&)> edit_proc) 
	: file_data_base(dataProvider, edit_proc)
{
	
}

void student_db::Add(const Student& entity)
{
	int id = file_data_base<Student>::GetDataSet().size() + 1;

	Student& temp = const_cast<Student&>(entity);

	temp.SetId(id);

	file_data_base<Student>::Add(temp);
}


