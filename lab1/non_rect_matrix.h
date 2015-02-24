#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdlib>

#include <ctime>

#include "in_out_helper.h"

#define MAX_RAND_VALUE 255
#define REMOVED_VALUE -1

using namespace std;

namespace alg_ds
{
	class non_rect_matrix
	{
	private:
		int _m;
		int *_n;
		int **_matrix;

		bool _create();
		void _delete();

		void _view();
		void _randomize_matrix();

		bool _exec_task();
		bool _is_even_digits(int);

		non_rect_matrix(int, int *);
	public:
		bool is_created;
		bool is_changed;

		non_rect_matrix();
		non_rect_matrix(const non_rect_matrix&);
		~non_rect_matrix();

		void create();
		void view(char *);
		void exec_task();
	};
}

