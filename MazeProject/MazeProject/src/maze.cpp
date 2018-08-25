#include "maze.h"

#include <iostream>

namespace maze
{
	Maze::Maze(unsigned height, unsigned width){
		// create maze cells
		for(unsigned i = 0; i < height; i++){
			// rows
			std::vector<maze::Cell *> cur_row;

			// columns
			for(int j = 0; j < width; j++)
			{
				Cell *cell = new Cell(i, j);
				cur_row.push_back(cell);
			}
			cells.push_back(cur_row);
		}

		this->width = width;
		this->height = height;
	}

	Cell *Maze::get_cell(unsigned x_pos, unsigned y_pos){
		if(x_pos >= width)
		{
			return nullptr;
		}

		if(y_pos >= height)
		{
			return nullptr;
		}

		return cells[x_pos][y_pos];
	}

	void Maze::add_path(Cell *start_cell, Cell *end_cell){
		if (start_cell == nullptr || end_cell == nullptr) {
			std::cerr << "Maze add path cells invalid." << std::endl;
			return;
		}

		Path *path =  new Path(start_cell, end_cell);
		// cell: add path
		start_cell->add_path(path);
		end_cell->add_path(path);
		// paths: add path
		paths.push_back(path);
	}

	Maze::~Maze(){

		// delete cells
		for(unsigned i = 0; i < height; i++){
			// row
			std::vector<maze::Cell *> current_row = cells[i];
			// column
			for(unsigned j = 0; j < width; j++)
			{
				delete current_row[j];
			}
		}

		// delete paths
		for(unsigned i = 0; i < paths.size(); i++){
			delete paths[i];
		}
	}

}
