#include "path.h"

namespace maze {
	Cell * maze::Path::get_next_cell(Cell * cell)
	{
		if (cell == start_cell) {
			return end_cell;
		}
		else if (cell == end_cell) {
			return start_cell;
		}
		return nullptr;
	}

}

