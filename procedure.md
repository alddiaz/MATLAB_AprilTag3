++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
How to compile MATLAB_AprilTag3 - The AprilTag3 MEX wrapper for MATLAB for Linux
Aldo Diaz, Linköping, 2019
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# STEP 1: Compile AprilTag library

1. Download the Machine Vision Toolbox (MVTB) for MATLAB: <br />
https://petercorke.com/wordpress/?ddownload=527
1. Install MVTB from MATLAB GUI by opening the file `Machine Vision Toolbox for MATLAB.mltbx`
1. Uncompress the MATLAB_AprilTag3 GitHub's file `AprilTag3.tar.gz` (AprilTag3 source code)
  or download the latest version at: <br />
https://codeload.github.com/AprilRobotics/apriltags/zip/master
1. Rename the uncompressed directory to `apriltag` to match it with the wrapper.
1. Move latter `apriltag` directory to MVTB_MEX directory by running from command line: <br />
```shell
MVTB_MEX="$HOME/Documents/MATLAB/Add-Ons/Toolboxes/Machine Vision Toolbox for MATLAB/vision/mex/apriltag"
mv apriltag "$MVTB_MEX"
```
1. Copy and replace the content of MATLAB_AprilTag3 GitHub directory `apriltag`  at `Machine Vision Toolbox for MATLAB/vision/mex/apriltag/` to `MVTB_MEX` directory.
1. Compile the AprilTag library:
```shell
cd "$MVTB_MEX"
make
sudo make install
```
++++++++++++++++++++++++++++++++++++++++++++++++

# STEP 2: Compile MATLAB_AprilTag3 - The AprilTag3 MEX wrapper for MATLAB

1. Copy all the content from MATLAB_AprilTag3 GitHub directory `Machine Vision Toolbox for MATLAB` to `"$HOME/Documents/MATLAB/Add-Ons/Toolboxes/Machine Vision Toolbox for MATLAB/"`

1. Compile the MEX file:
```shell
cd "$HOME/Documents/MATLAB/Add-Ons/Toolboxes/Machine Vision Toolbox for MATLAB/vision/mex"
PREFIX="$HOME/Documents/MATLAB/Add-Ons/Toolboxes/Machine Vision Toolbox for MATLAB/vision/mex/apriltag"
mex apriltags.c -I"$PREFIX" -I"$PREFIX"/common -L"$PREFIX" -lapriltag
```

1. Open MATLAB to compile the rest of MVTB libraries:
```shell
make
```

1. Render the tags with appropiate scale (e.g. 3 to 5 inches) <br />
**N.B.:** The AprilTag detector only works with "**tag36h11**" tag family!

1. Uncompress the GitaHub file `tag36h11.tar.gz`

1. Open a PNG tag file in an appropriate image editor, e.g., Inkscape

1. Choose tag dimensions to print it.

1. Enjoy! =})
