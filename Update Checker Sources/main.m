//
//  main.m
//  Perian
//
//  Created by Augie Fackler on 1/7/07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include <sys/stat.h>
#include <unistd.h>

#define lockPath "/tmp/PerianUpdateLock"

static int fp = -1;

static void deleteLock()
{
	close(fp);
	unlink(lockPath);
}

int main(int argc, char *argv[])
{
	fp = open(lockPath, O_CREAT | O_EXCL);
	if(fp == -1)
	{
		struct stat lockfile;
		time_t current = time(NULL);
		if(stat(lockPath, &lockfile))
		{
			if(lockfile.st_ctimespec.tv_sec + 60*60 > current)  //Only pay attention to lock file if it is no more than an hour old
			{
				unlink(lockPath);
				fp = open(lockPath, O_CREAT | O_EXCL | O_EXLOCK);
			}
		}		
	}
	if(fp == -1)
		return 0;
	
	atexit(deleteLock);

	int ret = NSApplicationMain(argc,  (const char **) argv);
	
	return ret;
}
