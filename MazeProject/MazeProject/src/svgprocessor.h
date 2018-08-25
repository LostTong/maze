#pragma once

#include "maze.h"
//#include "persistencestrategy.h"
#include "mazefactory.h"
#include <fstream>
#include <string>
#include <memory>
#include <iostream>

#define CELL_SIZE_PIXELS 20
#define WALL_SIZE_FACTOR 0.1
#define PATHWAY_COLOR "rgb(255,255,255)"
#define SOLVED_PATHWAY_COLOR "rgb(255,0,0)"

namespace maze
{
	class SVGSave : public MazeFactory
	{
		maze::Maze * maze;
		std::string file_path;

		void output_pathway(maze::Pathway & pathway, unsigned offset, std::fstream & output);

		public:
			SVGSave(maze::Maze & maze, std::string file_path) : maze(&maze), file_path(file_path) {};
			virtual void persist_maze();

			std::unique_ptr<maze::Maze> make_maze(){ return nullptr; };
			void BinaryLoad(std::string file_path) {};
			void BinarySave(maze::Maze & maze, std::string file_path) {};
			


			const static unsigned int WALL_WIDTH = (unsigned)((double) WALL_SIZE_FACTOR * CELL_SIZE_PIXELS);
			const static unsigned int PATH_WIDTH = CELL_SIZE_PIXELS - 2 * WALL_WIDTH;
	};
}