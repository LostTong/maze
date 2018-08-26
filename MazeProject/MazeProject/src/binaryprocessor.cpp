#include "binaryprocessor.h"
#include <iostream>
namespace maze
{
	/* Determin whether edge is out of bound */
	std::string maze::BinaryProcessor::determin_edge_out_of_bound(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
	{
		std::string message = "";

		if (x1 >= maze->width)
		{
			message = "Error:Edge out of bounds: x1: " + std::to_string(x1);
		}
		else if (y1 >= maze->height)
		{
			message = "\nError:Edge out of bounds: y1: " + std::to_string(y1);
		}
		else if (x2 >= maze->width)
		{
			message = "\nError:Edge out of bounds: x2: " + std::to_string(x2);
		}	
		else if (y2 >= maze->height)
		{
			message = "\nError:Edge out of bounds: y2: " + std::to_string(y2);
		}
		return message;
	}

	/* Generates a maze using a binary file */
	std::unique_ptr<maze::Maze> maze::BinaryProcessor::generate_maze()
	{
		std::fstream binaryFile(file_path, std::fstream::in | std::fstream::binary);

		unsigned width = 0, height = 0, numEdges = 0;


		if (!binaryFile.is_open())
		{
			/* Open file error. */
			OuputLog("Open file error.");
			return nullptr;
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
			OuputLog("Error:Width or higth is error.They must be greater than zero.");
			return nullptr;
		}

		/* Check for overflow */
		unsigned check = width * height;
		if (check / height != width)
		{
			OuputLog("Error:Width or height exceeding the maximum value.");
			return nullptr;
		}


		/* Initialize maze object */
		std::unique_ptr<maze::Maze> maze(new Maze(height, width));


		unsigned long readEdges = 0;
		/* edges */
		while ((unsigned int)binaryFile.tellg() != file_length)
		{
			unsigned x1 = 0, x2 = 0, y1 = 0, y2 = 0;

			/* Get data from file */
			binaryFile.read((char*)&x1, sizeof(x1));
			binaryFile.read((char*)&y1, sizeof(y1));
			binaryFile.read((char*)&x2, sizeof(x2));
			binaryFile.read((char*)&y2, sizeof(y2));

			/* Test data */
			std::string message = determin_edge_out_of_bound(x1, y1, x2, y2);
			if (message != "")
				OuputLog(message.c_str());


			/* Add pathway to maze */
			maze->add_path(maze->get_cell(x1, y1), maze->get_cell(x2, y2));
			readEdges++;
		}
		binaryFile.close();

		if (readEdges < numEdges)
			OuputLog("Error:Missing edges");
		else if (readEdges > numEdges)
		{
			OuputLog("Error:Num edges read: " + readEdges );
			OuputLog("Error:Too many edges");
		}

		return maze;
	}

	void maze::BinaryProcessor::save_maze_file()
	{
		std::fstream output_file(file_path, std::fstream::out | std::fstream::binary | std::fstream::trunc);

		if (!output_file.is_open())
		{
			OuputLog("Error:Could not open file");
			return;
		}

		std::vector<maze::Path *> * pathways = maze->get_paths();

		/* Write headers */
		const unsigned height = maze->width;
		const unsigned width = maze->height;
		const unsigned number_edges = pathways->size();
		
		output_file.write((char*)&width, sizeof(width));
		output_file.write((char*)&height, sizeof(height));
		output_file.write((char*)&number_edges, sizeof(number_edges));

		/* Edges/pathways */
		for (maze::Path * pathway : *pathways)
		{
			const unsigned x1 = pathway->start_cell->get_x_position();
			const unsigned y1 = pathway->start_cell->get_y_position();
			const unsigned x2 = pathway->end_cell->get_x_position();
			const unsigned y2 = pathway->end_cell->get_y_position();

			/* ouput x1 y1 x2 y2*/
			output_file.write((char*)&x1, sizeof(x1));
			output_file.write((char*)&y1, sizeof(y1));
			output_file.write((char*)&x2, sizeof(x2));
			output_file.write((char*)&y2, sizeof(y2));
		}
		output_file.close();
	}
}