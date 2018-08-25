#include "binaryprocessor.h"
#include <iostream>
namespace maze
{
	/* Generates a maze using a binary file */
	std::unique_ptr<maze::Maze> maze::BinaryProcessor::generate_maze()
	{
		std::fstream binaryFile(file_path, std::fstream::in | std::fstream::binary);

		unsigned width = 0, height = 0, numEdges = 0;


		if (!binaryFile.is_open())
		{
			/* Error opening file */
			OuputLog("Could not open file");
		}

		/* File length */
		binaryFile.seekg(0, binaryFile.end);

		unsigned file_length = binaryFile.tellg();
		binaryFile.seekg(0, binaryFile.beg);


		/* read header info */
		binaryFile.read((char*)&width, sizeof(width));
		binaryFile.read((char*)&height, sizeof(height));
		binaryFile.read((char*)&numEdges, sizeof(numEdges));

		/* Test header info */
		if (width == 0 || height == 0)
		{
			OuputLog("Width or higth is error.");
		}

		/* Check for overflow */
		unsigned check = width * height;
		if (check / height != width)
		{
			OuputLog("Width and/or height too large.");
		}


		/* Initialize maze object */
		std::unique_ptr<maze::Maze> maze(new Maze(height, width));


		unsigned long readEdges = 0;
		/* edges */
		while ((unsigned int)binaryFile.tellg() != file_length)
		{
			unsigned x1 = 0, x2 = 0, y1 = 0, y2 = 0;

			/* Get data from file */
			/* x1 */
			binaryFile.read((char*)&x1, sizeof(x1));
			/* y1 */
			binaryFile.read((char*)&y1, sizeof(y1));
			/* x2 */
			binaryFile.read((char*)&x2, sizeof(x2));
			/* y2 */
			binaryFile.read((char*)&y2, sizeof(y2));

			/*std::cerr << "read edge: cell["<< y1 << "][" << x1 << "] to cell[" <<
			x2 << "][" << y2 << "]\n";*/

			/* Test data */
			std::string message = "";

			if (x1 >= maze->width)
			{
				message = "Edge out of bounds: x1: " + std::to_string(x1);

			}
			else if (x2 >= maze->width)
			{
				message = "\nEdge out of bounds: x2: " + std::to_string(x2);
			}
			else if (y1 >= maze->height)
			{
				message = "\nEdge out of bounds: y1: " + std::to_string(y1);
			}
			else if (y2 >= maze->height)
			{
				message = "\nEdge out of bounds: y2: " + std::to_string(y2);
			}

			if (message != "")
				OuputLog(message.c_str());


			/* Add pathway to maze */
			maze->add_path(maze->get_cell(x1, y1), maze->get_cell(x2, y2));
			readEdges++;
		}
		binaryFile.close();

		if (readEdges < numEdges)
			OuputLog("Missing edges");
		else if (readEdges > numEdges)
		{
			OuputLog("Num edges read: " + readEdges );
			OuputLog("Too many edges");
		}

		return maze;
	}

	void maze::BinaryProcessor::save_maze_file()
	{
		std::fstream output_file(file_path, std::fstream::out | std::fstream::binary | std::fstream::trunc);

		if (!output_file.is_open())
		{
			OuputLog("Could not open file");
		}

		std::vector<maze::Path *> * pathways = maze->get_pathways();

		/* Write headers */
		const unsigned number_edges = pathways->size();
		const unsigned height = maze->width;
		const unsigned width = maze->height;
		output_file.write((char*)&width, sizeof(width));
		output_file.write((char*)&height, sizeof(height));
		output_file.write((char*)&number_edges, sizeof(number_edges));


		/*std::cout << "Width: " << width << ", height: " << height << ", number_edges: ";
		std::cout << number_edges << "\n";*/


		/* Edges/pathways */
		for (maze::Path * pathway : *pathways)
		{
			const unsigned x1 = pathway->start_cell->get_x_position();
			const unsigned y1 = pathway->start_cell->get_y_position();
			const unsigned x2 = pathway->end_cell->get_x_position();
			const unsigned y2 = pathway->end_cell->get_y_position();

			/* x1 */
			output_file.write((char*)&x1, sizeof(x1));
			/* y1 */
			output_file.write((char*)&y1, sizeof(y1));
			/* x2 */
			output_file.write((char*)&x2, sizeof(x2));
			/* y2 */
			output_file.write((char*)&y2, sizeof(y2));
		}
		output_file.close();
	}
}