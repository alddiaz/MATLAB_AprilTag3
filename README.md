# MATLAB_AprilTag3
A MATLAB wrapper for AprilTag3 written by Aldo Díaz (aldodiaz64 (at) gmail (dot) com).<br />
The procedure was updated to enable the compilation in MATLAB for Linux.<br />

**Please cite this paper if you use HBWT_AnaSynth in your research:**<br />
[1] Aldo Díaz, "MATLAB_AprilTag3", Linköping, Sweden, 2019.
<br /><br />
The repository contains the mex function 'apriltags.c' implementing the basic functionality for detection and 3-D pose estimation of AprilTag3 (current version, April 2019).<br />
The code includes a fix of 'apriltag_pose.c', the original C++ module for 3-D pose estimation, to prevent deallocation of uninitialized memory.
It is strongly suggested to implement the fix before compiling the C++ code for the detector.<br />
N.B.: Only the family 'tag36h11' of tags is supported.<br />
Reference Guide: https://github.com/AprilRobotics/apriltag/wiki/AprilTag-User-Guide

# Demo
[AprilTag3 detection in MATLAB](https://youtu.be/ptx3UyyvmTA)

# Procedure
Read 'procedure.txt' <br />
# Acknowledgments
- Basic MEX infrastructure provided by Peter Corke in the Machine Vision Toolbox for MATLAB. Download available at [http://petercorke.com/wordpress/toolboxes/machine-vision-toolbox](http://petercorke.com/wordpress/toolboxes/machine-vision-toolbox).
- 'apriltag_pose.c' fix by Gustaf Hendeby (Linkoping University, 2019).

# References
[1] Krogius, M.; Haggenmiller, A., Olson, E.; Flexible  Layouts  for  Fiducial  Tags, 2019, [pre-print](https://april.eecs.umich.edu/media/pdfs/krogius2019iros.pdf).<br />
[2] Corke P., The Machine Vision Toolbox: a MATLAB toolbox for vision and vision-based control, In: IEEE Robotics and Automation Magazine, vol. 12(4), 2005, pp. 16-25, [DOI: 10.1109/MRA.2005.1577021](https://ieeexplore.ieee.org/document/1577021).<br />
[3] Corke, P., MATLAB toolboxes: robotics and vision for students and teachers, In: IEEE Robotics and Automation Magazine, vol. 14(4), 2007, pp. 16-17, [DOI: 10.1109/M-RA.2007.912004](https://ieeexplore.ieee.org/document/4437745).
