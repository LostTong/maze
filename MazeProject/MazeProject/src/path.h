#pragma once

#include "cell.h"
#include <vector>
#include <functional>



namespace maze
{
	class Cell;

	class Path
	{
		public:
			Path(Cell *start_cell, Cell *end_cell): start_cell(start_cell),
				end_cell(end_cell), is_exit_path(false) {};
			~Path() {};

			// maze::Cell * get_first_cell() { return cell1; };
			Cell *get_next_cell(maze::Cell *cell);

		public:
			Cell *start_cell, *end_cell;
			bool is_exit_path;
	};
}

/* hash */
namespace std
{
	template <>
	struct hash<maze::Path *>
	{
		std::size_t operator()(maze::Path * const & pathway) const noexcept{
			return std::hash<std::size_t>()((std::size_t)pathway);
		}
	};
}
