#ifndef __SPECTRE4NEOLIX_H__
#define __SPECTRE4NEOLIX_H__

extern "C" {


struct exposureTimesIn {
	unsigned int x;
	unsigned int y;
	unsigned int z;
};

struct depthpoint {
	float x;
	float y;
	float z;
	float noise;
};

enum FMT_TYPE {
	FMT_TYPE_MULTIFREQ = 0,
	FMT_TYPE_MONOFREQ
};

int spectre_init(int exposure_time);
int spectre_deinit();

int spectre_produce(void *pdata, int data_len);


/*  spectre_buf: pixel point buf, 
    struct pixel {
	usigned short x;
	usigned short y;
	usigned short z;
	usigned short noise;
    };

 * raw buf: gray_buf, size = WIDTH 224 * HEIGHT * 172 * sizeof(uint16_t)
 * spectre_size: pixel point buf, WIDTH 224 * HEIGHT 172 * sizeof(struct pixel)
 * exposureTime: exposure time
 */

int spectre_produce_sunny(char *spectre_buf, char *gray_buf, unsigned int spectre_size, unsigned int exposureTime);


/* in == true, set to single frame mode
 * in == false, set to multi frame mode
 */
int spectre_use_single_frame(bool in);
/* in == true, parse paramater from eeprom.bin
 * in == false, get paramater from pre-shipped binary files
 */
}
#endif //__VIDEO_H__
