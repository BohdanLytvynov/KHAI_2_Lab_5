// Lab_2_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "StudentDb.h"
#include "lab5_funcs.h"
#include <fstream>
#include <crtdbg.h>
#include<algorithm>

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

    student_db_provider* st_db_prov = nullptr;

    student_db* db = nullptr;

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
        int com = Input<int>(us("Виберіть опцію: \n\t1) Переглянути базу данних - натисніть 1. \n\t2) Додати нового студента - натисніть 2. \n\t3) Редагування Студента - натисніть 3. \n\t4) Видалити студента - натисніть 4"), to_int_converter,
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

        int sort_com = 0;
        
        int id = -1;

        Student s;

        Student* s_ptr = nullptr;

        switch (com)
        {
            case 1://View Data Base
                
                system("cls");

                std::cout << "Student Database\n" << std::endl;

                students = db->GetDataSet();

                lab5_functions::Display(students);
               
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

                    std::function<bool(const Student&, const Student&)> sort_pred = nullptr;

                    switch (sort_com)
                    {
                    case 1: //Sort by Surename

                        sort_pred = Pred_Surename;

                        break;                    

                    case 2:

                        sort_pred = Pred_Name;

                        break;

                    case 3:

                        sort_pred = Pred_Lastname;

                        break;

                    case 4:

                        sort_pred = Pred_Age;

                        break;

                    case 5:

                        sort_pred = Pred_Group;

                        break;

                    case 6:

                        sort_pred = Pred_Mark;

                        break;
                    }

                    system("cls");

                    sort(students.begin(), students.end(), sort_pred);

                    Display(students);

                } while (sort_com != 7);
                
            break;

            case 2://Add new Student

                system("cls");

                std::cout << "Student Database\n" << std::endl;

                cin >> s;

                db->Add(s);

                db->Save();

                break;

            case 3://Edit Student

                //1) Find Student by Id

                system("cls");

                std::cout << "Student Database\n" << std::endl;

                id = Input<int>(us("Введіть ідентифікатор Студента (Указано як поле Id)"), to_int_converter);

                s_ptr = db->Search([id](const Student& ent)-> bool { return ent.GetId() == id; });

                if (s_ptr != nullptr)
                {
                    cout << *s_ptr<< endl;

                    cout << "\n";

                    //Edit
                    // 
                    //                     
                }
                else
                {
                    cout << us("Студента з таким ай ді не існує!") << endl;
                }
                    
                break;

            case 4:

                system("cls");

                std::cout << "Student Database\n" << std::endl;

                id = Input<int>(us("Введіть ідентифікатор Студента (Указано як поле Id) Для видалення."), to_int_converter);

                s_ptr = db->Search([id](const Student& ent)-> bool { return ent.GetId() == id; });

                if (s_ptr != nullptr)
                {
                    cout << *s_ptr << endl;

                    cout << "\n";
                 
                    //Delete

                }
                else
                {
                    cout << us("Студента з таким ай ді не існує!") << endl;
                }

                /*db->Delete(*s_ptr);

                db->Save();*/

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

