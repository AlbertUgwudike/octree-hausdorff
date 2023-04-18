#ifndef OCTREE_H
#define OCTREE_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "../utility/image.h"
#include "../utility/panic.h"

typedef struct {
    int count = 0;
    Point origin;
    Point extrema;
    Point aggregate;
} Octant_Features;

typedef struct Octree {
    Point anchor;
    int count;
    Point origin;
    Point extrema;
    Octree *children[8];
} Octree;

// deallocate octree
Octree *init_octree(Octant_Features ofs);

// deallocate octree
void delete_octree(Octree *tree);

// get octant features
Octant_Features process(Image &img, Point origin, Point extrema);

// recursively creates octree of subvolume defined
// by origin and extrema
Octree *create_octree(Image &img, Point origin, Point extrema);

// dermine the quadrant to which a point belongs
int quadrant_idx(Point anchor, Point query);

// determine if Octree is leaf
bool is_leaf(Octree *octree);

// pretty print an octree
void traverse_tree(Octree *tree, int depth);

// count the total number of leaves
int count_leaves(Octree *tree);

// determiine the distance between p and tree
double closest(Octree *tree, Point p);

// determine greatest minimim distance between two point clouds
double hausdorff(const char *img1_fn, const char *img2_fn);

#endif
