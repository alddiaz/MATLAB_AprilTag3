# How to compile MATLAB_AprilTag3 - The MEX wrapper for Linux

## STEP 1: Compile AprilTag library

1. Install the Machine Vision Toolbox (MVTB) by opening MATLAB_AprilTag3 GitHub's file `MVTB-4.3.mltbx` from MATLAB GUI, or download the latest version at: <br />
    https://petercorke.com/download/28/mvtb/1109/mvtb-4-3.mltbx
1. Create auxiliary environmental variables from command line:
    ```shell
    MLTBX_DIR="$HOME/Documents/MATLAB/Add-Ons/Toolboxes"
    MVTB="$MLTBX_DIR/Machine Vision Toolbox for MATLAB"
    MVTB_MEX="$MVTB/vision/mex"
    MVTB_APRILTAG="$MVTB_MEX/apriltag"
    ```
1. Download MATLAB_AprilTag3 GitHub's file `AprilTag3.tar.gz` (the AprilTag3 source code)
and uncompress it, or download the latest version at: <br />
    https://codeload.github.com/AprilRobotics/apriltags/zip/master
1. Rename the uncompressed directory to `apriltag` to match the wrapper path.
1. Copy latter `apriltag` directory to `MVTB_MEX` by running from command line: <br />
    ```shell
    cp -pr apriltag "$MVTB_MEX"
    ```
1. Download MATLAB_AprilTag3 GitHub's directory `apriltag` at `Machine Vision Toolbox for MATLAB/vision/mex/apriltag/`
and copy it into `MVTB_MEX` directory:
    ```shell
    cp -pr apriltag "$MVTB_MEX"
    ```
1. Compile the AprilTag library:
    ```shell
    cd "$MVTB_APRILTAG"
    make
    sudo make install
    ```

## STEP 2: Compile MATLAB_AprilTag3

1. Download MATLAB_AprilTag3 GitHub's directory `Machine Vision Toolbox for MATLAB`
and copy it into `MLTBX_DIR` directory:
    ```shell
    cp -pr "Machine Vision Toolbox for MATLAB" "$MLTBX_DIR"
    ```
1. Compile the MEX file:
    ```shell
    cd "$MVTB_MEX"
    mex apriltags.c -I"$MVTB_APRILTAG" -I"$MVTB_APRILTAG"/common -L"$MVTB_APRILTAG" -lapriltag
    ```
1. Compile the remaining MVTB libraries from MATLAB's command line:
    ```matlab
    make
    ```
## STEP 3: Render your tags with appropriate scale (e.g. 3 to 5 inches)

**N.B.:** MATLAB_AprilTag3 detector only works with "**tag36h11**" tag family!

1. Download and uncompress MATLAB_AprilTag3 GitHub's file `tag36h11.tar.gz`
    ```shell
    gunzip -dc tag36h11.tar.gz | tar xvf -
    ```
1. Open a PNG tag file using an appropriate image editor, e.g., Inkscape.

1. Choose the tag dimensions before printing.

1. Enjoy! =})
