#include "non_rect_matrix.h"

using namespace alg_ds;

non_rect_matrix::non_rect_matrix()
	: _m(0), _n(NULL), _matrix(NULL), is_created(false), is_changed(false)
{
	// randomize
	srand(time(NULL));
}

non_rect_matrix::non_rect_matrix(int m, int *n)
{
	if (m < 0)
	{
		in_out_helper::out_error(ERR_NOT_GE_ZERO);
		return;
	}

	this->_m = m;
	this->_n = new int[m];
	this->_matrix = new int*[_m];

	for (int i = 0; i < m; i++)
	{
		if (n[i] < 0)
		{
			in_out_helper::out_error(ERR_NOT_GE_ZERO);
			this->_delete();
			return;
		}

		this->_matrix[i] = new int[n[i]];
	}
}

non_rect_matrix::non_rect_matrix(const non_rect_matrix& _src)
{
	this->_m = _src._m;
	this->_n = new int[_m];
	this->_matrix = new int*[_m];

	for (int i = 0; i < _m; i++)
	{
		this->_n[i] = _src._n[i];
		this->_matrix[i] = new int[_src._n[i]];
	}

	for (int i = 0; i < _m; i++)
		for (int j = 0; j < _n[i]; j++)
			this->_matrix[i][j] = _src._matrix[i][j];

	this->is_created = _src.is_created;
	this->is_changed = _src.is_changed;
}

bool non_rect_matrix::_create()
{
	if (this->_matrix)
		this->_delete();

	char *errmsg = new char[BUFSIZ];

	int m;
	m = in_out_helper::input_integer("Input m: ", (char **)&errmsg);

	if (m < 0)
		strcpy_s(errmsg, BUFSIZ, ERR_NOT_GE_ZERO);

	if (*errmsg)
	{
		in_out_helper::out_error(errmsg);
		delete[] errmsg;
		return false;
	}

	this->_m = m;
	this->_n = new int[_m];
	for (int i = 0; i < _m; i++)
	{
		ostringstream _out;
		_out << "Input n[" << setw(2) << i << "]: ";
		this->_n[i] = in_out_helper::input_integer(_out.str().c_str(), (char **)&errmsg);
		
		if (_n[i] < 0)
			strcpy_s(errmsg, BUFSIZ, ERR_NOT_GE_ZERO);

		if (*errmsg)
		{
			in_out_helper::out_error(errmsg);
			delete[] errmsg;
			delete[] _n;

			_n = NULL;
			return false;
		}
	}

	this->_matrix = new int*[_m];
	for (int i = 0; i < _m; i++)
		this->_matrix[i] = new int[_n[i]];

	this->_randomize_matrix();

	delete[] errmsg;
	return true;
}

void non_rect_matrix::_delete()
{
	if (!this->_m || !this->_matrix)
		return;

	for (int i = 0; i < _m; i++)
		delete[] this->_matrix[i];
	delete[] this->_matrix;

	if (this->_n)
		delete[] this->_n;

	this->_matrix = NULL;
	this->_n = NULL;
	this->_m = 0;
}

void non_rect_matrix::_view()
{
	if (!this->_m)
	{
		in_out_helper::out_msg(INF_EMPTY_RESULT);
		return;
	}

	for (int i = 0; i < _m; i++)
	{
		cout << "[" << setw(2) << i << "] => ";
		if (!_n[i])
			in_out_helper::out_msg(INF_EMPTY_RESULT);
		else
		{
			for (int j = 0; j < _n[i]; j++)
				cout << right << setw(5) << this->_matrix[i][j];
			cout << endl;
		}
	}
}

void non_rect_matrix::_randomize_matrix()
{
	if (!_n || !_m)
		return;

	for (int i = 0; i < _m; i++)
		for (int j = 0; j < _n[i]; j++)
			this->_matrix[i][j] = rand() % MAX_RAND_VALUE;
}

non_rect_matrix::~non_rect_matrix()
{
	this->_delete();
}

void non_rect_matrix::create()
{
	this->is_created = this->_create();
}

void non_rect_matrix::view(char *msg)
{
	in_out_helper::out_msg(msg);
	this->_view();
}

bool non_rect_matrix::_exec_task()
{
	if (!_n || !_m)
		return false;

	non_rect_matrix t_nr_matrix(*this);

	for (int i = 0; i < _m; i++)
	{
		if (_n[i])
		{
 			t_nr_matrix._n[i] = 0;
			for (int j = 0; j < _n[i]; j++)
			{
				if (this->_is_even_digits(_matrix[i][j]))
					t_nr_matrix._n[i]++;
				else
					t_nr_matrix._matrix[i][j] = REMOVED_VALUE;
			}
		}
	}

	for (int i = 0; i < _m; i++)
	{
		delete[]this->_matrix[i];

		this->_matrix[i] = new int[t_nr_matrix._n[i]];
		if (t_nr_matrix._n[i])
		{
			for (int j = 0, k = 0; j < _n[i]; j++)
			{
				if (t_nr_matrix._matrix[i][j] != REMOVED_VALUE)
					this->_matrix[i][k++] = t_nr_matrix._matrix[i][j];
			}
		}

		this->_n[i] = t_nr_matrix._n[i];
	}

	return true;
}

void non_rect_matrix::exec_task()
{
	this->is_changed = this->_exec_task();
}

bool non_rect_matrix::_is_even_digits(int a)
{
	bool result = true;

	do
	{
		result &= !((a % 10) % 2);
	} while (a /= 10);

	return result;
}