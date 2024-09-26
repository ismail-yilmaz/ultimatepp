#include "SshBasics.h"

// ExecListDir:
// Demonstrates a remote command execution.

void ExecListDir(SshSession& session)
{
	const char *cmdline = "ls -l /pub/example";
	
	SshExec exec(session);
	String cout, cerr;
	int exit_code = exec(cmdline, cout, cerr);
	if(!exec.IsError()) {
		DUMP(exit_code);
		RLOG("Stdout:\n" << cout);
		RLOG("Stderr:\n" << cerr);
		return;
	}
	RLOG(exec.GetErrorDesc());
	
	// Or you can use one of the helper functions instead:
	// RLOG("Stdout:\n" << SshExecute(session, cmdline));
}