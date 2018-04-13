/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <unistd.h>
#include <system/toolsIO.hpp>
#include <processing/processing.hpp>
#include <processing/processingInternal.hpp>
#include <common/calibration.hpp>
extern "C"
{
#include <cutils/properties.h>
#include <sys/time.h>
}
#include <processing/algorithm/ref/initCalcAutoExposure.hpp>
#include <processing/common/processingInit.hpp>

#include <video.h>

extern struct exposureTimesIn spectre_exposureTimes;
extern uint16_t *g_gray_buf;
extern uint16_t use_single_frame_mode ;

extern int camera_getbuf(char *p, unsigned int size);

inline bool spectreAstonParameterSave (SpectreParameter *param, std::string path)
{
    float temp;
    uint32_t boolTemp {};

    pmd_saveArray ("param_Version", 1, &param->version);
    pmd_saveArray ("param_Type", 1, &param->type);

    pmd_saveArray ("param_AdaptiveNoiseFilterType", 1, &param->adaptiveNoiseFilterType);
    pmd_saveArray ("param_AmplitudeThreshold", 1, &param->amplitudeThreshold);
    pmd_saveArray ("param_ConsistencyTolerance", 1, &param->consistencyTolerance);
    pmd_saveArray ("param_FlyingPixelF0", 1, &param->flyingPixel.f0);
    pmd_saveArray ("param_FlyingPixelF1", 1, &param->flyingPixel.f1);
    pmd_saveArray ("param_FlyingPixelFarDist", 1, &param->flyingPixel.farDist);
    pmd_saveArray ("param_FlyingPixelNearDist", 1, &param->flyingPixel.nearDist);
    temp = (float) param->saturationThreshold.lower;
    pmd_saveArray ("param_LowerSaturationThreshold", 1, &temp);
    temp = (float) param->saturationThreshold.upper;
    pmd_saveArray ("param_UpperSaturationThreshold", 1, &temp);

    pmd_saveArray ("param_MPIAmpThreshold", 1, &param->mpi.amplitudeThreshold);
    pmd_saveArray ("param_MPIDistThreshold", 1, &param->mpi.distanceThreshold);
    pmd_saveArray ("param_MPINoiseDistance", 1, &param->mpi.noiseDistance);
    pmd_saveArray ("param_NoiseThreshold", 1, &param->noiseThreshold);
    pmd_saveArray ("param_ReferenceAmplitude", 1, &param->exposureReferenceAmplitude);

    // Algorithm Parameters
    boolTemp = param->config.useAdaptiveNoiseFilter > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseAdaptiveNoiseFilter", 1, &boolTemp);
    boolTemp = param->config.useCalcIntensities > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseCalcIntensities", 1, &boolTemp);
    boolTemp = param->config.useAutoExposure > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseAutoExposure", 1, &boolTemp);
    boolTemp = param->config.useRemoveFlyingPixel > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseRemoveFlyingPixel", 1, &boolTemp);
    boolTemp = param->config.useMPIFlagAverage > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseMPIFlagAverage", 1, &boolTemp);
    boolTemp = param->config.useMPIFlagAmplitude > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseMPIFlagAmplitude", 1, &boolTemp);
    boolTemp = param->config.useMPIFlagDistance > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseMPIFlagDistance", 1, &boolTemp);
    boolTemp = param->config.useValidateImage > 0 ? (uint32_t) 1 : (uint32_t) 0;
    pmd_saveArray ("param_UseValidateImage", 1, &boolTemp);

    return true;
}

