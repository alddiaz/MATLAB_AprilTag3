#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <unistd.h>

#include "apriltag.h"
#include "image_u8.h"
#include "tag36h11.h"

#include "zarray.h"
#include "getopt.h"

#include "mex.h"

#include "apriltag_pose.h"

#ifdef __cplusplus
extern "C" {
#endif

static const char *fields[] = {"id", "hamming", "margin", "H", "center", "corners", "p", "R"};

mxArray *getTag(int width, int height, unsigned char *image, double tagSize, double *calibMatrix)
{
    apriltag_family_t *tf = NULL;
    tf = tag36h11_create();

    apriltag_detector_t *td = apriltag_detector_create();
    apriltag_detector_add_family(td, tf);
    td->quad_decimate = 2.0; // detection of quads done on a lower-resolution image
    td->quad_sigma = 0.0; // Gaussian blur (std in pixels) applied to the segmented image
    td->nthreads = 4; // number of threads to be used
    td->debug = 0; // // When non-zero, write debugging images to the current directory
    //int quiet = 0;
    //int maxiters = 1;
    const int hamm_hist_max = 10;
    image_u8_t *im = NULL;
    mxArray *out;
    int ntags;

    int hamm_hist[hamm_hist_max];
    memset(hamm_hist, 0, sizeof(hamm_hist));

    // Create the image structure, copy pixels to row-major order
    im = image_u8_create(width, height);

    for (int y=0; y < height; y++) {
        unsigned char *p = &im->buf[y*im->stride];
        unsigned char *q = &image[y];
        for (int x=0; x < width; x++) {
            *p++ = *q;
            q += height;
        }
    }

    // Perform the detections
    zarray_t *detections = apriltag_detector_detect(td, im);
    ntags = detections->size;

    if (ntags == 0) {
        zarray_destroy(detections);
        // mxDestroyArray(out);
        image_u8_destroy(im);
        apriltag_detector_destroy(td);
        tag36h11_destroy(tf);
        return NULL;
    }

    // create return structure
    out = mxCreateStructMatrix(1, ntags, 8, fields);

    for (int i = 0; i < ntags; i++) {
        apriltag_detection_t *det;
        double *p, *q;

        // Get the i'th tag
        zarray_get(detections, i, &det);

        // Save results into a passed MATLAB strucutre
        mxSetField(out, i, fields[0], mxCreateDoubleScalar( (double) det->id ) ); // id
        mxSetField(out, i, fields[1], mxCreateDoubleScalar( (double) det->hamming ) ); // hamming
        mxSetField(out, i, fields[2], mxCreateDoubleScalar( (double) det->decision_margin ) ); // margin
        /* id: The decoded ID of the tag.*/
        /* hamming: How many error bits were corrected. Accepting large numbers of
        corrected errors leads to greatly increased false positive rates.
        As of this implementation, the detector cannot detect tags with
        a hamming distance greater than 2. */
        /* margin: A measure of the quality of the binary decoding process: the
        average difference between the intensity of a data bit versus
        the decision threshold. Higher numbers roughly indicate better
        decodes. This is a reasonable measure of detection accuracy
        only for very small tags-- not effective for larger tags (where
        we could have sampled anywhere within a bit cell and still
        gotten a good detection. */

        // Save the tag homography as a 3x3 matrix
        mxArray *H = mxCreateDoubleMatrix( 3, 3, mxREAL );
        p = mxGetPr(H);
        q = det->H->data;
        for (int row=0; row<3; row++) {
            for (int col=0; col<3; col++) {
                p[row+col*3] = *q++;
            }
        }
        mxSetField(out, i, fields[3], H);
        /* H: The 3x3 homography matrix describing the projection from an
        "ideal" tag (with corners at (-1,1), (1,1), (1,-1), and (-1,-1))
        to pixels in the image. */

        // Save the center
        mxArray *center = mxCreateDoubleMatrix( 2, 1, mxREAL );
        p = mxGetPr(center);
        p[0] = det->c[0];
        p[1] = det->c[1];
        mxSetField(out, i, fields[4], center); // center
        /* center: The center of the detection in image pixel coordinates */

        // Save the corners as a 2x4 matrix
        mxArray *corners = mxCreateDoubleMatrix( 2, 4, mxREAL );
        p = mxGetPr(corners);
        for (int row=0; row<4; row++)
            for (int col=0; col<2; col++)
                p[col+row*2] = det->p[row][col]; // it's transposed
        mxSetField(out, i, fields[5], corners ); // corners
        /* corners: The corners of the tag in image pixel coordinates.
        These always wrap counter-clock wise around the tag. */

        // Pose Estimation
        apriltag_detection_info_t info;
        info.det = det;
        info.tagsize = tagSize;
        info.fx = *(calibMatrix + 0);
        info.fy = *(calibMatrix + 4);
        info.cx = *(calibMatrix + 6);
        info.cy = *(calibMatrix + 7);
        /* 'apriltag_detection_info_t' is a struct required for pose estimation
       containing:
         1. detector parameters
         2. camera calibration matrix
         3. tag size in meters
       */

        apriltag_pose_t pose;
        double err = estimate_tag_pose(&info, &pose);

        // Assign pose parameters to MATLAB structs for export
        mxArray *worldp = mxCreateDoubleMatrix( 3, 1, mxREAL );
        p = mxGetPr(worldp);
        int col=0;
        for (int row=0; row<3; row++)
            p[row+col*1] = *(pose.t->data + row+col*1);
        mxSetField(out, i, fields[6], worldp );  // worldp
        /* worldp: The position of the tag center w.r.t. the origin of camera coordinates */

        mxArray *R = mxCreateDoubleMatrix( 3, 3, mxREAL );
        p = mxGetPr(R);
        for (int row=0; row<3; row++)
            for (int col=0; col<3; col++)
                p[row+col*3] = *(pose.R->data + col+row*3);
        mxSetField(out, i, fields[7], R );  // R
        /* R: The rotation of the tag center w.r.t. the origin of camera coordinates */

        hamm_hist[det->hamming]++;

        // Deallocate memory
        matd_destroy(pose.t);
        matd_destroy(pose.R);
        apriltag_detection_destroy(det);
    }

    // Deallocate memory
    // Don't deallocate contents of inputs; those are the argv!
    zarray_destroy(detections);
    image_u8_destroy(im);
    apriltag_detector_destroy(td);
    tag36h11_destroy(tf);

    return out;
}


#define	IM_IN 		prhs[0] // grayscale image matrix
#define	TAG_SIZE	prhs[1] // tag size in meters
#define	CALIB_M		prhs[2] // camera calibration matrix

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    // Check inputs:
    if (nrhs < 3) {
        mexErrMsgTxt("Not enough input arguments.");
    }
    if (nrhs > 3) {
        mexErrMsgTxt("Too many input arguments.");
    }

    // Check outputs:
    if (nlhs > 1) {
        mexErrMsgTxt("Invalid number of outputs to MEX file.");
    }

    // Check image matrix input:
    if (mxGetN(IM_IN) < 3 || mxGetM(IM_IN) < 3) {
        mexErrMsgTxt("Invalid image.");
    }
    if (mxGetNumberOfDimensions(IM_IN) > 2) {
        mexErrMsgTxt("Color images are not supported");
    }

    // Check tag size input:
    if(mxGetN(TAG_SIZE) != 1 || mxGetScalar(TAG_SIZE) <= 0) {
        mexErrMsgTxt("Invalid tag size value.");
    }

    // Check camera calibration matrix input:
    if (mxGetN(CALIB_M) != 3 && mxGetM(CALIB_M) != 3) {
        mexErrMsgTxt("Invalid camera calibration matrix.");
    }

    // Get number of pixels in the image
    int width = mxGetN(IM_IN);
    int height = mxGetM(IM_IN);

    unsigned char *im; // image matrix
    double ts; // tag size in meters
    double *cm; // camera calibration matrix

    switch (mxGetClassID(IM_IN)) {
        case mxUINT8_CLASS: {
            im = (unsigned char *)mxGetPr(IM_IN); // get pointer to image
            break;
        }
        case mxDOUBLE_CLASS: {
            unsigned char *p = im = (unsigned char *)malloc(width*height);
            double        *q = mxGetPr(IM_IN);

            // Type convert
            for (int i=0; i<width*height; i++) {
                    *p++ = *q++ * 255;
            }
            break;
        }
        default:
            mexErrMsgTxt("Only uint8 or double images allowed.");
    }

    ts = mxGetScalar(TAG_SIZE); // get tag size
    cm = mxGetData(CALIB_M); // get camera calibration matrix

    // Find the tags
    plhs[0] = getTag(width, height, im, ts, cm);

    if (plhs[0] == NULL) {
        plhs[0] = mxCreateDoubleMatrix( 0, 0, mxREAL );  // return []
    }
}

#ifdef __cplusplus
}
#endif
