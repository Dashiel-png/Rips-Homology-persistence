#ifndef READER
#define READER

#include <gudhi/Points_off_io.h>
#include <vector>
#include <iostream>
#include <string>

class FileReader {
    std::string filename;
    using Point = std::vector<double>;
    
    public:
    FileReader(std::string);

    std::vector<Point> offRead();
};


#endif