inline bool spectreAstonParameterLoad (SpectreParameter **params, std::string path)
{
    *params = reinterpret_cast<SpectreParameter *> (malloc (sizeof (SpectreParameter)));
    memset (*params, 0, sizeof (SpectreParameter));

    float temp;
    uint32_t boolTemp {};

    pmd_loadScalar (path + "/param_Type.bin", & ( (*params)->type));
    pmd_loadScalar (path + "/param_Version.bin", & ( (*params)->version));

    pmd_loadScalar (path + "/param_AdaptiveNoiseFilterType.bin", & ( (*params)->adaptiveNoiseFilterType));
    pmd_loadScalar (path + "/param_AmplitudeThreshold.bin", & ( (*params)->amplitudeThreshold));
    pmd_loadScalar (path + "/param_ConsistencyTolerance.bin", & ( (*params)->consistencyTolerance));
    pmd_loadScalar (path + "/param_FlyingPixelF0.bin", & ( (*params)->flyingPixel.f0));
    pmd_loadScalar (path + "/param_FlyingPixelF1.bin", & ( (*params)->flyingPixel.f1));
    pmd_loadScalar (path + "/param_FlyingPixelFarDist.bin", & ( (*params)->flyingPixel.farDist));
    pmd_loadScalar (path + "/param_FlyingPixelNearDist.bin", & ( (*params)->flyingPixel.nearDist));
    pmd_loadScalar (path + "/param_LowerSaturationThreshold.bin", &temp);
    (*params)->saturationThreshold.lower = (uint16_t) temp;
    pmd_loadScalar (path + "/param_UpperSaturationThreshold.bin", &temp);
    (*params)->saturationThreshold.upper = (uint16_t) temp;

    pmd_loadScalar (path + "/param_MPIAmpThreshold.bin", & ( (*params)->mpi.amplitudeThreshold));
    pmd_loadScalar (path + "/param_MPIDistThreshold.bin", & ( (*params)->mpi.distanceThreshold));
    pmd_loadScalar (path + "/param_MPINoiseDistance.bin", & ( (*params)->mpi.noiseDistance));
    pmd_loadScalar (path + "/param_NoiseThreshold.bin", & ( (*params)->noiseThreshold));
    pmd_loadScalar (path + "/param_ReferenceAmplitude.bin", & ( (*params)->exposureReferenceAmplitude));

    // Algorithm Parameters
    pmd_loadScalar (path + "/param_UseAdaptiveNoiseFilter.bin", &boolTemp);
    (*params)->config.useAdaptiveNoiseFilter = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseCalcIntensities.bin", &boolTemp);
    (*params)->config.useCalcIntensities = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseAutoExposure.bin", &boolTemp);
    (*params)->config.useAutoExposure = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseRemoveFlyingPixel.bin", &boolTemp);
    (*params)->config.useRemoveFlyingPixel = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseMPIFlagAverage.bin", &boolTemp);
    (*params)->config.useMPIFlagAverage = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseMPIFlagAmplitude.bin", &boolTemp);
    (*params)->config.useMPIFlagAmplitude = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseMPIFlagDistance.bin", &boolTemp);
    (*params)->config.useMPIFlagDistance = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseValidateImage.bin", &boolTemp);
    (*params)->config.useValidateImage = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;

    return true;
}

inline bool spectreAstonCalibrationSave (SpectreCalibration *ps_calib, std::string path)
{
    bool status = true;

    uint32_t numPixel = ps_calib->pv_calibrationROI[2] * ps_calib->pv_calibrationROI[3];

    // dimension information calibrationROI
    status = pmd_saveArray ("calib_CalibrationROI", 4, ps_calib->pv_calibrationROI) && status ? true : false;

    // general information
    status = pmd_saveArray ("calib_date", 19, ps_calib->pc_date) && status ? true : false;
    status = pmd_saveArray ("calib_serial", 9, ps_calib->pc_serial) && status ? true : false;
    status = pmd_saveArray ("calib_SensorSerial", 19, ps_calib->pc_sensorSerial) && status ? true : false;

    status = pmd_saveArray ("calib_version", 1, &ps_calib->version) && status ? true : false;
    status = pmd_saveArray ("calib_type", 1, &ps_calib->type) && status ? true : false;

    int16_t *directionsTemp = (int16_t *) malloc (numPixel * 3 * sizeof (int16_t));;
    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        directionsTemp[ (3 * idx) + 0] = (int16_t) (ps_calib->pm3d_directions[ (3 * idx) + 0] * (float) INT16_MAX);
        directionsTemp[ (3 * idx) + 1] = (int16_t) (ps_calib->pm3d_directions[ (3 * idx) + 1] * (float) INT16_MAX);
        directionsTemp[ (3 * idx) + 2] = (int16_t) (ps_calib->pm3d_directions[ (3 * idx) + 2] * (float) INT16_MAX);
    }
    status = pmd_saveArray ("calib_directions", numPixel * 3, directionsTemp) && status ? true : false;
    free (directionsTemp);

    // lensparam
    int *lensParamTemp = (int *) malloc (ps_calib->sizeLensParam * sizeof (int));
    for (size_t idx = 0; idx < ps_calib->sizeLensParam; ++idx)
    {
        lensParamTemp[idx]  = (int) (ps_calib->pv_lensparam[idx] * 1000000.0f);
    }
    status = pmd_saveArray ("calib_lensparam", ps_calib->sizeLensParam, lensParamTemp) && status ? true : false;
    free (lensParamTemp);

    // mask
    status = pmd_saveArray ("calib_mask", numPixel, ps_calib->pm_mask) && status ? true : false;

    // fpn
    uint16_t *fpnTemp = (uint16_t *) malloc (numPixel * sizeof (uint16_t));
    for (uint32_t i = 0; i < numPixel; ++i)
    {
        fpnTemp[i] = (uint16_t) (ps_calib->pm_fpn[i] * 16.0f);
    }
    status = pmd_saveArray ("calib_fpn", numPixel, fpnTemp) && status ? true : false;
    free (fpnTemp);

    for (uint32_t idx = 0; idx < ps_calib->sizeProbeData; ++idx)
    {
        std::stringstream temp;
        temp << ps_calib->pns_probeData[idx].frequency;
        std::string calib_req_str = temp.str() + "Hz";
        temp.str ("");

        // FPPN
        status = pmd_saveArray ("calib_fppn_" + calib_req_str, numPixel, ps_calib->pns_probeData[idx].pm_fppn) && status ? true : false;

        // TempCompensation
        uint8_t size = ps_calib->pns_probeData[idx].sizeTempCompensation;
        status = pmd_saveArray ("calib_TempCompensation_" + calib_req_str, size, ps_calib->pns_probeData[idx].pv_tempCompensation) && status ? true : false;

        // Noise Parameter
        size = ps_calib->pns_probeData[idx].sizeNoiseParamter;
        status = pmd_saveArray ("calib_NoiseParameter_" + calib_req_str, size, ps_calib->pns_probeData[idx].pv_noiseParameter) && status ? true : false;

        // Wiggling correction
        size = ps_calib->pns_probeData[idx].ps_phaseWiggling.size;
        status = pmd_saveArray ("calib_WigglingAmplitude_" + calib_req_str, size, ps_calib->pns_probeData[idx].ps_phaseWiggling.pv_amplitude) && status ? true : false;
        status = pmd_saveArray ("calib_WigglingHarmonic_" + calib_req_str, size, ps_calib->pns_probeData[idx].ps_phaseWiggling.pv_harmonic) && status ? true : false;
        status = pmd_saveArray ("calib_WigglingPhase_" + calib_req_str, size, ps_calib->pns_probeData[idx].ps_phaseWiggling.pv_phase) && status ? true : false;

        if (ps_calib->sizeProbeData > 1)
        {
            // Amplitude Wiggling correction
            size = ps_calib->pns_probeData[idx].ps_amplitudeWiggling.size;
            status = pmd_saveArray ("calib_AmplitudeWigglingAmplitude_" + calib_req_str, size, ps_calib->pns_probeData[idx].ps_amplitudeWiggling.pv_amplitude) && status ? true : false;
            status = pmd_saveArray ("calib_AmplitudeWigglingHarmonic_" + calib_req_str, size, ps_calib->pns_probeData[idx].ps_amplitudeWiggling.pv_harmonic) && status ? true : false;
            status = pmd_saveArray ("calib_AmplitudeWigglingOffset_" + calib_req_str, 1, &ps_calib->pns_probeData[idx].ps_amplitudeWiggling.offset) && status ? true : false;
            status = pmd_saveArray ("calib_AmplitudeWigglingPhase_" + calib_req_str, size, ps_calib->pns_probeData[idx].ps_amplitudeWiggling.pv_phase) && status ? true : false;
        }
    }

    return status;
}

