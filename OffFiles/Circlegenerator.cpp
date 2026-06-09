#ifndef CIRCLE
#define CIRCLE

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

struct Point3{
    double x, y, z;
};

int main(int argc, char** argv){
    int nums = argv[1][0];
    double radius = argv[2][0];
    double noise = argv[3][0];

    //Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> noisy_dist(-noise,noise);
    std::uniform_real_distribution<> angle_dist(0.0, 2.0 * M_PI);
    std::uniform_real_distribution<> radius_dist(0.0, radius*radius);

    //generate points
    std::vector<Point3> points;

    for(int i = 0; i < nums; i++){
        double r = std::sqrt(radius_dist(gen));
        double theta = angle_dist(gen);

        double x_comp = r * std::cos(theta);
        double y_comp = r * std::sin(theta);

        Point3 p;
        p.x = x_comp + noisy_dist(gen);
        p.y = y_comp + noisy_dist(gen);
        p.z = 0.0;

        points.push_back(p);
    }

    std::ofstream filestream("circle.off");
    if(!filestream.is_open()) {
        std::cerr << "File error" << std::endl;
        return 1;
    }

    filestream << "OFF\n";
    filestream << points.size() << " 0 0\n";
    for(const auto& p : points){
        filestream << p.x << p.y << p.z << std::endl;
    }
    filestream.close();
    std::cout << "Successfully generated " << points.size() << " points in circle.off" << std::endl;
    return 0;
    

}



#endif