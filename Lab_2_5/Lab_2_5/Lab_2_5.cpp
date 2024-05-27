// Lab_2_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "StudentDb.h"
#include "lab5_funcs.h"
#include <fstream>
#include <crtdbg.h>
#include<algorithm>


std::string m_path_to_file = "../Data/Students.txt";

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
        std::cout << er.what() << endl;
    }
   

#pragma endregion

    do
    {
        int com = Input<int>(us("������� �����: \n\t1) ����������� ���� ������ - �������� 1. \n\t2) ������ ������ �������� - �������� 2. \n\t3) ����������� �������� - �������� 3. \n\t4) �������� �������� - �������� 4"), to_int_converter,
            [](string& inp, us& error)->bool
            {
                int c = stoi(inp);

                if (c < 0)
                {
                    error = "������� ���� �������!";

                    return false;
                }
                return true;
            });

        vector<Student> students;

        int sort_com = 0;
        
        int id = -1;

        Student s;

        Student* s_ptr = nullptr;

        string new_field;

        int new_int = 0;

        float new_mark = 0.0;

        switch (com)
        {
            case 1://View Data Base
                
                system("cls");

                std::cout << "Student Database\n" << std::endl;

                students = db->GetDataSet();

                lab5_functions::Display(students);
               
                do
                {
                    sort_com = Input<int>(us("����������: \n\t1) �� �������� - �������� 1. \n\t2) �� ������ - �������� 2. \n\t3) �� ��-������� - �������� 3. \n\t4) �� ³��� - �������� 4. \n\t5) �� ������� - �������� 5. \n\t6) �� ������� - �������� 6. \n\t7) ����� � ������ ��������� - �������� 7."), to_int_converter,
                        [](string& inp, us& error)->bool
                        {
                            int c = stoi(inp);

                            if (c < 0 && c > 7)
                            {
                                error = "������� ���� �������!";

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

                std::cin >> s;

                db->Add(s);

                db->Save();

                break;

            case 3://Edit Student

                //1) Find Student by Id

                system("cls");

                std::cout << "Student Database\n" << std::endl;

                id = Input<int>(us("������ ������������� �������� (������� �� ���� Id): "), to_int_converter);

                s_ptr = db->Search([id](const Student& ent)-> bool { return ent.GetId() == id; });

                if (s_ptr != nullptr)
                {
                    std::cout << *s_ptr<< endl;

                    std::cout << "\n";

                    int field = Input<int>(us("��� ���� �������� �� ������ ������������? \n\t1) ������� - ������ 1. \n\t2) ��\"� - ������ 2. \n\t3) ��-������� - ������ 3. \n\t4) ³� - ������ 4. \n\t5) ������ - ������ 5. \n\t6) ������ - ������ 6."),
                        to_int_converter,
                        [](string& inp, us& error)->bool
                        {
                            int temp = stoi(inp);

                            if (temp < 0 && temp > 6)
                            {
                                std::cout << us("������ ������� ���� ��� �����������, ��������� ��:!") << endl;

                                return false;
                            }

                            return true;
                        });

                    if (field == 1)
                    {
                        do
                        {
                            std::cout << us("������ ���� �������: (�� �������� �����)") << endl;

                            std::cin >> new_field;

                        } while (!AcceptInput<string>(new_field));
                        
                        s_ptr->SetSurename(us(new_field));
                    }
                    else if (field == 2)
                    {
                        do
                        {
                            std::cout << us("������ ���� ��\"�: (�� �������� �����)") << endl;

                            std::cin >> new_field;

                        } while (!AcceptInput<string>(new_field));

                        s_ptr->SetName(us(new_field));
                    }
                    else if (field == 3)
                    {
                        do
                        {
                            std::cout << us("������ ���� ��-�������: (�� �������� �����)") << endl;

                            std::cin >> new_field;

                        } while (!AcceptInput<string>(new_field));

                        s_ptr->SetLastname(us(new_field));
                    }
                    else if (field == 4)
                    {
                        do
                        {
                            new_int = Input<int>(us("������ ����� �� ��������: (�� �������� �����)"),
                                to_int_converter,
                                [](std::string& inp, us& error)->bool
                                {
                                    int temp = std::stoi(inp);

                                    if (temp < 0)
                                    {
                                        error = "³� �� ���� ���� ��\"�����!";
                                        return false;
                                    }
                                    else if (temp > 100)
                                    {
                                        error = "³� �� ���� ���� ����� 100!";
                                        return false;
                                    }

                                    return true;
                                });

                        } while (!AcceptInput<int>(new_int));

                        s_ptr->SetAge(new_int);
                    }
                    else if (field == 5)
                    {
                        do
                        {
                            new_int = Input<int>(us("������ ���� ������ ��������: (�� �������� �����)"),
                                to_int_converter,
                                [](std::string& inp, us& error)->bool
                                {
                                    int temp = std::stoi(inp);

                                    if (temp < 0)
                                    {
                                        error = "������ �� ���� ���� ��\"�����!";
                                        return false;
                                    }

                                    return true;
                                });

                        } while (!AcceptInput<int>(new_int));

                        s_ptr->SetGroup(new_int);
                    }
                    else if (field == 6)
                    {
                        do
                        {
                            new_mark = Input<float>(us("������ ���� ������ ��������: (�� �������� �����)"),
                                to_int_converter,
                                [](std::string& inp, us& error)->bool
                                {
                                    float temp = std::stof(inp);

                                    if (temp < 0)
                                    {
                                        error = "������ �� ���� ���� ��\"����!";
                                        return false;
                                    }

                                    return true;
                                });

                        } while (!AcceptInput<float>(new_mark));

                        s_ptr->SetMark(new_mark);
                    }
                    
                    db->Save();
                    
                    std::cout << us("����������� �������� ���������!") << endl;
                }
                else
                {
                    std::cout << us("�������� � ����� �� � �� ����!") << endl;
                }
                    
                break;

            case 4:

                system("cls");

                std::cout << "Student Database\n" << std::endl;

                id = Input<int>(us("������ ������������� �������� (������� �� ���� Id) ��� ���������."), to_int_converter);

                s_ptr = db->Search([id](const Student& ent)-> bool { return ent.GetId() == id; });

                if (s_ptr != nullptr)
                {
                    std::cout << *s_ptr << endl;

                    std::cout << "\n";
                 
                    if (AcceptCommand(us("ϳ�������� ������� ��������� ��������.")))
                    {
                        db->Delete(*s_ptr);

                        db->Save();
                    }
                    else
                    {
                        std::cout << us("��������� �������!") << std::endl;
                    }
                }
                else
                {
                    std::cout << us("�������� � ����� �� � �� ����!") << endl;
                }               

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

