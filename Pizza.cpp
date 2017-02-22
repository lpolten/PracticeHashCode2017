//
// Created by bennatura on 2/22/17.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Pizza.h"

Pizza::Pizza(char * file) {
    std::fstream filestream(file);

    std::string line;
    getline(filestream, line);
    std::stringstream ss(line);

    ss >> _rows;
    ss >> _columns;
    ss >> _min_content;
    ss >> _max_content;

    _cells.reserve(_rows);

    for(size_t i = 0; i < _rows; i++)
    {
        std::vector<Content> cur_row;
        getline(filestream,line);

        for(size_t j = 0; j < line.length(); j++)
        {
            Content const content = line[j] == 'T' ? Content::T : Content::M;
            cur_row.push_back(content);
        }

        _cells.push_back(cur_row);
    }
}

void Pizza::print_cells() {
    for(size_t i = 0; i < _cells.size(); i++)
    {
        for(size_t j = 0; j < _cells[i].size(); j++)
        {
            std::cout << _cells[i][j];
        }
        std::cout << std::endl;
    }
}

int Pizza::get_score() {

    bool cell_used[_rows][_columns];

    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++)
        {
            cell_used[i][j] = false;
        }
    }

    int score = 0;

    for(size_t i = 0; i < _slices.size(); i++)
    {
        Slice const slice = _slices[i];

        //test if slice is legit

        if(std::max(slice.row1, slice.row2) >= _rows or std::max(slice.column1, slice.column2) >= _columns)
        {
            return SLICES_OUT_OF_BOUNDS;
        }

        std::vector<unsigned> contents(2, 0);

        for(unsigned row = slice.row1; row <= slice.row2; row++)
        {
            for(unsigned column = slice.column1; column <= slice.column2; column++)
            {
                if(cell_used[row][column])
                {
                    return SLICES_OVERLAP;
                }

                cell_used[row][column] = true;
                contents[_cells[row][column]]++;
            }
        }

        if(std::max(contents[0],contents[1]) > _max_content or std::min(contents[0],contents[1]) < _min_content)
        {
            return SLICES_WRONG_CONTENT;
        }

        score += slice.size();
    }

    return score;
}

void Pizza::write_submission_file(char * output_filename)
{
    std::ofstream output_file;
    output_file.open(output_filename);

    output_file << _slices.size();

    for(size_t i = 0; i < _slices.size(); i++)
    {
        Slice const slice = _slices[i];
        output_file << std::endl << slice.row1 << " " << slice.column1 << " " << slice.row2 << " " << slice.column2;
    }

    output_file.close();
    /*std::string file_string(output_filename);
    system(("gedit " + file_string).c_str());*/
}

void Pizza::run_algorithm()
{
    /*greedy algorithm, just adds new legal slices if possible*/
    bool cell_used[_rows][_columns];
    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++)
        {
            cell_used[i][j] = false;
        }
    }

    for(unsigned i = 0; i < _rows;i++)
    {
        for(unsigned k = i; k < _rows;k++)
        {
            for(unsigned j = 0; j < _columns; j++)
            {
                for(unsigned l = j; l < _columns; l++)
                {
                    //test if slice is legit
                    bool this_slice_not_used = true;
                    std::vector<unsigned> contents(2, 0);

                    for(unsigned row = i; row <= k; row++)
                    {
                        for(unsigned column = j; column <= l; column++)
                        {
                            if(cell_used[row][column]!=false)
                            {
                                this_slice_not_used = false;
                            }
                            contents[_cells[row][column]]++;
                        }
                    }
                    if(std::max(contents[0],contents[1]) > _max_content or std::min(contents[0],contents[1]) < _min_content)
                    {
                        this_slice_not_used = false;
                    }
                    if(this_slice_not_used)
                    {
                        _slices.push_back(Slice(i,j,k,l));
                        for(unsigned row = i; row <= k; row++)
                        {
                            for(unsigned column = j; column <= l; column++)
                            {
                                cell_used[row][column] = true;
                            }
                        }
                    }
                }
            }
        }
    }
}


