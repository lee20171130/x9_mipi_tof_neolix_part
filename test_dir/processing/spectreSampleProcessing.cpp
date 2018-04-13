/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <sample/spectreSample.hpp>
#include <sample/spectreSampleCalc.hpp>
#include <thread>
#include <processing/processingInternal.hpp>
#include <processing/tools/astonTools.hpp>

#include <video.h>
#define WIDTH 224
#define HEIGHT 172


#if 0
int myprocess(struct spectre::sample::Data &output)
{
    float* coordinates = output->pm3d_coord;

    for (; distance < end; ++distance, ++distanceNoise, ++flags)
    {
        if (sparsePointCloud && *flags) {
            directions += 3;
        }
        else
        {
            *coordinates++ = *distance * *directions++;     // x
            *coordinates++ = *distance * *directions++;     // y
            *coordinates++ = *distance * *directions++;     // z
            if (*flags) {
                *coordinates++ = 0.0f;
            }
            else {
                *coordinates++ = -*distanceNoise * invThreshold + 1.0f;
            }
        }
    }
}
#endif
int specture_save_file(void *data, char *filename)
{
	struct depthpoint *p = (struct depthpoint *) data;
	FILE *fp;
	float val;
	unsigned int i;
	unsigned short tmp;

	fp = fopen(filename, "wb+");
	if (fp) {
		for (i = 0; i < WIDTH * HEIGHT; i++) {
			tmp = (unsigned short)(p[i].z * 4096);
#if 0
			if (0 && i < 100)
				printf("convert val: %d\n", tmp);
#endif
			fwrite(&tmp, 1, 2, fp);
		}
		fclose(fp);
	}

	return 0;
}


int specture_save_buf(void *data, char *buf)
{
	memcpy((void*) buf, data, 16 * WIDTH * HEIGHT);
	return 0;
}

int specture_save_buf2(void *data, char *buf)
{
	struct depthpoint *p = (struct depthpoint *) data;
	unsigned short *v = (unsigned short *) buf;
	unsigned int i;
	FILE *fp = NULL;

#ifdef DEBUG_DUMP_FILE_RAW
	fp = fopen("specure_pixels_xyz.txt", "wb+");
	if (!fp) {
		pmd_printf("dnx(%d) open specure_pixels_xyz.txt fail\n", __LINE__);
	}
#endif


	for (i = 0; i < WIDTH * HEIGHT; i++) {
		*v++ = (unsigned short) (p[i].x * 2048);
		*v++ = (unsigned short) (p[i].y * 2048);
		*v++ = (unsigned short) (p[i].z * 2048);
		*v++ = (unsigned short) (p[i].noise * 2048);

#ifdef DEBUG_DUMP_FILE
		if (fp) { 
		if (p[i].z > 1.0)
			fprintf(fp, "%f;%f;%f\n", 0, 0 , 0);
		else
			fprintf(fp, "%f;%f;%f\n", p[i].x, p[i].y, p[i].z);
		}
#endif
	}
	if (fp != NULL)
		fclose(fp);

#if DEBUG_DUMP_FILE_RAW
	{

	static unsigned int idx = 0;

	if (idx == 0)
	fp = fopen("specure_pixels_x0.raw", "wb+");
	else if (idx == 1)
	fp = fopen("specure_pixels_x1.raw", "wb+");

	fwrite(buf, 2, WIDTH * HEIGHT, fp);
	fclose(fp);
	idx++;
	}
#endif
	return 0;
}

struct exposureTimesIn spectre_exposureTimes;
uint16_t *g_gray_buf = NULL;
uint16_t use_single_frame_mode = 1;

int spectre_use_single_frame(bool in)
{
	if (in == true)
	  use_single_frame_mode = 1;
	else
	  use_single_frame_mode = 0;
        return 0;
}
struct spectre::sample::Data data;
int spectre_init(unsigned int exposureTime)
{
	int ret = 0;
    	spectre::sample::initMemory (data);
    spectre_exposureTimes.x = 0x1F4;
    spectre_exposureTimes.y = exposureTime;
    spectre_exposureTimes.z = exposureTime;
	return ret;
}
int spectre_deinit(void)
{
	int ret = 0;
    	spectre::sample::freeMemory (data);
	return ret;
}
int spectre_produce2(char *pcl_data, int size)
{
	int ret = 0;
    spectre::sample::runProcessing (data);
    specture_save_buf((void *) data.ps_output->pm3d_coord, pcl_data);
	return ret;
}
int spectre_produce(char *spectre_buf, char *gray_buf, unsigned int spectre_size, unsigned int exposureTime)
{
    if (gray_buf != NULL)
    	g_gray_buf = (uint16_t *) gray_buf;

    spectre_exposureTimes.x = 0x1F4;
    spectre_exposureTimes.y = exposureTime;
    spectre_exposureTimes.z = exposureTime;

    spectre::sample::initMemory (data);

    spectre::sample::runProcessing (data);
    spectre::sample::calcMeanDistanceAndValidPixels ( (uint32_t) data.ps_output->numColumns * (uint32_t) data.ps_output->numRows,
            data.ps_output->pm_distance,
            data.ps_output->pm_flags,
            data);
    spectre::sample::printMeanDistanceAndValidPixels (data);

    specture_save_file((void *) data.ps_output->pm3d_coord, "spectre_pixels.raw");
    specture_save_buf((void *) data.ps_output->pm3d_coord, spectre_buf);

    spectre::sample::freeMemory (data);
    g_gray_buf = NULL;
    return 0;
}

