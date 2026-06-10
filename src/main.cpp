#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

#include <gudhi/Rips_complex.h>
#include <gudhi/Simplex_tree.h>
#include <gudhi/Persistent_cohomology.h>
#include <gudhi/distance_functions.h>

#include <filereaders.hpp>

int main(int argc, char **argv) {
    // 1. Define types
    using Simplex_tree = Gudhi::Simplex_tree<Gudhi::Simplex_tree_options_fast_persistence>;
    using Filtration_value = Simplex_tree::Filtration_value;
    using Point = std::vector<double>;
    using Rips_complex  = Gudhi::rips_complex::Rips_complex<Filtration_value>;


    // 2. Load the noisy circle point cloud (.off format)
    FileReader file("circle.off");
    std::vector<Point> points = file.offRead();

    // 3. Construct the Vietoris-Rips complex (max dimension 2 to capture triangles)

    std::cout << "points size: " << points.size() << "\n";

    if (points.empty()) {
        std::cerr << "EMPTY POINT CLOUD\n";
        return 1;
    }

    size_t dim = points[0].size();

    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].size() != dim) {
            std::cerr << "DIM MISMATCH at " << i << "\n";
            return 1;
        }
    }
    Filtration_value max_edge_length = 5.0;
    Rips_complex rips_complex(points, max_edge_length, Gudhi::Euclidean_distance());

    Simplex_tree simplex_tree;
    rips_complex.create_complex(simplex_tree, 2);

    simplex_tree.initialize_filtration();
    simplex_tree.make_filtration_non_decreasing();

    std::cout << "points size: " << points.size() << "\n";

    // 4. Compute persistent homology
    Gudhi::persistent_cohomology::Persistent_cohomology<Simplex_tree, Gudhi::persistent_cohomology::Field_Zp> pcoh(simplex_tree, true);

    std::cout << "points size: " << points.size() << "\n";
    
    pcoh.init_coefficients(2);
    //pcoh.initialize_persistent_cohomology(false); // false for vineyarding if desired
    pcoh.compute_persistent_cohomology();

    // 5. Output persistence diagram and filter noise
    Filtration_value min_persistence = 0.01; // Set a threshold to ignore noise
    
    std::cout << "Dimension (Birth, Death)\n";
    for (auto const& pair : pcoh.get_persistent_pairs()) {
        int dim = simplex_tree.dimension(get<0>(pair));
        Filtration_value birth = simplex_tree.filtration(get<0>(pair));
        Filtration_value death = simplex_tree.filtration(get<1>(pair));
        
        // Filter out short-lived features (noise)
        if (death - birth >= 0) {
            std::cout << dim << " (" << birth << ", " << death << ")\n";
        }
    }

    return 0;
}

