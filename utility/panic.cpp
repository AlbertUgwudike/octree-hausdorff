#include "panic.h"

void panic(Message message) {
    std::string msg = panic_message(message);
    std::cout << "Error: " << msg << std::endl;
    exit(-1);
}

std::string panic_message(Message message) {
    switch (message) {
        case IMG_LOAD:
            return "Image Load failure.";
        case DATA_TYPE:
            return "Invalid nifti data-type.";
        case TREE_ALLOC:
            return "Tree allocation failure.";
        case EMPTY_TREE:
            return "Queried Empty Octree.";
    }
}
