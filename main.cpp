#include <chrono>
#include <iostream>

#include "octree/octree.h"

int main(int argc, char **argv) {
    const char *img1_fn = argv[1];
    const char *img2_fn = argv[2];

    std::cout << "Determining Hausdorff distance between " << img1_fn << " and "
              << img2_fn << " ..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    double hd = sqrt(hausdorff(img1_fn, img2_fn));

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Hausdorff distance = " << hd << " voxels." << std::endl;
    std::cout << "Compute time = " << duration.count() << " ms." << std::endl;
}