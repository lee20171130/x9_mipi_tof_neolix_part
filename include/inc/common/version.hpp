#pragma once

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* Retrieves current version number
*/
PMDDCLSPEC const char *getSpectreVersion ();

/**
* Returns the git description string of
* revision that was used to build the binary
*/
PMDDCLSPEC const char *getSpectreGitDescription ();

#ifdef __cplusplus
}
#endif
