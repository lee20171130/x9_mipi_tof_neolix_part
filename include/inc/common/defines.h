/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/




// Export Definition
#ifdef _WIN32
#ifdef SPECTRE_SHARED
#ifdef SPECTRE_EXPORT
#define PMDDCLSPEC __declspec( dllexport )
#else // SPECTRE_EXPORT
#define PMDDCLSPEC __declspec( dllimport  )
#endif // SPECTRE_EXPORT
#else // SPECTRE_SHARED
#define PMDDCLSPEC
#endif // SPECTRE_SHARED
#else // _WIN32
#define PMDDCLSPEC
#endif // _WIN32
