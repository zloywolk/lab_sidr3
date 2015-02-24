#include "cli_application.h"

using namespace alg_ds;

const char *cli_application::_menu_items[n_a] =
{
	MNU_CREATE,
	MNU_VIEW,
	MNU_EXEC,
	MNU_EXIT
};

void(*cli_application::_actions[n_a])(non_rect_matrix& _src) =
{
	exit,
	create,
	view,
	exec
};

cli_application::cli_application()
{
}

cli_application::~cli_application()
{
}

void cli_application::create(non_rect_matrix& _src)
{
	in_out_helper::out_msg("=> Create new non-rectangular matrix");
	_src.create();
	if (_src.is_created)
	{
		in_out_helper::out_msg("=> Matrix created");
		_src.view("=> Created source matrix");
	}
	else
		in_out_helper::out_error(ERR_OBJECT_NOT_CREATED);
}

void  cli_application::view(non_rect_matrix& _src)
{
	if (_src.is_created)
	{
		if (!_src.is_changed)
			_src.view("=> Source matrix");
		else
			_src.view("=> New matrix (with only even digits)");
	}
	else
		in_out_helper::out_error(ERR_OBJECT_NOT_CREATED);
}

void cli_application::exec(non_rect_matrix& _src)
{
	in_out_helper::out_msg("=> Run task by student variant");
	if (_src.is_created)
	{
		_src.view("=> Source matrix");
		if (!_src.is_changed)
		{
			_src.exec_task();
			in_out_helper::out_msg("=> Task successfuly completed");
			_src.view("=> New matrix (with only even digits)");
		}
		else
			in_out_helper::out_error(ERR_TASK_ALREADY_EXECUTED);
	}
	else
		in_out_helper::out_error(ERR_OBJECT_NOT_CREATED);
}

void  cli_application::exit(non_rect_matrix& _src)
{
	in_out_helper::out_msg("Exit from application\nBye....");
}

void cli_application::_start()
{
	int n = 0;
	do
	{
		_show_menu();
		n = this->_get_command();
		this->_actions[n](this->_source);
	} while (n);
}

void cli_application::run()
{
#ifdef _RU_RU
	setlocale(LC_ALL, "Russian");
#endif
	this->_start();
}

void cli_application::_show_menu()
{
	in_out_helper::out_msg("MAIN MENU\n");
	for (int i = 0; i < n_a; i++)
		in_out_helper::out_msg(_menu_items[i]);
}

int cli_application::_get_command()
{
	char *errmsg = new char[BUFSIZ];
	int n = 0;
	bool is_err = false;

	do
	{
		n = in_out_helper::input_integer("Input your choise: ", (char **)&errmsg);

		if (*errmsg)
		{
			in_out_helper::out_error(errmsg);
			is_err = true;
		}

		if (n < 0)
		{
			in_out_helper::out_error(ERR_NOT_GE_ZERO);
			is_err = true;
		}
		else if (n >= n_a)
		{
			ostringstream _out;
			_out << ERR_NOT_LE_VALUE << n_a;

			in_out_helper::out_error(_out.str().c_str());
			is_err = true;
		}
		else is_err = false;
	} while (is_err);

	delete[] errmsg;
	return n;
}