# MATLAB_AprilTag3
A MATLAB wrapper for AprilTag3.
The repository contains the mex function "apriltags.c" implementing the basic functionality for detection and 3-D pose estimation of AprilTags3, the current version (2019).
The code includes a fix  to the original C++ implementation of the AprilTag3 detector that prevents deallocation of uninitialized memory on the 3-D pose estimation module.
It is strongly suggested to implement the fix before compiling the detector.
N.B.: Only the family 'tag36h11' of tags is supported.

# Procedure

# Acknowledgments
- Basic MEX infrastructure provided Peter Corke in the Machine Vision Toolbox for MATLAB.
- Fix provided by Gustaf Hendeby (Linkoping University, 2019).
