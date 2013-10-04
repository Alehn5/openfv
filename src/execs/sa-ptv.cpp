#include "std_include.h"

#include "calibration.h"
#include "refocusing.h"
#include "pLoc.h"
#include "tracking.h"
#include "tools.h"
#include "optimization.h"

#include "cuda_lib.h"
#include "cuda_profiler_api.h"

#include "gperftools/profiler.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    
    /*
    // Camera Calibration Section
    string calib_path(argv[1]);
    Size grid_size = Size(6,9); // Format (horizontal_corners, vertical_corners)
    double grid_size_phys = 6;  // in [mm]

    //stringstream sref(argv[2]);
    int ref = 1;
    //sref>>ref; // 1 for refractive

    multiCamCalibration calibration(calib_path, grid_size, grid_size_phys, ref, 0, 0);
    //calibration.grid_view();
    
    calibration.run();
    */
    /*
    vector<int> const_pts;
    baProblem_ref ba_problem;
    calibration.run_BA_refractive(ba_problem, "../temp/ba_data.txt", Size(1292,964), const_pts);
    calibration.write_calib_results_matlab_ref();
    */
    
    int frame = 0;
    int mult = 0;
    double mult_exp = 1.0/9.0;
    //string refoc_path(argv[1]);
    //string refoc_path("../../experiment/binary_cylinder/");
    saRefocus refocus(string(argv[1]), frame, mult, mult_exp);
    refocus.read_imgs_mtiff(string(argv[2]));
    refocus.initializeGPU();
    refocus.GPUrefocus_ref(0, 0, 1, 0);
    waitKey(0);
    //refocus.GPUliveView();

    //ProfilerStart("profile");
    //refocus.CPUrefocus_ref();
    //ProfilerStop();

    /*
    int live = 1;
    if (live) {
        refocus.GPUliveView();
    } else {
        refocus.initializeGPU();
        
        int window = 2;
        int cluster_size = 10;
        double zmin = -30.0; //-20
        double zmax = 30.0; //40
        double dz = 0.1;
        double thresh = 90.0; //100.0
        pLocalize localizer(window, zmin, zmax, dz, thresh, cluster_size, refocus);

        //localizer.z_resolution();
        //localizer.crop_focus();
        
        //localizer.run();
        //localizer.write_particles_to_file("../matlab/data_files/particle_sim/particles_grid_mult.txt");
        //localizer.find_particles_all_frames();

        //localizer.write_all_particles_to_file(particle_file);        
        

    }
    
    //cout<<endl<<"TIME TAKEN: "<<(omp_get_wtime()-wall_timer)<<" seconds"<<endl;
    */    

    return 1;

}