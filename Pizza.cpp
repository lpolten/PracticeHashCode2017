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

void Pizza::run_algorithm() {
    //TODO: create slices here.

    Slice slice(2,2,3,3);
    _slices.push_back(slice);
    _slices.push_back(Slice(5,5,4,4));

}


