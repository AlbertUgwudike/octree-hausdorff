#include "octree.h"

// create octree
Octree *init_octree(Octant_Features ofs) {
    Octree *new_tree = new Octree;
    if (!new_tree) panic(TREE_ALLOC);
    new_tree->anchor = div(ofs.aggregate, ofs.count);
    new_tree->origin = ofs.origin;
    new_tree->extrema = ofs.extrema;
    for (int i = 0; i < 8; i++) new_tree->children[i] = NULL;
    return new_tree;
}

void delete_octree(Octree *tree) {
    if (!tree) return;
    for (int i = 0; i < 8; i++) delete_octree(tree->children[i]);
    delete tree;
}

// recursively creates octree of subvolume defined
// by origin and extrema
Octree *create_octree(Image &img, Point origin, Point extrema) {
    Octant_Features ofs = process(img, origin, extrema);
    // std::cout << "Creating octree " << ofs.origin.x << " " << ofs.origin.y
    //         << " " << ofs.origin.z << std::endl;
    if (ofs.count == 0) return NULL;
    Octree *new_tree = init_octree(ofs);
    if (ofs.count == 1) return new_tree;
    for (int i = 0; i < 8; i++) {
        Point ext = {(i / 1) % 2 ? ofs.origin.x : ofs.extrema.x,
                     (i / 2) % 2 ? ofs.origin.y : ofs.extrema.y,
                     (i / 4) % 2 ? ofs.origin.z : ofs.extrema.z};
        Point new_origin = min_extrema(new_tree->anchor, ext);
        Point new_extrema = max_extrema(new_tree->anchor, ext);
        new_tree->children[i] = create_octree(img, new_origin, new_extrema);
    }
    return new_tree;
}

int count_leaves(Octree *tree) {
    if (!tree) return 0;
    if (is_leaf(tree)) return 1;
    int sum = 0;
    for (int i = 0; i < 8; i++) sum += count_leaves(tree->children[i]);
    return sum;
}

void traverse_tree(Octree *tree, int depth) {
    if (!tree) return;
    for (int i = 0; i < 2 * depth; i++) std::cout << " ";
    if (is_leaf(tree))
        std::cout << "Leaf ";
    else
        std::cout << "Node ";
    std::cout << tree->anchor.x << " " << tree->anchor.y << " "
              << tree->anchor.z << std::endl;
    for (int i = 0; i < 8; i++) traverse_tree(tree->children[i], depth + 1);
}

// dermine the quadrant to which a point belongs
int quadrant_idx(Point anchor, Point query) {
    int idx = (query.x < anchor.x ? 1 : 0);
    idx += (query.y < anchor.y ? 2 : 0);
    return idx + (query.z < anchor.z ? 4 : 0);
}

// check cubes [origin, extrema] and [p, r] overlap
bool in_bound(Point origin, Point extrema, Point p, double r) {
    Point p_o = add(p, {-r, -r, -r});
    Point p_e = add(p, {r, r, r});
    Point ow = sub(max_extrema(p_e, extrema), min_extrema(p_o, origin));
    Point cw = add(sub(p_e, p_o), sub(extrema, origin));
    return cw.x > ow.x && cw.y > ow.y && cw.z > ow.z;
}

// get nearest point
double closest(Octree *tree, Point p) {
    if (!tree) panic(EMPTY_TREE);
    double dist_to_anchor = sq_distance(p, tree->anchor);
    if (is_leaf(tree)) return dist_to_anchor;
    int qi = quadrant_idx(tree->anchor, p);

    double current_nearest =
        tree->children[qi] ? closest(tree->children[qi], p) : INFINITY;

    if (current_nearest == 0) return 0;

    for (int i = 0; i < 8; i++) {
        Octree *child = tree->children[i];
        if (!child) continue;
        if (in_bound(child->origin, child->extrema, p, current_nearest)) {
            double d = closest(child, p);
            if (d < current_nearest) current_nearest = d;
        }
    }

    return current_nearest;
}

Octant_Features process(Image &img, Point p1, Point p2) {
    // order extrema
    Point small = min_extrema(p1, p2);
    Point large = max_extrema(p1, p2);

    Octant_Features ofs;

    for (float x = std::ceil(small.x); x < large.x; x++)
        for (float y = std::ceil(small.y); y < large.y; y++)
            for (float z = std::ceil(small.z); z < large.z; z++) {
                if (!idx(img, {x, y, z})) continue;
                Point p = {x, y, z};
                ofs.origin = ofs.count ? min_extrema(ofs.origin, p) : p;
                ofs.extrema = ofs.count ? max_extrema(ofs.extrema, p) : p;
                ofs.count++;
                ofs.aggregate = add(ofs.aggregate, p);
            }

    ofs.origin = small;
    ofs.extrema = large;
    return ofs;
}

// determine if Octree is leaf
bool is_leaf(Octree *octree) {
    for (int i = 0; i < 8; i++)
        if (octree->children[i]) return false;
    return true;
}

double hausdorff(const char *img1_fn, const char *img2_fn) {
    Image img1 = load_image(img1_fn);
    Octree *tree = create_octree(img1, {0, 0, 0}, {img1.H, img1.W, img1.D});
    unload_image(img1);

    Image img2 = load_image(img2_fn);
    double dist = 0;

    for (float x = 0; x < img2.H; x++)
        for (float y = 0; y < img2.W; y++)
            for (float z = 0; z < img2.D; z++) {
                if (!idx(img2, {x, y, z})) continue;
                double d = closest(tree, {x, y, z});
                dist = std::max(dist, d);
            }
    unload_image(img2);
    delete_octree(tree);
    return dist;
}