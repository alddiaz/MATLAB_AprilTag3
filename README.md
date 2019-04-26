# MATLAB_AprilTag3
A MATLAB wrapper for AprilTag3.
The procedure was updated to enable the compilation in MATLAB for Linux.
The repository contains the mex function 'apriltags.c' implementing the basic functionality for detection and 3-D pose estimation of AprilTags3, the current version (2019).
The code includes a fix of 'apriltag_pose.c', the original C++ module for AprilTag3 3-D pose estimation, to prevent deallocation of uninitialized memory after 3-D pose estimation.
It is strongly suggested to implement the fix before compiling the detector.
N.B.: Only the family 'tag36h11' of tags is supported.

# Procedure
Read 'procedure.txt'

# Acknowledgments
- Basic MEX infrastructure provided Peter Corke in the Machine Vision Toolbox for MATLAB.
- AprilTag3 fix by Gustaf Hendeby (Linkoping University, 2019).
