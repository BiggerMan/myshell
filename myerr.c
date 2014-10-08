#include "myerr.h"
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

static  void err_doit(int, int, const char*, va_list);
void err_ret(const char *fmt, ...)
{
	va_list ap; /* for ... */

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}

void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char buff[MAXLINE];
	vsnprintf(buff, MAXLINE, fmt, ap);
	if(errnoflag)
		snprintf(buff+strlen(buff), MAXLINE-strlen(buff), ": %s", strerror(error));
	strcat(buff,"\n");
	fflush(stdout);/*in case  stdout and stderr are same*/
	fputs(buff, stderr);
	fflush(NULL);/*fflush all stdio output streams*/
}
