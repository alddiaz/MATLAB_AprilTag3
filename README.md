# MATLAB_AprilTag3
The AprilTag3 wrapper for MATLAB with updated procedure for Linux compilation.<br />
**N.B.:** Only the family ''**tag36h11**'' of tags is supported!<br />

**Please cite this software if you use MATLAB_AprilTag3 in your research:**<br />
[1] A. A. Díaz Salazar, "MATLAB_AprilTag3", Linköping, Sweden, 2019.

# Procedure
Read '**procedure.txt**'. <br />
The MEX function '**apriltags.c**' implements AprilTag3 detection and 3-D pose estimation (April 2019 version).<br />
**'apriltags.c'** contains a **fix** to prevent deallocation of uninitialized memory.<br />
AprilRobotics guide: https://github.com/AprilRobotics/apriltag/wiki/AprilTag-User-Guide

# Demo
[AprilTag3 detection in MATLAB](https://youtu.be/ptx3UyyvmTA)

# Example
> im_rgb = imread("my_RGB_image.png"); <br />
  IM = rgb2gray(im_rgb); <br />
  tags = apriltags(IM, TAGSIZE, K); <br />

- "tags" is a vector of structures that describe each of the AprilTags found within image IM. <br />
TAGSIZE specifies the actual (printed!) tag size in meters. <br />
- K specifies camera calibration as a 3x3 matrix defined as K = [fx 0 u0; 0 fy v0; 0 0 1], with parameters <br />
  (fx, fy)	camera focal length <br />
  (u0, v0)	principal point (optical center of camera) <br />

Run "help apriltags" for further details.

# Acknowledgments
- Basic MEX infrastructure provided by Peter Corke in the Machine Vision Toolbox for MATLAB. Download available at [http://petercorke.com/wordpress/toolboxes/machine-vision-toolbox](http://petercorke.com/wordpress/toolboxes/machine-vision-toolbox).
- 'apriltag_pose.c' fix by Gustaf Hendeby (Linkoping University, 2019).

# References
[1] A. A. Díaz Salazar, "MATLAB_AprilTag3", Linköping, Sweden, 2019.<br />
[2] M. Krogius, A. Haggenmiller, and E. Olson, “Flexible Layouts for Fiducial Tags”, In: 2019 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS), 2019, pp. 1898–1903. [DOI: 10.1109/IROS40897.2019.8967787](https://ieeexplore.ieee.org/document/8967787).<br />
[3] Corke P., The Machine Vision Toolbox: a MATLAB toolbox for vision and vision-based control, In: IEEE Robotics and Automation Magazine, vol. 12(4), 2005, pp. 16–25. [DOI: 10.1109/MRA.2005.1577021](https://ieeexplore.ieee.org/document/1577021).<br />
[4] Corke, P., MATLAB toolboxes: robotics and vision for students and teachers, In: IEEE Robotics and Automation Magazine, vol. 14(4), 2007, pp. 16–17. [DOI: 10.1109/M-RA.2007.912004](https://ieeexplore.ieee.org/document/4437745).
