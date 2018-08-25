#pragma once
#include "maze.h"
#include "mazefactory.h"
#include <memory>
#include <fstream>

namespace maze
{
	class BinaryProcessor : public MazeFactory
	{
		std::string file_path;
		maze::Maze * maze;
	public:
		void BinaryLoad(std::string file_path)
		{
			this->file_path = file_path;
		}
		void BinarySave(maze::Maze & maze, std::string file_path)
		{
			this->maze = &maze,
			this->file_path = file_path;
		}
		BinaryProcessor(maze::Maze * maze, std::string file_path)
		{
			this->maze = maze,
			this->file_path = file_path;
		}
		virtual std::unique_ptr<maze::Maze> make_maze() override;
		virtual void persist_maze() override;
	};
}