/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#include <sample/spectreSampleCalc.hpp>

#define SPECTRE_PATH "/data/spectre/sample"
const std::string strPath = SPECTRE_PATH;
std::string spectre::sample::getDefaultDataPath()
{
   // SystemIOReal io;
    //auto exeDir = pmd_getDirectory (io.getOwnExePath());
    //std::string subPath (char_CAST (DATA_PATH));
    //return exeDir + subPath;
	//const std::string strPath = "./data";
	return strPath;
	
}
  
void spectre::sample::initMemory (struct Data &data)
{
    const std::string calibDir = "Process_Calib";
    const std::string paramDir = "Process_Param";
    const std::string inputDir = "Process_Input";
    const std::string testDir = "Process_Calib_test"; //added by zhudm

    pmd_printf ("\n");
    pmd_printf ("Reading sample data from: %s\n", data.workingDir.c_str());
    pmd_printf ("Initialize Memory \n");

    // initializiation
    spectreAstonInputLoad (&data.ps_input, data.workingDir + "/" + inputDir);
    spectreAstonParameterLoad (&data.ps_param, data.workingDir + "/" + paramDir);
    pmd_printf ("dnx init,  dir: %s\n", (data.workingDir + "/" + testDir).c_str());


    std::ifstream file (strPath + "/" + testDir + "/calib_CalibrationROI.bin", std::fstream::binary  | std::fstream::in);

    if (!file.good())
    {
        //First Run, transform eeprom to speparate files
        pmd_printf ("dnx transform eeprom, first run\n");

	    sunnyAstonCalibrationLoad (&data.ps_calib, data.ps_input, data.workingDir + "/" + testDir);
	    sunnyAstonCalibrationSave(data.ps_calib, data.workingDir + "/" + testDir);
    }
	else
	{
		//Calibration data exist
		pmd_printf ("dnx use eeprom, re-run\n");
		spectreAstonCalibrationLoad (&data.ps_calib, data.ps_input, data.workingDir + "/" + testDir);
	}
    
    pmd_printf ("dnx init,  dir: %s\n", (data.workingDir + "/" + calibDir).c_str());
    spectreAstonOutputInit (&data.ps_output, data.ps_input, data.ps_calib);
    pmd_printf ("dnx init, line %d\n", __LINE__);
    spectreAstonIntermediateInit (&data.ps_inter, data.ps_input);
    pmd_printf ("dnx init, line %d\n", __LINE__);
}

void spectre::sample::freeMemory (struct Data &data)
{
    pmd_printf ("\n");
    pmd_printf ("Free Memory \n");

    spectreAstonIntermediateFree (data.ps_inter);
    spectreAstonCalibrationFree (data.ps_calib);
    spectreAstonParameterFree (data.ps_param);
    spectreAstonOutputFree (data.ps_output);
    spectreAstonInputFree (data.ps_input);
}

void spectre::sample::runProcessing (struct Data &data)
{
    pmd_printf ("\n");
    pmd_printf ("Run spectre processing\n");

    // sensor data ps_interessing
    spectreAstonRun (data.ps_input, data.ps_calib, data.ps_param, data.ps_inter, data.ps_output);
}

void spectre::sample::calcMeanDistanceAndValidPixels (uint32_t numPixels, float *distances, uint32_t *flags, struct Data &data)
{
    pmd_printf ("\n");
    pmd_printf ("Run Calculation of mean distance and valid pixels\n");

    for (uint32_t i = 0; i < numPixels; i++)
    {
        if (!flags[i])
        {
            data.meanDistance += distances[i];
            data.numValidPixels++;
        }
    }

    data.meanDistance /= (float) data.numValidPixels;
}

void spectre::sample::calcMeanTimeAndFps (struct Data &data, bool noStop)
{
    pmd_printf ("\n");
    pmd_printf ("Run Calculation of current fps and mean time\n");

    Timer timer;
    uint32_t iterations = 100;
    data.vfps.clear();

    std::chrono::seconds fiveSeconds (5);
    auto frStart = std::chrono::steady_clock::now();
    for (uint32_t i = 0, frCount = 1; noStop ? true : i < iterations; i++, ++frCount)
    {
        // sensor data ps_interessing
        timer.start();
        spectreAstonRun (data.ps_input, data.ps_calib, data.ps_param, data.ps_inter, data.ps_output);
        timer.stop();
        auto sleepPeriod = std::chrono::milliseconds (196) - timer.getLastDur();
        std::this_thread::sleep_for (sleepPeriod);
        auto frCurrent = std::chrono::steady_clock::now();
        auto frDuration = std::chrono::duration_cast<std::chrono::milliseconds> (frCurrent - frStart);
        if (frDuration >= fiveSeconds)
        {
            data.vfps.push_back (static_cast<double> (frCount) / (static_cast<double> (frDuration.count()) / 1000.0));
            frStart = frCurrent;
            frCount = 0;
        }
    }

    // acquire calculation mean time
    data.meanTime = std::chrono::duration_cast<flMilliseconds> (timer.getMeanTime()).count();
}

void spectre::sample::printMeanDistanceAndValidPixels (struct Data &data)
{
    pmd_printf ("Valid Pixel: %d \n", data.numValidPixels);
    pmd_printf ("Mean distance: %f \n", data.meanDistance);
}

void spectre::sample::printMeanTimeAndFps (struct Data &data)
{
    for (size_t i = 0; i < data.vfps.size(); i++)
    {
        pmd_printf ("current frame rate is %f fps\n", data.vfps.at (i));
    }
    pmd_printf ("Average Time [ms]: %f \n", data.meanTime);
}
