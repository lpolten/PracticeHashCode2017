//
// Created by bennatura on 2/22/17.
//

#ifndef PRACTICEHASHCODE2017_PIZZA_H
#define PRACTICEHASHCODE2017_PIZZA_H

#include <vector>
#include <assert.h>

enum Content{T = 0, M =1};

struct Slice{

    Slice (unsigned row1_, unsigned column1_, unsigned row2_, unsigned column2_)
    : row1(row1_), column1(column1_), row2(row2_), column2(column2_)
    {}

    unsigned row1;
    unsigned column1;
    unsigned row2;
    unsigned column2;

    unsigned size() const
    {
        assert(row2 >= row1);
        assert(column2 >= column1);
        return (row2 - row1 + 1) * (column2 - column1 + 1);
    }
};

inline std::ostream& operator<< (std::ostream& stream, const Content& content)
{
    stream << ((content == Content::T) ? "T" : "M");
    return stream;
}

class Pizza {
public:
    Pizza(char * file);
    void print_cells();
    int get_score();
    void run_algorithm();

private:

    unsigned _rows;
    unsigned _columns;
    unsigned _min_content;
    unsigned _max_content;
    std::vector<std::vector<Content> > _cells;

    std::vector<Slice> _slices;
};


#endif //PRACTICEHASHCODE2017_PIZZA_H
