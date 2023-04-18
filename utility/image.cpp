#include "image.h"

// populates canvas with image from nifti file
Image load_image(const char *filename) {
    nifti_image *nim = nifti_image_read(filename, true);
    if (!nim) panic(IMG_LOAD);
    // if (nim->datatype != 4) panic(DATA_TYPE);

    bool *data = new bool[nim->nvox];
    for (int i = 0; i < nim->nvox; i++) {
        data[i] = ((short *)nim->data)[i];
    }

    double H = nim->dim[1];
    double W = nim->dim[2];
    double D = nim->dim[3];

    nifti_image_free(nim);
    return {data, H, W, D};
}

void unload_image(Image img) { delete img.data; }

bool idx(Image &img, Point point) {
    // index formula taken from nifit header file
    // (i + j*dim[1] + k*dim[1]*dim[2]) * (bitpix/8)
    int i = point.x + point.y * img.H + point.z * img.H * img.W;
    if (i >= img.H * img.W * img.D) {
        std::cout << "Invalid Coordinates " << point.x << " " << point.y << " "
                  << point.z << std::endl;
        std::cout << "H W D: " << img.H << " " << img.W << " " << img.D
                  << std::endl;
        std::cout << "idx: " << i << std::endl;
        std::cout << "max: " << int(img.H) * int(img.W) * int(img.D)
                  << std::endl;
        exit(-1);
    }
    return img.data[i];
}

Point add(Point p1, Point p2) {
    return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

Point sub(Point p1, Point p2) {
    return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

Point div(Point p, float denom) {
    return {p.x / denom, p.y / denom, p.z / denom};
}

Point min_extrema(Point p1, Point p2) {
    return {std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)};
}

Point max_extrema(Point p1, Point p2) {
    return {std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)};
}

double sq_distance(Point p1, Point p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    double z = p1.z - p2.z;
    return pow(x, 2) + pow(y, 2) + pow(z, 2);
}
