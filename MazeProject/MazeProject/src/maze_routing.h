#pragma once

#include <vector>
#include <iostream>

#include "maze.h"
#include "cell.h"
#include "path.h"

using namespace maze;

class MazeRouting {
public:
	MazeRouting(maze::Maze *maze);
	~MazeRouting();

	void path_finding();

private:
	bool solve_path(Cell *cur_cell, Cell *exit_cell);

public:
	maze::Maze *maze;
	std::vector<Path *> solved_paths;
	bool has_solve_path;
};