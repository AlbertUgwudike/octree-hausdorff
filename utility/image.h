#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>

#include "nifti/nifti1_io.h"
#include "panic.h"

typedef struct {
    bool *data;
    double H, W, D;
} Image;

typedef struct {
    double x, y, z;
} Point;

// populates canvas with image from file: 'filename'
Image load_image(const char *filename);

void unload_image(Image img);

bool idx(Image &img, Point point);

Point add(Point p1, Point p2);

Point sub(Point p1, Point p2);

Point div(Point p, float denom);

Point min_extrema(Point p1, Point p2);

Point max_extrema(Point p1, Point p2);

double sq_distance(Point p1, Point p2);

// test images
// bool data[36] = {
//     1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
//     1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
// };
// Image img = {data, 3, 3, 4};

// bool data[27] = {
//     0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
// };
// Image img = {data, 3, 3, 3};

#endif