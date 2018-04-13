/*
 * Pelican Imaging Confidential
 * Unpublished Work Copyright 2015 Pelican Imaging, Inc.  All Rights Reserved.
 * 
 * All information contained herein is the confidential property of Pelican Imaging, Inc.
 * The intellectual and technical
 * concepts contained herein are proprietary of Pelican Imaging Inc. 
 * and may be covered by U.S. and Foreign Patents, patents in process,
 * and are protected by trade secret and / or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Pelican Imaging Inc.
 */

#ifndef SDM450RDIHALInterface_H
#define SDM450RDIHALInterface_H

#include<stdio.h>
#include<stdlib.h>


class SettingsValue {
	public:
		uint32_t exposure_val;
		uint8_t gain_val;
};

class SDM450RDIHALInterface 
{
public:
    SDM450RDIHALInterface(int camId);
    ~SDM450RDIHALInterface();

   // int32_t init();
    int32_t camera_getbuf(u_int8_t *frameBuffer, uint32_t bufferSize, uint32_t &bufIdx);
    int32_t teardown();
	int32_t getCameraSettings(void);
	static  int32_t get_num_cameras();
	float get_tof_temp();
	int tof_eeprom_enable();
    int32_t camera_open(int camId);
	int32_t setTOF_FPS_Mode(uint32_t fps_mode);
	int32_t camera_close();
	int32_t getNumRdiBuf();
	void    getRdiBufInfo(int  bufCount , 
	                      void *bufInfo);
private:
    bool isStreaming_;
	bool mCameraOpen;
	int  mCameraId;
};

#endif //SDM450RDIHALInterface_H
