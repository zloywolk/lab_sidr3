#pragma once
#include <clocale>

#include "non_rect_matrix.h"

#ifndef _RU_RU
#define MNU_EXIT	"0 - Exit"
#define MNU_CREATE	"1 - Create"
#define MNU_VIEW	"2 - View"
#define MNU_EXEC	"3 - Exec task"
#else
#define MNU_EXIT	"0 - Выход"
#define MNU_CREATE	"1 - Создать"
#define MNU_VIEW	"2 - Просмотр"
#define MNU_EXEC	"3 - Выполнить задание"
#endif

namespace alg_ds
{
	class cli_application
	{
	private:
		const static int n_a = 4;
		static void(*_actions[n_a])(non_rect_matrix&);
		static const char *_menu_items[n_a];
		non_rect_matrix _source;

		static void create(non_rect_matrix&);
		static void view(non_rect_matrix&);
		static void exec(non_rect_matrix&);
		static void exit(non_rect_matrix&);

		void _start();
		void _show_menu();
		int _get_command();
	public:
		void run();
		cli_application();
		~cli_application();
	};
}