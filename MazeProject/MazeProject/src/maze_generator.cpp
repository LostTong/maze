#include "maze_generator.h"
#include "cell.h"
#include "path.h"

#include <unordered_set>
/*#include <iostream>*/

namespace maze
{
	std::unique_ptr<Maze> MazeGenerator::generate()
	{
		// init
    	std::unique_ptr<Maze> maze(new Maze(width, height));
		std::mt19937 mt(seed);

		Maze tmp_maze(width, height);
		std::unordered_set<Cell *> visited_cells;
		bool is_solve = depth_search(tmp_maze, mt, (void *)&visited_cells);
		if (is_solve) {
			build_solve_path(tmp_maze);
		}

    	Cell *current_cell = nullptr, *next_cell = nullptr;

        /* The current pathway stack : I didn't use  SolvingStrategy::build_solved_pathway() because it is less
        efficient to store a cell-pathway map which has to be probed and navigated compared
        to the use of a sole pathway stack which is possible with this strategy */
    	std::stack<maze::Cell *> path_stack;
		                                 
    	unsigned long number_of_total_cells = height * width;
    	unsigned long number_of_visited_cells = 0;

    	/* Starting at top left */
    	path_stack.push(maze->get_cell(0, 0));
    	number_of_visited_cells++;

    	while(number_of_visited_cells < number_of_total_cells)
    	{
        	current_cell = path_stack.top();
        	unsigned current_y_pos = current_cell->get_y_position();
        	unsigned current_x_pos = current_cell->get_x_position();

        	/* Get unvisited neighbouring cells */
        	std::vector<maze::Cell *> unvisited_neighbours;
        	/* One above - check because cant be negative*/
			if (current_y_pos != 0)
        	{
				maze::Cell * cell_above = maze->get_cell(current_x_pos, current_y_pos - 1);
            	if(cell_above != nullptr)
                	if(!cell_above->has_pathway())
                    	unvisited_neighbours.push_back(cell_above);
        	}
        
        	/* One below */

			maze::Cell * cell_below = maze->get_cell(current_x_pos, current_y_pos + 1);
        	if(cell_below != nullptr)
            	if(!cell_below->has_pathway())
                	unvisited_neighbours.push_back(cell_below);
            

        	/* One left - check because unsigned cant be negative*/
			if (current_cell->get_x_position() != 0)
        	{
				maze::Cell * cell_left = maze->get_cell(current_x_pos - 1, current_y_pos);
            	if(cell_left != nullptr)
                	if(!cell_left->has_pathway())
                    	unvisited_neighbours.push_back(cell_left);
        	}
        
        	/* One right */
			maze::Cell * cell_right = maze->get_cell(current_x_pos + 1, current_y_pos);
        	if(cell_right != nullptr)
            	if(!cell_right->has_pathway())
                	unvisited_neighbours.push_back(cell_right);

       		/* Choose path to make with random unvisited neighbours */
        	if(unvisited_neighbours.empty())
        	{
            	/* No more unvisited */
            	path_stack.pop();
            	continue;
        	}

        	/* Randomly select path */
        	unsigned random_index = mt() % unvisited_neighbours.size();
        	/* Decide a path */
        	next_cell = unvisited_neighbours[random_index];

			maze->add_path(current_cell, next_cell);
        	path_stack.push(next_cell);
        	number_of_visited_cells++;

            current_cell = nullptr;
    	}

    	return maze;
	}

	bool MazeGenerator::depth_search(Maze &maze, std::mt19937 &mt, void *visited_cells_ptr) {
		// search cell stack
		if (unvisited_cells.empty()) {
			return false;
		}
		// new start cell
		Cell *start_cell = unvisited_cells.top();
		std::unordered_set< Cell*> visited_cells = *(std::unordered_set< Cell*> *)visited_cells_ptr;
		visited_cells.insert(start_cell);
		// is exit cell
		if (start_cell == maze.get_exit_cell()) {
			return true;
		}
		/* up, down, left, right */
		unsigned x_pos = start_cell->get_x_position();
		unsigned y_pos = start_cell->get_y_position();
		Cell *cell_up = maze.get_cell(x_pos, y_pos - 1);
		Cell *cell_down = maze.get_cell(x_pos, y_pos + 1);
		Cell *cell_left = maze.get_cell(x_pos - 1, y_pos);
		Cell *cell_right = maze.get_cell(x_pos + 1, y_pos);
		std::vector<Cell *> cell_vec;
		cell_vec.push_back(maze.get_cell(x_pos, y_pos - 1));
		cell_vec.push_back(maze.get_cell(x_pos, y_pos + 1));
		cell_vec.push_back(maze.get_cell(x_pos - 1, y_pos));
		cell_vec.push_back(maze.get_cell(x_pos + 1, y_pos));	
		// add unvisited cells by mt::19937
		while (true) {
			if (cell_vec.empty()) {
				break;
			}
			int idx = mt() % (cell_vec.size());
			Cell *cell = cell_vec[idx];
			if (cell != nullptr && visited_cells.find(cell) != visited_cells.end()) {
				unvisited_cells.push(cell);
				cell->prev_cell = start_cell;
			}
			cell_vec.erase(cell_vec.begin() + idx);
		}
		return depth_search(maze, mt, visited_cells_ptr);

	}

	void MazeGenerator::build_solve_path(Maze &maze) {
		solve_paths.clear();
		Cell *curr_cell = maze.get_exit_cell();
		while (true) {
			Cell *prev_cell = curr_cell->prev_cell;
			if (prev_cell == nullptr) {
				break;
			}
			Path *path = new Path(prev_cell, curr_cell);
			solve_paths.push_back(path);
		}
		return;
	}
}

