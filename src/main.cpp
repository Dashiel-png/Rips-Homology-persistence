#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

#include <gudhi/Rips_complex.h>
#include <gudhi/Simplex_tree.h>
#include <gudhi/Persistent_cohomology.h>

#include <filereaders.hpp>

int main(int argc, char **argv) {
    // 1. Define types
    using Simplex_tree = Gudhi::Simplex_tree<Gudhi::Simplex_tree_options_fast_persistence>;
    using Filtration_value = Simplex_tree::Filtration_value;
    using Point = std::vector<double>;

    // 2. Load the noisy circle point cloud (.off format)
    FileReader file("circle.off");
    std::vector<Point> points = file.offRead();

    // 3. Construct the Vietoris-Rips complex (max dimension 2 to capture triangles)
    Filtration_value max_edge_length = 2.0;
    Gudhi::Rips_complex<Filtration_value> rips_complex(points, max_edge_length);

    Simplex_tree simplex_tree;
    rips_complex.create_simplex_tree(simplex_tree, 2);

    // 4. Compute persistent homology
    Gudhi::persistent_cohomology::Field_Zp field(11); // Z/11Z coefficients
    Gudhi::persistent_cohomology::Persistent_cohomology<Simplex_tree, Gudhi::persistent_cohomology::Field_Zp> 
        pcoh(simplex_tree, field);
    
    pcoh.initialize_persistent_cohomology(false); // false for vineyarding if desired
    pcoh.compute_persistent_cohomology();

    // 5. Output persistence diagram and filter noise
    Filtration_value min_persistence = 0.2; // Set a threshold to ignore noise!
    
    std::cout << "Dimension (Birth, Death)\n";
    for (auto pair : pcoh.get_persistence_pairs()) {
        int dim = simplex_tree.dimension(pair.first);
        Filtration_value birth = simplex_tree.filtration(pair.first);
        Filtration_value death = simplex_tree.filtration(pair.second);
        
        // Filter out short-lived features (noise)
        if (death - birth >= min_persistence) {
            std::cout << dim << " (" << birth << ", " << death << ")\n";
        }
    }

    return 0;
}