extern "C"
{
    bool sunnyAstonCalibrationLoad(SpectreCalibration **ps_calib, SpectreInput *ps_input, std::string path);
    bool sunnyAstonCalibrationSave (SpectreCalibration *ps_calib, std::string path);
}
//The active functions


inline bool spectreAstonCalibrationLoad (SpectreCalibration **ps_calib, SpectreInput *ps_input, std::string path)
{
    bool status = true;
    size_t size = 0;
    uint8_t sizeProbeData = 0;
    uint8_t *posDepthProbe = (uint8_t *) malloc (ps_input->numFrameSets * sizeof (uint8_t));

    for (uint8_t idx = 0; idx < ps_input->numFrameSets; ++idx)
    {
        if (ps_input->pv_imagerModes[idx] == 0)
        {
            posDepthProbe[sizeProbeData] = idx;
            sizeProbeData++;
        }
    }

    *ps_calib = reinterpret_cast<SpectreCalibration *> (malloc (sizeof (SpectreCalibration)));
    memset (*ps_calib, 0, sizeof (SpectreCalibration));
    (*ps_calib)->sizeProbeData = sizeProbeData;
    (*ps_calib)->pns_probeData = reinterpret_cast<SpectreCalibrationProbeData *> (malloc (sizeof (SpectreCalibrationProbeData) * sizeProbeData));
    memset ( (*ps_calib)->pns_probeData, 0, sizeof (SpectreCalibrationProbeData) * sizeProbeData);

    // dimension information calibrationROI
    status = pmd_loadArray (path + "/calib_CalibrationROI.bin", & ( (*ps_calib)->pv_calibrationROI)) ==  4 && status ? true : false;

    // general information
    status = pmd_loadArray (path + "/calib_date.bin", & ( (*ps_calib)->pc_date)) == 19 && status ? true : false;
    status = pmd_loadArray (path + "/calib_serial.bin", & ( (*ps_calib)->pc_serial)) == 9 && status ? true : false;
    status = pmd_loadArray (path + "/calib_SensorSerial.bin", & ( (*ps_calib)->pc_sensorSerial)) == 19 && status ? true : false;

    status = pmd_loadScalar (path + "/calib_version.bin", & ( (*ps_calib)->version)) == 1 && status ? true : false;
    status = pmd_loadScalar (path + "/calib_type.bin", & ( (*ps_calib)->type)) == 1 && status ? true : false;

    // ps_calib->ation data
    uint32_t width = (*ps_calib)->pv_calibrationROI[2];
    uint32_t height = (*ps_calib)->pv_calibrationROI[3];
    uint32_t numPixel = width * height;

    // directions
    (*ps_calib)->pm3d_directions = (float *) malloc (numPixel * 3 * sizeof (float));
    int16_t *directionsTemp = NULL;
    status = pmd_loadArray (path + "/calib_directions.bin", &directionsTemp) == 3 * numPixel && status ? true : false;
    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        (*ps_calib)->pm3d_directions[ (3 * idx)] = (float) directionsTemp[ (3 * idx)] / (float) INT16_MAX;
        (*ps_calib)->pm3d_directions[ (3 * idx) + 1] = (float) directionsTemp[ (3 * idx) + 1] / (float) INT16_MAX;
        (*ps_calib)->pm3d_directions[ (3 * idx) + 2] = (float) directionsTemp[ (3 * idx) + 2] / (float) INT16_MAX;
    }
    free (directionsTemp);

    // lensparam
    int *lensparamTemp = NULL;
    size = pmd_loadArray (path + "/calib_lensparam.bin", &lensparamTemp);
    (*ps_calib)->sizeLensParam = (uint8_t) size;
    (*ps_calib)->pv_lensparam = (float *) malloc (numPixel * 3 * sizeof (float));
    for (size_t idx = 0; idx < size; ++idx)
    {
        (*ps_calib)->pv_lensparam[idx] = (float) lensparamTemp[idx] / 1000000.0f;
    }
    free (lensparamTemp);

    // mask
    (*ps_calib)->pm_mask = (uint8_t *) malloc (numPixel * sizeof (uint8_t));
    uint8_t *maskTemp = NULL;
    status = pmd_loadArray (path + "/calib_mask.bin", &maskTemp) == numPixel && status ? true : false;
    for (size_t idx = 0; idx < numPixel; ++idx)
    {
        (*ps_calib)->pm_mask[idx] = maskTemp[idx] != 0 ? true : false;
    }
    free (maskTemp);

    // fpn
    (*ps_calib)->pm_fpn = (float *) malloc (numPixel * sizeof (float));
    uint16_t *fpnTemp = NULL;
    status =  pmd_loadArray (path + "/calib_fpn.bin", &fpnTemp) == numPixel && status ? true : false;
    for (uint32_t i = 0; i < numPixel; ++i)
    {
        (*ps_calib)->pm_fpn[i] = (float) fpnTemp[i] / 16.0f;
    }
    free (fpnTemp);

    for (uint32_t idx = 0; idx < sizeProbeData; ++idx)
    {
        std::stringstream temp;
        temp << ps_input->pv_frequencies[posDepthProbe[idx]];
        std::string calib_req_str = temp.str() + "Hz.bin";
        temp.str ("");

        // frequency
        (*ps_calib)->pns_probeData[idx].frequency = ps_input->pv_frequencies[posDepthProbe[idx]];

        // FPPN
        status = pmd_loadArray (path + "/calib_fppn_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].pm_fppn)) == numPixel && status ? true : false;

        // TempCompensation
        size = pmd_loadArray (path + "/calib_TempCompensation_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].pv_tempCompensation));
        (*ps_calib)->pns_probeData[idx].sizeTempCompensation = (uint8_t) size;

        // NoiseParameter
        size = pmd_loadArray (path + "/calib_NoiseParameter_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].pv_noiseParameter));
        (*ps_calib)->pns_probeData[idx].sizeNoiseParamter = (uint8_t) size;

        // Wiggling correction
        auto numWiggles = pmd_loadArray (path + "/calib_WigglingAmplitude_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.pv_amplitude));
        (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.size = (uint8_t) numWiggles;
        status = pmd_loadArray (path + "/calib_WigglingHarmonic_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.pv_harmonic)) == numWiggles && status ? true : false;
        status = pmd_loadArray (path + "/calib_WigglingPhase_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.pv_phase)) == numWiggles && status ? true : false;
        (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.offset = 0.0f;

        if (sizeProbeData > 1)
        {
            // Amplitude Wiggling correction
            uint32_t numWigglesAmp;
            numWigglesAmp = (uint32_t) pmd_loadArray (path + "/calib_AmplitudeWigglingAmplitude_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.pv_amplitude));
            (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.size = (uint8_t) numWigglesAmp;

            status = pmd_loadArray (path + "/calib_AmplitudeWigglingHarmonic_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.pv_harmonic)) == numWigglesAmp && status ? true : false;
            status = pmd_loadScalar (path + "/calib_AmplitudeWigglingOffset_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.offset)) == 1 && status ? true : false;
            status = pmd_loadArray (path + "/calib_AmplitudeWigglingPhase_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.pv_phase)) == numWigglesAmp && status ? true : false;
        }
    }

    free (posDepthProbe);

    return status;
}

inline bool spectreAstonOutputInit (SpectreOutput **ps_output, SpectreInput *ps_input, SpectreCalibration *ps_calib)
{
    *ps_output = reinterpret_cast<SpectreOutput *> (malloc (sizeof (SpectreOutput)));
    memset (*ps_output, 0, sizeof (SpectreOutput));

    uint8_t sizeProbeData = 0;

    for (uint8_t idx = 0; idx < ps_input->numFrameSets; ++idx)
    {
        if (ps_input->pv_imagerModes[idx] == 0)
        {
            sizeProbeData++;
        }
    }

    uint32_t numPixel = ps_input->pv_subROI[2] * ps_input->pv_subROI[3];

    (*ps_output)->numColumns = ps_input->pv_subROI[2];
    (*ps_output)->numRows = ps_input->pv_subROI[3];
    (*ps_output)->pm_amplitude = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_amplitude, 0, sizeof (float) *numPixel);
    (*ps_output)->pm3d_coord = (float *) malloc (numPixel * 4 * sizeof (float));
    memset ( (*ps_output)->pm3d_coord, 0, sizeof (float) * 3 * numPixel);
    (*ps_output)->pm_distance = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_distance, 0, sizeof (float) *numPixel);
    (*ps_output)->pm_distanceNoise = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_distanceNoise, 0, sizeof (float) *numPixel);
    (*ps_output)->pm_intensity = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_intensity, 0, sizeof (float) *numPixel);
    (*ps_output)->pm_flags = (uint32_t *) malloc (numPixel * sizeof (uint32_t));
    memset ( (*ps_output)->pm_flags, 0, sizeof (uint32_t) *numPixel);

    memset ( (*ps_output)->pm_intensity, 0, sizeof (float) *numPixel);
    (*ps_output)->pv_exposureTimesOut = (uint32_t *) malloc ( (ps_input->numFrameSets) * sizeof (uint32_t));
    memset ( (*ps_output)->pv_exposureTimesOut, 0, sizeof (uint32_t) * (ps_input->numFrameSets));

    (*ps_output)->pns_probeData = reinterpret_cast<SpectreOutputProbeData *> (malloc (sizeProbeData * sizeof (SpectreOutputProbeData)));
    memset ( (*ps_output)->pns_probeData, 0, sizeof (SpectreOutputProbeData) * sizeProbeData);

    (*ps_output)->sizeProbeData = sizeProbeData;
    for (uint32_t idx = 0; idx < sizeProbeData; ++idx)
    {
        (*ps_output)->pns_probeData[idx].pm_amplitude = (float *) malloc (sizeof (float) * numPixel);
        memset ( (*ps_output)->pns_probeData[idx].pm_amplitude, 0, sizeof (float) * numPixel);
        (*ps_output)->pns_probeData[idx].pm_amplitudeNoise = (float *) malloc (sizeof (float) * numPixel);
        memset ( (*ps_output)->pns_probeData[idx].pm_amplitudeNoise, 0, sizeof (float) * numPixel);
        (*ps_output)->pns_probeData[idx].pm_distance = (float *) malloc (sizeof (float) * numPixel);
        memset ( (*ps_output)->pns_probeData[idx].pm_distance, 0, sizeof (float) * numPixel);
        (*ps_output)->pns_probeData[idx].pm_distanceNoise = (float *) malloc (sizeof (float) * numPixel);
        memset ( (*ps_output)->pns_probeData[idx].pm_distanceNoise, 0, sizeof (float) * numPixel);
    }

    return true;
}

inline bool spectreAstonInputSave (SpectreInput *ps_input, std::string path)
{

    uint32_t numPixel = ps_input->pv_sensorROI[2] * ps_input->pv_sensorROI[3];
    bool status = true;

    status = pmd_saveArray ("input_SensorROI", 4, ps_input->pv_sensorROI) && status ? true : false;
    status = pmd_saveArray ("input_SubROI", 4, ps_input->pv_subROI) && status ? true : false;
    status = pmd_saveArray ("input_Temperature", 1, ps_input->p_temperature) && status ? true : false;
    status = pmd_saveArray ("input_NumFrameSets", 1, &ps_input->numFrameSets) && status ? true : false;
    status = pmd_saveArray ("input_NumFrames", ps_input->numFrameSets, ps_input->pv_numFrames) && status ? true : false;

    // raw data
    uint8_t count = 0;
    for (uint8_t fs_idx = 0; fs_idx < ps_input->numFrameSets; ++fs_idx)
    {
        for (uint8_t f_idx = 0; f_idx < ps_input->pv_numFrames[fs_idx]; ++f_idx, ++count)
        {
	    pmd_printf("dnx(%d): input_RawData: fs_idx (%d), f_idx (%d), numPixel (%d)\n", __LINE__, fs_idx, f_idx, numPixel);
            status = pmd_saveArray ("input_RawData_" + pmd_numberToString (count), numPixel, ps_input->pnnm_rawData[fs_idx][f_idx]) && status ? true : false;
        }
    }

    // phases
    for (uint8_t idx = 0; idx < ps_input->numFrameSets; ++idx)
    {
        status = pmd_saveArray ("input_Phases_" + pmd_numberToString (idx), ps_input->pv_numFrames[idx], ps_input->pnv_phases[idx]) && status ? true : false;
    }

    uint8_t size = ps_input->numFrameSets;
    status = pmd_saveArray ("input_InExposureTimes", size, ps_input->pv_exposureTimesIn);
    status = pmd_saveArray ("input_Frequencies", size, ps_input->pv_frequencies);
    status = pmd_saveArray ("input_IlluminationModes", size, ps_input->pv_illuminationModes);
    status = pmd_saveArray ("input_ImagerModes", size, ps_input->pv_imagerModes);
    status = pmd_saveArray ("input_FrameSetComposition", size, ps_input->pv_FrameSetComposition);
    status = pmd_saveArray ("input_ExposureLimits", 2, ps_input->pv_exposureLimits);
    status = pmd_saveArray ("input_Type", 1, & (ps_input->type));
    status = pmd_saveArray ("input_Version", 1, & (ps_input->version));

    return status;
}

inline bool spectreAstonInputLoad (SpectreInput **ps_input, std::string path)
{
    bool status = true;
    size_t size = 0;
    size_t numPixel = 0;

    (*ps_input) = reinterpret_cast<SpectreInput *> (malloc (sizeof (SpectreInput)));

    status = pmd_loadArray (path + "/input_SensorROI.bin", & ( (*ps_input)->pv_sensorROI)) == 4 && status ? true : false;
    status = pmd_loadArray (path + "/input_SubROI.bin", & ( (*ps_input)->pv_subROI)) == 4 && status ? true : false;
    if (!status)
    {
        return status;
    }

    numPixel = (*ps_input)->pv_sensorROI[2] * (*ps_input)->pv_sensorROI[3];

    (*ps_input)->p_temperature = (float *) malloc (sizeof (float));
    if (!access("/data/load_input_Temperature.txt", R_OK)) {
       status = pmd_loadScalar (path + "/input_Temperature.bin", (*ps_input)->p_temperature) == 1 && status ? true : false;
       pmd_printf("load from fake binary Temp\n");
    } else {
	float tmp = temperature_read();
	memcpy((*ps_input)->p_temperature, &tmp, 4);

        pmd_printf("load from real hardware Temp\n");
       }


    if (use_single_frame_mode == 1)
       status = pmd_loadScalar (path + "/input_Single_NumFrameSets.bin", & ( (*ps_input)->numFrameSets)) == 1 && status ? true : false;
    else
       status = pmd_loadScalar (path + "/input_NumFrameSets.bin", & ( (*ps_input)->numFrameSets)) == 1 && status ? true : false;

    size = (size_t) (*ps_input)->numFrameSets;

    if (use_single_frame_mode == 1)
       status = pmd_loadArray (path + "/input_Single_NumFrames.bin", & ( (*ps_input)->pv_numFrames)) == size && status ? true : false;
    else
       status = pmd_loadArray (path + "/input_NumFrames.bin", & ( (*ps_input)->pv_numFrames)) == size && status ? true : false;

    (*ps_input)->pnnm_rawData = (uint16_t ** *) malloc ( (*ps_input)->numFrameSets * sizeof (uint16_t **));

    // rawData
    uint32_t total_frame;
    uint32_t count = 0;
    uint32_t my_f_idx = 0;
    uint16_t *p_dst, *p_src, *total;

    if (use_single_frame_mode == 1)
	total_frame = 5;
    else
	total_frame = 9;

#if (DEBUG_READ_FILE==1)
    static uint32_t my_f_cnt = 0;
    status = pmd_loadArray (path + "/input_RawData_all_" + pmd_numberToString (my_f_cnt) + ".bin", &total) == (numPixel * total_frame) && status ? true : false;

    if (status == true)
	    pmd_printf("dnx(%d): input_RawData(%d): load data success\n", __LINE__, my_f_cnt);
    else
	    pmd_printf("dnx(%d): input_RawData(%d): load data fail\n", __LINE__, my_f_cnt);


    my_f_cnt++;
#else
    // read frome camera buf
    total = (uint16_t *) malloc(numPixel * 9 * sizeof(uint16_t));
    camera_getbuf((char *)total, numPixel * 9 * sizeof(uint16_t));
    pmd_printf("dnx(%d): load data from camera success\n", __LINE__ );
#endif

    for (uint8_t fs_idx = 0; fs_idx < (*ps_input)->numFrameSets; ++fs_idx)
    {
        (*ps_input)->pnnm_rawData[fs_idx] = (uint16_t **) malloc ( (*ps_input)->pv_numFrames[fs_idx] * sizeof (uint16_t *));
        for (uint8_t f_idx = 0; f_idx < (*ps_input)->pv_numFrames[fs_idx]; ++f_idx, ++count)
        {

            //status = pmd_loadArray (path + "/input_RawData_" + pmd_numberToString (count) + ".bin", & ( (*ps_input)->pnnm_rawData[fs_idx][f_idx])) == numPixel && status ? true : false;
            (*ps_input)->pnnm_rawData[fs_idx][f_idx] = (uint16_t *) malloc(numPixel * sizeof(uint16_t));
	    p_dst = (uint16_t *) (*ps_input)->pnnm_rawData[fs_idx][f_idx];
	    p_src = (uint16_t *) (total + my_f_idx * numPixel);

  	  	if (my_f_idx == 2 && g_gray_buf != NULL)
	        	memcpy((void *)g_gray_buf, (const void *) p_src, numPixel * 2); 

	    pmd_printf("dnx(%d): input_RawData: fs_idx (%d), f_idx (%d), numPixel (%d), point total src(%p %p)\n", __LINE__,
	    	fs_idx, f_idx, numPixel,
		total, p_src);

            for (uint32_t p_idx = 0; p_idx < numPixel; p_idx++) {
	         *p_dst = (*p_src >> 4);
		 p_dst++;
		 p_src++;
	    }

	    my_f_idx++;

	    #if  0// shift right 4
	    {
	    char filename[32];
	    FILE *fp;

	    snprintf(filename,32, "mydump_%d.bin", my_f_idx);

	    fp= fopen(filename, "wb+");
	    fwrite((*ps_input)->pnnm_rawData[fs_idx][f_idx], numPixel, 2, fp);
	    fclose(fp);

	    }
	    #endif
        }
    }
    free(total);
    // phases
    (*ps_input)->pnv_phases = (uint16_t **) malloc ( (*ps_input)->numFrameSets * sizeof (uint16_t *));
    for (uint8_t idx = 0; idx < (*ps_input)->numFrameSets; ++idx)
    {
        size = (*ps_input)->pv_numFrames[idx];

    if (use_single_frame_mode == 1)
        status = pmd_loadArray (path + "/input_Single_Phases_" + pmd_numberToString (idx) + ".bin", & ( (*ps_input)->pnv_phases[idx])) ==  size && status ? true : false;
    else
        status = pmd_loadArray (path + "/input_Phases_" + pmd_numberToString (idx) + ".bin", & ( (*ps_input)->pnv_phases[idx])) ==  size && status ? true : false;
    }


    size = (size_t) (*ps_input)->numFrameSets;
#if 0

    if (use_single_frame_mode == 1)
        status = pmd_loadArray (path + "/input_Single_InExposureTimes.bin", & ( (*ps_input)->pv_exposureTimesIn)) ==  size && status ? true : false;
    else
        status = pmd_loadArray (path + "/input_InExposureTimes.bin", & ( (*ps_input)->pv_exposureTimesIn)) ==  size && status ? true : false;
#else
	(*ps_input)->pv_exposureTimesIn = (uint32_t *) malloc (3 * sizeof (uint32_t));
	memcpy((*ps_input)->pv_exposureTimesIn, &spectre_exposureTimes, 12);

	pmd_printf("dnx(%d): exposureTimesIn: x,y,z(%d, %d, %d)\n", __LINE__, spectre_exposureTimes.x, spectre_exposureTimes.y, spectre_exposureTimes.z);
#endif
    status = pmd_loadArray (path + "/input_Frequencies.bin", & ( (*ps_input)->pv_frequencies)) ==  size && status ? true : false;

    if (use_single_frame_mode == 1) {
        status = pmd_loadArray (path + "/input_Single_IlluminationModes.bin", & ( (*ps_input)->pv_illuminationModes)) ==  size && status ? true : false;
        status = pmd_loadArray (path + "/input_Single_ImagerModes.bin", & ( (*ps_input)->pv_imagerModes)) ==  size && status ? true : false;
    } else {
        status = pmd_loadArray (path + "/input_IlluminationModes.bin", & ( (*ps_input)->pv_illuminationModes)) ==  size && status ? true : false;
        status = pmd_loadArray (path + "/input_ImagerModes.bin", & ( (*ps_input)->pv_imagerModes)) ==  size && status ? true : false;
    }
    status = pmd_loadArray (path + "/input_FrameSetComposition.bin", & ( (*ps_input)->pv_FrameSetComposition)) ==  size && status ? true : false;
    status = pmd_loadArray (path + "/input_ExposureLimits.bin", & ( (*ps_input)->pv_exposureLimits)) ==  2 && status ? true : false;
    status = pmd_loadScalar (path + "/input_Type.bin", & ( (*ps_input)->type)) ==  1 && status ? true : false;
    status = pmd_loadScalar (path + "/input_Version.bin", & ( (*ps_input)->version)) ==  1 && status ? true : false;

    return status;
}

inline bool spectreAstonCalibrationFree (SpectreCalibration *ps_calib)
{
    free (ps_calib->pv_calibrationROI);
    free (ps_calib->pm3d_directions);
    free (ps_calib->pv_lensparam);
    free (ps_calib->pm_mask);
    free (ps_calib->pm_fpn);
    free (ps_calib->pc_serial);
    free (ps_calib->pc_date);
    free (ps_calib->pc_sensorSerial);


    for (uint32_t idx = 0; idx < ps_calib->sizeProbeData; ++idx)
    {
        free (ps_calib->pns_probeData[idx].pm_fppn);
        free (ps_calib->pns_probeData[idx].pv_tempCompensation);
        free (ps_calib->pns_probeData[idx].ps_phaseWiggling.pv_amplitude);
        free (ps_calib->pns_probeData[idx].ps_phaseWiggling.pv_harmonic);
        free (ps_calib->pns_probeData[idx].ps_phaseWiggling.pv_phase);
        free (ps_calib->pns_probeData[idx].pv_noiseParameter);
        if (ps_calib->sizeProbeData > 1)
        {
            free (ps_calib->pns_probeData[idx].ps_amplitudeWiggling.pv_amplitude);
            free (ps_calib->pns_probeData[idx].ps_amplitudeWiggling.pv_harmonic);
            free (ps_calib->pns_probeData[idx].ps_amplitudeWiggling.pv_phase);
        }
    }

    free (ps_calib->pns_probeData);
    free (ps_calib);

    return true;
}

inline bool spectreAstonInputFree (SpectreInput *ps_input)
{
    free (ps_input->pv_sensorROI);
    free (ps_input->pv_subROI);
    free (ps_input->p_temperature);

    uint32_t count = 0;
    for (uint8_t fs_idx = 0; fs_idx < ps_input->numFrameSets; ++fs_idx)
    {
        for (uint8_t f_idx = 0; f_idx < ps_input->pv_numFrames[fs_idx]; ++f_idx, ++count)
        {
            free (ps_input->pnnm_rawData[fs_idx][f_idx]);
        }
        free (ps_input->pnnm_rawData[fs_idx]);
    }
    free (ps_input->pnnm_rawData);

    for (uint8_t idx = 0; idx < ps_input->numFrameSets; ++idx)
    {
        free (ps_input->pnv_phases[idx]);
    }
    free (ps_input->pv_numFrames);
    free (ps_input->pnv_phases);

    free (ps_input->pv_exposureTimesIn);
    free (ps_input->pv_frequencies);
    free (ps_input->pv_illuminationModes);
    free (ps_input->pv_imagerModes);
    free (ps_input->pv_FrameSetComposition);
    free (ps_input->pv_exposureLimits);
    free (ps_input);

    return true;
}

inline bool spectreAstonOutputFree (SpectreOutput *ps_output)
{
    for (uint32_t idx = 0; idx < ps_output->sizeProbeData; ++idx)
    {
        free (ps_output->pns_probeData[idx].pm_amplitude);
        free (ps_output->pns_probeData[idx].pm_amplitudeNoise);
        free (ps_output->pns_probeData[idx].pm_distance);
        free (ps_output->pns_probeData[idx].pm_distanceNoise);
    }
    free (ps_output->pns_probeData);

    free (ps_output->pm_amplitude);
    free (ps_output->pm3d_coord);
    free (ps_output->pm_distance);
    free (ps_output->pm_distanceNoise);
    free (ps_output->pm_flags);
    free (ps_output->pv_exposureTimesOut);
    free (ps_output->pm_intensity);
    free (ps_output);

    return true;
}

inline bool spectreAstonIntermediateInit (struct SpectreIntermediate **ps_inter, struct SpectreInput *ps_input)
{
    return spectreIntermediateInit (ps_input, ps_inter) == SPECTRE_PROCESSING_SUCCESS;
}

inline void spectreAstonIntermediateFree (struct SpectreIntermediate *ps_inter)
{
    spectreIntermediateFree (ps_inter);
}

inline bool spectreAstonParameterFree (SpectreParameter *params)
{
    free (params);
    return true;
}
