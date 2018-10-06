#include "cell.h"

namespace maze
{
	Cell::Cell(unsigned x_pos, unsigned y_pos)
	{
		this->x_pos = x_pos;
		this->y_pos = y_pos;
		prev_cell = nullptr;
	}

	void Cell::add_path(Path *pathway)
	{
		paths.push_back(pathway);
	}

	bool Cell::is_connect_cell(Cell *cell) {
		for (auto *path : *(get_paths())) {
			if (path->start_cell == cell || path->end_cell == cell) {
				return true;
			}
		}
		return false;
	}
}
