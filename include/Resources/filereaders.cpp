
#include "filereaders.hpp"

using Point = std::vector<double>;
FileReader::FileReader(std::string name): filename{name} {}

std::vector<Point> FileReader::offRead(){
    Gudhi::Points_off_reader<Point> off_reader(this->filename);
    if (!off_reader.is_valid()) {
        std::cerr << "Unable to read file: " << this->filename << "\n";
        return {};
    }
    return off_reader.get_point_cloud();
}