#include "SshBasics.h"

// SFtpTransparency:
// Demonstrates  access to sftp directory hierarcy in a file-system-agnostic (transparent) way.

void ReadDirEntries(FileSystemInfo& fsi, const String& path)
{
	int maxentry = 5;
	for(FileSystemInfo::FileInfo entry : fsi.Find(path, maxentry)) {
		DUMP(entry.filename);
		DUMP(entry.is_folder);
		DUMP(entry.length);
		DUMP(entry.last_access_time);
		//...
	}
}

void SFtpTransparency(SshSession& session)
{
	RLOG("Local file system objects----------------------------------------------------------");
	ReadDirEntries(StdFileSystemInfo(), GetCurrentDirectory());

	SFtp sftp(session);
	SFtpFileSystemInfo sfsi(sftp);
	
	RLOG("Remote file system objects---------------------------------------------------------");
	ReadDirEntries((FileSystemInfo&) sfsi, "/pub/example/*.png");
	
	if(sftp.IsError())
		RLOG(sftp.GetErrorDesc());
}
