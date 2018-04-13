
#define _CRT_SECURE_NO_WARNINGS
//#include <sample/spectreSample.hpp>
//#include <sample/spectreSampleCalc.hpp>
//#include <thread>
//#include <processing/processingInternal.hpp>
//#include <processing/tools/astonTools.hpp>
extern "C"
{
#include <stdlib.h>
#include <video.h>
}

#include <sys/time.h>



#define WIDTH 224
#define HEIGHT 172

char spectre_buf[WIDTH * HEIGHT * 4 * 4 + 256];
char gray_buf[WIDTH * HEIGHT * 4 * 4 + 256];

struct exposure {
	unsigned int x;
	unsigned int y;
	unsigned int z;
};
int main (int argc, char **argv)
{
	struct timeval tv0, tv1;
	unsigned int time;

	struct exposure d; 
	d.x = 0x1F4;

	camera_open("/dev/video0", FMT_TYPE_MULTIFREQ);

	if (argc > 1) {
	    time = atoi(argv[1]);
	    //pmd_printf("%d set exposure time (%d)", __LINE__, time);
	    camera_set_exposure(time);
	    d.y = time;
	    d.z = time;



	}

	spectre_use_single_frame(true);
	//pmd_printf("dnx(%d), call one", __LINE__);

	gettimeofday(&tv0, NULL);
	
	spectre_init(time);

	spectre_produce2(spectre_buf, sizeof(spectre_buf));

	spectre_deinit();
	gettimeofday(&tv1, NULL);



	camera_close();
	return 0;
}
