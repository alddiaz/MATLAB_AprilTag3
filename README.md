# MATLAB_AprilTag3
A MATLAB wrapper for AprilTag3.
The procedure was updated to enable the compilation in MATLAB for Linux.
The repository contains the mex function 'apriltags.c' implementing the basic functionality for detection and 3-D pose estimation of AprilTag3 (current version, April 2019).
The code includes a fix of 'apriltag_pose.c', the original C++ module for 3-D pose estimation, to prevent deallocation of uninitialized memory.
It is strongly suggested to implement the fix before compiling the C++ code for the detector.
N.B.: Only the family 'tag36h11' of tags is supported.

# Demo
https://youtu.be/ptx3UyyvmTA

# Procedure
Read 'procedure.txt'

# Acknowledgments
- Basic MEX infrastructure provided Peter Corke in the Machine Vision Toolbox for MATLAB.
- 'apriltag_pose.c' fix by Gustaf Hendeby (Linkoping University, 2019).
