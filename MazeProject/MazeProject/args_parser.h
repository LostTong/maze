#pragma once

#include <string>

namespace maze {
	class ArgsParser
	{
	public:
		ArgsParser();
		~ArgsParser();

	public:
		const std::string load_binary_flag = "--lb";
		const std::string save_binary_flag = "--sb";
		const std::string save_svg_flag = "--sv";
		const std::string generate_maze_flag = "--g";

	private:
		std::string load_binary_file;
		std::string save_binary_file;
		std::string save_svg_file;
		
		bool generate_maze_enable;
		unsigned generate_maze_seed;
		unsigned generate_maze_width;
		unsigned generate_maze_height;

	public:
		void init();
		bool parse(int argc, char * argv[]);
	};
}


