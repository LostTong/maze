#include "cell.h"

namespace maze
{
	Cell::Cell(unsigned x_pos, unsigned y_pos)
	{
		this->x_pos = x_pos;
		this->y_pos = y_pos;
	}

	void Cell::add_path(Path *pathway)
	{
		paths.push_back(pathway);
	}
}
