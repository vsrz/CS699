#include "Logger.h"
#include <ctime>
#include "md5_wrapper.h"
#include "Dateutils.h"

Logger& Logger::get()
{
	static Logger instance;
	return instance;

}
void Logger::setLogFilename(std::string filename)
{
	mFilename = filename;
}

// Writes the log to disk then flushes it
void Logger::write()
{
	if (mFilename.empty())
	{
		// Really horrible way of generating a random filename
		unsigned long seed = (unsigned long)time(NULL);
		srand((unsigned int)seed);
		int num = rand() % (30000);
		md5wrapper m;
		
		//mFilename = m.getHashFromString(std::to_string(num)) + ".log";
		mFilename = "playdata.log";
	}
	mLogdata.append("End of play session\n==================\n\n");
	Fileutils::writeFileToDisk(mLogdata, mFilename);
	this->clear();

}

// Append the entry to the logfile
void Logger::log(std::string entry)
{
	mLogdata.append(Dateutils::getDateTime() + entry + "\n");
}

void Logger::clear()
{
	mLogdata.clear();
}