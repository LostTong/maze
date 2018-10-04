#pragma once

#include "path.h"
#include <vector>
#include <iostream>

namespace maze
{
	class Path;

	class Cell
	{
		public:
			Cell(unsigned y_position, unsigned x_position);
			~Cell() {};

			inline unsigned get_x_position() { return x_pos; };
			inline unsigned get_y_position() { return y_pos; }
			inline std::vector<Path *> * get_paths() { return &paths;};
			inline bool has_path() { return !paths.empty();};
			void add_path(Path *pathway);

			bool operator < (const Cell &cell) const{
				if (this->x_pos != cell.x_pos) {
					return this->x_pos < cell.x_pos;
				}
				return this->y_pos < cell.y_pos;
			}

			bool operator > (const Cell &cell) const{
				return !(*this < cell);
			}


	public:
		unsigned x_pos, y_pos;
		std::vector<Path *> paths;
		Cell *prev_cell;
	};
}

/* hash */
namespace std{
template <>
struct hash<maze::Cell *>
{
	std::size_t operator()(maze::Cell * const & cell) const noexcept
	{
		return std::hash<std::size_t>()((std::size_t)cell);
	}
};

template <>
struct equal_to<maze::Cell *>
{
	bool operator()(maze::Cell *cell1, maze::Cell *cell2) const noexcept
	{
		return (cell1->get_x_position() == cell2->get_x_position() && cell1->get_y_position() == cell2->get_y_position());
	}
};
} 


