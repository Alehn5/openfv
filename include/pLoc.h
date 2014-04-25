// -------------------------------------------------------
// -------------------------------------------------------
// Synthetic Aperture - Particle Tracking Velocimetry Code
// --- Particle Localization Header ---
// -------------------------------------------------------
// Author: Abhishek Bajpayee
//         Dept. of Mechanical Engineering
//         Massachusetts Institute of Technology
// -------------------------------------------------------
// -------------------------------------------------------

#ifndef LOCALIZATION_LIBRARY
#define LOCALIZATION_LIBRARY

#include "std_include.h"
#include "refocusing.h"
#include "typedefs.h"

using namespace std;
using namespace cv;

class pLocalize {

 public:

    ~pLocalize() {

    }

    pLocalize(localizer_settings s, saRefocus refocus, refocus_settings s2);

    vector<Point3f> detected_particles() { return particles_; }

    void run();

    void find_particles_all_frames();
    void find_particles_3d(int frame);
    
    void save_refocus(int frame);
    void z_resolution();
    void crop_focus();

    void find_clusters();
    void clean_clusters();
    void collapse_clusters();

    void find_particles(Mat image, vector<Point2f> &points_out);
    void refine_subpixel(Mat image, vector<Point2f> points_in, vector<particle2d> &points_out);

    void write_all_particles_to_file(string path);
    void write_all_particles(string path);
    void write_particles_to_file(string path);
    void write_clusters(vector<particle2d> &particles3D_, string path);
    void draw_points(Mat image, Mat &drawn, vector<Point2f> points);
    void draw_points(Mat image, Mat &drawn, vector<particle2d> points);
    void draw_point(Mat image, Mat &drawn, Point2f point);

 private:

    int point_in_list(Point2f point, vector<Point2f> points);
    double min_dist(Point2f point, vector<Point2f> points);
    double get_zloc(vector<particle2d> cluster);

    int window_;
    int cluster_size_;
    double zmin_;
    double zmax_;
    double dz_;
    double thresh_;
    double zext_;

    int zmethod_;

    vector<particle2d> particles3D_;
    vector< vector<particle2d> > clusters_;
    vector<Point3f> particles_;
    vector< vector<Point3f> > particles_all_;

    saRefocus refocus_;
    refocus_settings s2_;

    int show_particles_;

};

#endif
