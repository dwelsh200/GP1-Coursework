#include "errorlogger.h"
#include <math.h>

const char ErrorLogger::Filename[]="error.log";
ErrorLogger ErrorLogger::instance;
int ErrorLogger::LineCount=0;


ErrorLogger::ErrorLogger()
{
#ifdef LOGGING
	file.open(Filename);
#endif
}

ErrorLogger::~ErrorLogger()
{
#ifdef LOGGING
	file.close();
#endif
}

void ErrorLogger::Writeln(const char text[])
{
	Write(text);
	Write("\n");
}

void ErrorLogger::Write(const char text[])
{
#ifdef LOGGING
	if(LineCount<MAXLINES)
	{
		OutputDebugString(text);
		instance.file << text;
		if(++LineCount == MAXLINES)
		{
			OutputDebugString(TEXT("\nErrorLogger limit reached. Who taught you to progam?"));
			instance.file << "\nErrorLogger limit reached. Who taught you to progam?";
			instance.file.flush();
		}
	}
#endif
#ifdef SLOWLOG
	instance.file.flush();
#endif
}

void ErrorLogger::Writeln(double num)
{
	Write(num);
	Write("\n");
}

void ErrorLogger::Write(double num)
{
#ifdef LOGGING
	char buffer[32];
	sprintf_s( buffer,32, "%.8g", num );
	Write(buffer);
#endif
}

