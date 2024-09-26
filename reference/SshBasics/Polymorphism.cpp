#include "SshBasics.h"

// SshPolymorphism:
// Demonstrates polymorphism and RTTI for Ssh objects.

void SshPolymorphism(SshSession& session)
{
	constexpr const char *path = "/readme.txt";
	
	Array<Ssh> channels;
	
	channels.Create<Scp>(session);
	channels.Create<SFtp>(session);
	channels.Create<SshExec>(session);

	for(Ssh& channel : channels){
		if(channel.Is<Scp>()) {
			RLOG("\nFound: Scp object");
			RLOG("-----------------\n");
			RLOG(channel.To<Scp>().LoadFile(path));
		}
		else
		if(channel.Is<SFtp>()) {
			RLOG("\nFound: Sftp object");
			RLOG("------------------\n");
			RLOG(channel.To<SFtp>().GetInfo(path).GetName());
		}
		else
		if(channel.Is<SshExec>()) {
			RLOG("\nFound: Exec object");
			RLOG("------------------\n");
			String out, err;
			channel.To<SshExec>().Execute("ls -l", out, err);
			RLOG(out);
			RLOG(err);
		}
		if(channel.IsError()) {
			RLOG("Operation failed. Reason: " << channel.GetErrorDesc());
		}
	
	}
}