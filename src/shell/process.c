#include <shell/process.h>

#include <stdio.h>

#include <time.h>
#include <userenv.h>
#pragma comment(lib, "userenv.lib")

BOOL Execute(TCHAR *commandLine) {
  // Handle for the current process token
  HANDLE hToken = NULL;
  // Structures for process creation
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  // Required access rights for creating a process with a token
  DWORD desiredAccess = TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_QUERY |
                        TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID;

  // Get the token of the current process
  if (!OpenProcessToken(GetCurrentProcess(), desiredAccess, &hToken)) {
    _tprintf(_T("OpenProcessToken failed: %ld\n"), GetLastError());
    return FALSE;
  }

  // Initialize the STARTUPINFO structure
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  // Specify the desktop where the process will run
  si.lpDesktop = _T("winsta0\\default");

  // Create a new process under the user context specified by the token
  if (!CreateProcessAsUser(hToken, // Token handle for the user context
                           NULL,   // Application name (NULL uses command line)
                           commandLine, // Command line string
                           NULL,        // Process security attributes
                           NULL,        // Thread security attributes
                           FALSE,       // Inherit handles flag
                           0,           // Creation flags
                           NULL,        // Environment block
                           NULL,        // Current directory
                           &si,         // Startup info
                           &pi          // Process information
                           )) {
    _tprintf(_T("CreateProcessAsUser failed: %ld\n"), GetLastError());
    CloseHandle(hToken);
    return FALSE;
  }

  // Wait for the created process to complete
  WaitForSingleObject(pi.hProcess, INFINITE);

  // Clean up handles
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  CloseHandle(hToken);

  return TRUE;
}

DWORDLONG MeasureProcessTime(TCHAR *commandLine) {
  LARGE_INTEGER start, end;
  LARGE_INTEGER frequency;
  double elapsedTime;

  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start);

  if (!Execute(commandLine)) {
    return EXECUTION_ERROR;
  }

  QueryPerformanceCounter(&end);

  elapsedTime =
      ((double)(end.QuadPart - start.QuadPart) / frequency.QuadPart) * 1e+9;

  return (DWORDLONG)elapsedTime;
}
