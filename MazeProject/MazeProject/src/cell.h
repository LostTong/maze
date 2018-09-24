#pragma once

#include "path.h"
#include <vector>

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

			bool operator < (const Cell &cell) {
				if (this->x_pos < cell.x_pos) {
					return true;
				}
				return this->y_pos < cell.y_pos;
			}

			bool operator > (const Cell &cell) {
				return !(*this < cell);
			}

			bool operator == (const Cell &cell) {
				return this->x_pos == cell.x_pos && this->y_pos == cell.y_pos;
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
} 


