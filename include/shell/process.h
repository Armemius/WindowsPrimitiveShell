#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <tchar.h>
#include <windows.h>

#define EXECUTION_ERROR ((DWORDLONG)(-1))

BOOL Execute(TCHAR *commandLine);

DWORDLONG MeasureProcessTime(TCHAR *commandLine);

#endif
