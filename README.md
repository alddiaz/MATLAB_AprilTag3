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
- Basic MEX infrastructure provided by Peter Corke in the Machine Vision Toolbox for MATLAB. Download available at from [http://petercorke.com/wordpress/toolboxes/machine-vision-toolbox](http://petercorke.com/wordpress/toolboxes/machine-vision-toolbox).
- 'apriltag_pose.c' fix by Gustaf Hendeby (Linkoping University, 2019).

# References
[1] Krogius, M.; Haggenmiller, A.; Olson, E.; Flexible  Layouts  for  Fiducial  Tags, [pre-print](https://april.eecs.umich.edu/media/pdfs/krogius2019iros.pdf).
[2] P. Corke, The Machine Vision Toolbox: a MATLAB toolbox for vision and vision-based control, In: IEEE Robotics and Automation Magazine, vol. 12(4), 2005, pp. 16-25, [DOI: 10.1109/MRA.2005.1577021](https://ieeexplore.ieee.org/document/1577021).
[3] P. Corke, MATLAB toolboxes: robotics and vision for students and teachers, In: IEEE Robotics and Automation Magazine, vol. 14(4), 2007, pp. 16-17, [DOI: 10.1109/M-RA.2007.912004](https://ieeexplore.ieee.org/document/4437745).
