# Primitive Windows shell

This is a implementation of a most primitive Windows shell. It is a simple
command line interpreter that reads, interprets, and executes commands from the
user. It is a simple implementation of a shell that can be used to understand
the basic concepts of a shell.

The shell is implemented in C and uses the Windows API
([CreateProcessAsUser](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessasusera)
for command execution) to interact with the OS.
