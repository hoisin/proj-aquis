//--------------------------------------------------------------------------
//
//	20/10/2015
//
//	Simple Debugging Tool. Outputs log to specified text file
//	Singleton access
//
//	Author: Matt © 2015
//
//--------------------------------------------------------------------------

#ifndef __CDEBUGLOG_H_
#define __CDEBUGLOG_H__

#include <string>
#include <fstream>

class CDebugLog
{
public:
	~CDebugLog();

	static CDebugLog* GetInstance();

	void Release();

	bool Initialise(const std::string& fileDir);

	void WriteWarning(const std::string& log, bool bTimeStamp = true);
	void WriteError(const std::string& log, bool bTimeStamp = true);

private:
	CDebugLog();

	void StartLog();
	void EndLog();

	void WriteEntry(const std::string& log);
	void WriteTimeStampEntry(const std::string& logTextEntry);

private:
	static CDebugLog* _instance;

	bool m_bInit;
	std::string m_fileName;
	std::fstream m_fileStream;
};

#define CDEBUGLOG CDebugLog::GetInstance()


#endif