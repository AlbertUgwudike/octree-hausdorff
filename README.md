# Octree based rapid hausdorff distance algorithm

### Rapidly computes hausdorff distance between sparse 3D point clouds.

### Example usage:

-   $ make
-   $ ./hausdorff images/demo1.nii images/demo_noisy.nii
-   Determining Hausdorff distance between images/demo.nii and images/demo_noisy.nii ...
-   Hausdorff distance = 60.3738 voxels.
-   Compute time = 8615 ms.

The example images are sparse 3D binary images of dimension 512 * 512 * 160.
Each contains approximately 50,000 labelled voxels.

### Examples use the NifTi file format.

### Helper functions adapted from: https://nifti.nimh.nih.gov/pub/dist/src/
