#include "svg_save.h"

namespace maze
{
	void maze::SVGSave::save_svg_file(){
		std::fstream output(file_path, std::fstream::out | std::fstream::trunc);
		if(!output.is_open())
		{
			std::cout << "Could not open file" << std::endl;
			return;
		}

 		
		// header
 		int offset = wall_width * 2;
		int box_width = cell_size * maze->width + offset;
		int box_height = cell_size * maze->height + offset;
		output << "<svg width='" << box_width << "' ";
		output << "height='" << box_height << "' ";
		output << "xmlns='http://www.w3.org/2000/svg'>" << "\n";

		output << "<rect width='" << box_width << "' height='" << box_height;
		output << "' style='fill: black' />" << "\n";

		std::vector<maze::Path *> solved_pathway;
		std::vector<maze::Path *> unsolved_pathway;

		for(maze::Path *pathway : *maze->get_paths())
		{
			if(pathway->is_exit_path)
				solved_pathway.push_back(pathway);
			else
				unsolved_pathway.push_back(pathway);
		}

		//save path
		for(auto * path: unsolved_pathway)
		{
			save_path(*path, offset, output);
		}
 		for(auto * path: solved_pathway)
		{
			save_path(*path, offset, output);
		}

		// entry and exit
 		bool solved = !solved_pathway.empty();
		output << "<rect style='fill:";
 			if(solved)
 				output << path_color;
 			else
 				output << path_color;
		output << "' x='0' y='" << offset << "' width='" << path_width;
		output << "' height='" << path_width << "'/>" << "\n";

		output << "<rect style='fill:";
 			if(solved)
 				output << path_color;
 			else
 				output << path_color;
		output << "' x='" << (box_width - path_width - offset)  << "' y='";
		output << (box_height - path_width - offset) << "' width='";
		output << path_width + offset;
		output << "' height='" << path_width << "'/>" << "\n";

		output << "</svg>" << "\n";
		output.close();
	}


	void maze::SVGSave::save_path(maze::Path &path, unsigned offset, std::fstream & output)
	{
		int x, y;
		int path_width, path_height;

		maze::Cell * first_cell = path.start_cell;
		maze::Cell * second_cell = path.end_cell;

		int x1 = path.start_cell->get_x_position();
		int y1 = path.start_cell->get_y_position();
		int x2 = path.end_cell->get_x_position();
		int y2 = path.end_cell->get_y_position();

 			/* Dimentions depends on the edges/pathways - some in reverse order 
 			(right to left etc) so first we determine which cell is first,
 			then we can work out how to make the rectangle */
 			if (x1 < x2)
 			{
 				x = x1 * cell_size + offset;
 				path_width = 2 * cell_size - offset;
					/* (spanning over two cells) */
 			}
 			else if (x1 > x2)
 			{
 				x = x2 * cell_size + offset;
 				path_width = 2 * cell_size - offset;
					/* (spanning over two cells) */
 			}
 			else /* equal */
 			{
 				x = x2 * cell_size + offset;
 				path_width = cell_size - offset;
					/* (spanning over one cell) */
 			}

 			if (y1 < y2)
 			{
 				y = y1 * cell_size + offset;
 				path_height = 2 * cell_size - offset;
					/* (spanning over two cells) */
 			}
 			else if (y1 > y2)
 			{
 				y = y2 * cell_size + offset;
 				path_height = 2 * cell_size - offset;
					/* (spanning over two cells) */
 			}
 			else /* equal */
 			{
 				y = y2 * cell_size + offset;
 				path_height = cell_size - offset;
					/* (spanning over one cell) */
 			}

 			output << "<rect style='fill:";
 			if(path.is_exit_path)
 				output << path_color;
 			else
 				output << path_color;
 			output << "' ";
 			output << " x='" << x;
 			output << "' y='" << y;
 			output << "' width='" << path_width;
 			output << "' height='" << path_height << "'/>" << "\n";
 		}

 	}
