# MATLAB_AprilTag3
The AprilTag3 MEX wrapper for MATLAB on Linux implements tag detection and 3–D pose estimation. <br />
**N.B.:** Only the tag family ''**tag36h11**'' is supported! <br />

**Please cite this software if you use MATLAB_AprilTag3 in your research:** <br />
[1] A. A. Díaz Salazar, "MATLAB_AprilTag3", Linköping, Sweden, 2019. [Online](https://github.com/alddiaz/MATLAB_AprilTag3).

# Procedure
Read `procedure.md` for install instructions. <br />
> The MEX function "**apriltags.c**" implements AprilTag3 detection and 3–D pose estimation (April 2019 version) and contains a **MAJOR FIX** to prevent deallocation of uninitialized memory. <br />
AprilRobotics guide: https://github.com/AprilRobotics/apriltag/wiki/AprilTag-User-Guide

# Demo
[AprilTag3 detection on MATLAB](https://youtu.be/ptx3UyyvmTA)

# Example
Run `help apriltags` for syntax details.

```matlab
im_rgb = imread("my_RGB_image.png");
IM = rgb2gray(im_rgb);
tags = apriltags(IM, TAGSIZE, K);
```

> Inputs: <br />
**IM** is a grayscale image. <br />
**TAGSIZE** specifies the actual (printed!) tag size in meters. <br />
**K** specifies camera calibration as a 3x3 matrix defined by **K** = [**fx** 0 **u0**; 0 **fy** **v0**; 0 0 1] where **(fx, fy)** is the focal length and **(u0, v0)** is the principal point (optical center). <br />
Outputs: <br />
**tags** is a vector of structures with the parameters of the AprilTags found in **IM**. <br />

# Acknowledgments
Basic MEX infrastructure by Peter Corke given in the [Machine Vision Toolbox for MATLAB](http://petercorke.com/toolboxes/machine-vision-toolbox). <br />
MEX fix provided by [Gustaf Hendeby](http://users.isy.liu.se/en/rt/hendeby).

# References
[1] A. A. Díaz Salazar, "MATLAB_AprilTag3", Linköping, Sweden, 2019. [Online](https://github.com/alddiaz/MATLAB_AprilTag3). <br />
[2] M. Krogius, A. Haggenmiller, and E. Olson, “Flexible Layouts for Fiducial Tags”, In: 2019 IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS), 2019, pp. 1898–1903. [DOI: 10.1109/IROS40897.2019.8967787](https://ieeexplore.ieee.org/document/8967787).<br />
[3] P. Corke, The Machine Vision Toolbox: a MATLAB toolbox for vision and vision-based control, In: IEEE Robotics and Automation Magazine, vol. 12(4), 2005, pp. 16–25. [DOI: 10.1109/MRA.2005.1577021](https://ieeexplore.ieee.org/document/1577021).<br />
[4] P. Corke, MATLAB toolboxes: robotics and vision for students and teachers, In: IEEE Robotics and Automation Magazine, vol. 14(4), 2007, pp. 16–17. [DOI: 10.1109/M-RA.2007.912004](https://ieeexplore.ieee.org/document/4437745).
