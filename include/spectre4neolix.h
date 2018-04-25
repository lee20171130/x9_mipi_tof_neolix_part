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



extern int spectre_produce4neolix(unsigned int exposureTime, void *pdata, int data_len); 




}
#endif //__VIDEO_H__
