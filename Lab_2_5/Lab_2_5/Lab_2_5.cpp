// Lab_2_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "StudentDb.h"
#include "lab5_funcs.h"
#include <fstream>
#include <crtdbg.h>

std::string m_path_to_file = "Data/Students.txt";

int main()
{
    using namespace lab5_functions;
    using namespace std;

    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(flag);

    std::ifstream inp_file_stream;

    std::ofstream ofstream;

    std::cout << "Student Database" << std::endl;

    student_db_provider* st_db_prov;

    student_db* db;

#pragma region Initialize data base

    try
    {
        st_db_prov = new student_db_provider(m_path_to_file, &inp_file_stream, &ofstream);

        db = new student_db(st_db_prov, edit_proc);
    }
    catch (const std::runtime_error& er)
    {
        cout << er.what() << endl;
    }
   

#pragma endregion

    do
    {
        int com = Input<int>(us("Виберіть опцію: \n\t1) Переглянути базу данних, натисніть 1"), to_int_converter,
            [](string& inp, us& error)->bool
            {
                int c = stoi(inp);

                if (c < 0)
                {
                    error = "Невірний ввод команди!";

                    return false;
                }
                return true;
            });

        vector<Student> students;

        switch (com)
        {
            case 1://View Data Base

                std::cout << "Student Database" << std::endl;

                system("cls");

                students = db->GetDataSet();

                Display(students);

                int sort_com = 0;

                do
                {
                    sort_com = Input<int>(us("Сортування: \n\t1) За Прізвищем - натисніть 1. \n\t2) За Іменем - натисніть 2. \n\t3) За По-Батькові - натисніть 3. \n\t4) За Віком - натисніть 4. \n\t5) За группою - натисніть 5. \n\t6) За оцінкою - натисніть 6. \n\t7) Вийти з режиму перегляду - натисніть 7."), to_int_converter,
                        [](string& inp, us& error)->bool
                        {
                            int c = stoi(inp);

                            if (c < 0 && c > 7)
                            {
                                error = "Невірний ввод команди!";

                                return false;
                            }
                            return true;
                        });

                    switch (sort_com)
                    {
                    case 1:
                        break;
                    }

                } while (sort_com != 7);
                
            break;
            default:
                break;
        }



    } while (true);

#pragma region Clear data base

    delete st_db_prov;

    delete db;

#pragma endregion


    return 0;
}

