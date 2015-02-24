#pragma once
#include <iostream>

using namespace std;

#ifndef _RU_RU
#define ERR_INCORRECT_INTEGER_VALUE "Incorrect integer data"
#define ERR_NOT_GE_ZERO				"Value should be great or equal of zero"
#define ERR_NOT_LE_VALUE			"Value should be less or equal of value: "
#define ERR_NOT_LESS_VALUE			"Value should be less of value: "
#define ERR_OBJECT_NOT_CREATED		"Object not created"
#define ERR_TASK_ALREADY_EXECUTED	"Task has been executed already"
#define INF_EMPTY_RESULT			"<Empty set>"
#define ERR							"Error"
#else
#define ERR_INCORRECT_INTEGER_VALUE "Неверный тип Integer"
#define ERR_NOT_GE_ZERO				"Значение должно быть больше или равно нулю"
#define ERR_NOT_LE_VALUE			"Значение должно быть меньше или равно: "
#define ERR_NOT_LESS_VALUE			"Значение должно быть меньше: "
#define ERR_OBJECT_NOT_CREATED		"Объект не создан"
#define ERR_TASK_ALREADY_EXECUTED	"Задание уже выполненено"
#define INF_EMPTY_RESULT			"<Пустое множество>"
#define ERR							"Ошибка"

#endif

namespace alg_ds
{
	static class in_out_helper
	{
	public:
		static int input_integer(const char *msg, char **errmsg)
		{
			cout << msg;
			**errmsg = NULL;

			cin.clear();
			cin.sync(); 

			int result = 0;
			cin >> result;

			if (cin.eof())
			{
				cin.clear();
				cin.sync();

				return result;
			}

			if (cin.fail())
			{
				if (!cin.eof())
					strcpy_s(*errmsg, BUFSIZ, ERR_INCORRECT_INTEGER_VALUE);

				cin.clear();
				cin.sync();
			}

			cin.clear();
			cin.sync();

			return result;
		}

		static void out_error(const char *errmsg)
		{
			if (errmsg)
				cout << ERR << ": " << errmsg << endl;
		}

		static void out_msg(const char *msg)
		{
			if (msg)
				cout << msg << endl;
		}
	};
}