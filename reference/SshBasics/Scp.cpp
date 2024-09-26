#include "SshBasics.h"

// ScpGet:
// Demonstrates a file download using scp.

void ScpGet(SshSession& session)
{
	const char *path = "the/full/path/of/the/file/to/downlad";
	
	Scp scp(session);
	String file = scp.LoadFile(path);
	RLOG((!scp.IsError() ? file : scp.GetErrorDesc()));
}