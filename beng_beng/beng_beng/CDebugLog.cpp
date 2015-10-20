#include "CDebugLog.h"
#include <ctime>

CDebugLog* CDebugLog::_instance = nullptr;


CDebugLog::CDebugLog() : m_bInit(false), m_fileName("")
{
}


CDebugLog::~CDebugLog()
{
	if (m_fileStream.is_open())
		m_fileStream.close();

	m_bInit = false;
}


//------------------------------------------------------------------
//
//	GetInstance(..)
//
//	Returns instance to the debugger tool
//
//------------------------------------------------------------------
CDebugLog* CDebugLog::GetInstance()
{
	if (_instance)
		return _instance;
	else {
		_instance = new CDebugLog;
		return _instance;
	}
}


//------------------------------------------------------------------
//
//	Release(..)
//
//	Frees the debugger tool. Called ideally at the end of the application
//
//------------------------------------------------------------------
void CDebugLog::Release()
{
	if (_instance) {
		EndLog();
		delete _instance;
		_instance = nullptr;
	}
}


//------------------------------------------------------------------
//
//	Initialise(..)
//
//	Params:
//	fileDir		-	Location of the text file to write to
//
//	Initialisation of the debugger tool
//
//------------------------------------------------------------------
bool CDebugLog::Initialise(const std::string& fileDir)
{
	if (!m_bInit) {
		// Attempt to open/create file.
		// If existing, clear all contents
		m_fileStream.open(fileDir.c_str(), std::fstream::out | std::fstream::trunc);

		if (!m_fileStream.is_open())
			return false;

		m_bInit = true;
		StartLog();
	}
	else
		WriteTimeStampEntry("Initialisation attempt on DebugLog made when already initialised!");

	return true;
}


//------------------------------------------------------------------
//
//	WriteWarning(..)
//
//	Params:
//	log			-	Text to log
//	bTimeStamp	-	To include time stamp in entry
//
//	Writes warning entry to text file
//
//------------------------------------------------------------------
void CDebugLog::WriteWarning(const std::string& log, bool bTimeStamp)
{
	if (bTimeStamp)
		WriteTimeStampEntry("Warning: " + log);
	else
		WriteEntry("Warning: " + log);
}


//------------------------------------------------------------------
//
//	WriteError(..)
//
//	Params:
//	log			-	Text to log
//	bTimeStamp	-	To include time stamp in entry
//
//	Writes error entry to text file
//
//------------------------------------------------------------------
void CDebugLog::WriteError(const std::string& log, bool bTimeStamp)
{
	if (bTimeStamp)
		WriteTimeStampEntry("Error: " + log);
	else
		WriteEntry("Error: " + log);
}


//------------------------------------------------------------------
//
//	StartLog(..)
//
//	Writes header entry
//
//------------------------------------------------------------------
void CDebugLog::StartLog()
{
	if (m_bInit) {
		time_t rawTime;
		struct tm timeinfo;
		char buffer[32];

		time(&rawTime);
		localtime_s(&timeinfo, &rawTime);
		asctime_s(buffer, &timeinfo);
		m_fileStream << "Debug Log Started: " << buffer << "\n";
	}
}


//------------------------------------------------------------------
//
//	EndLog(..)
//
//	Writes foot entry
//
//------------------------------------------------------------------
void CDebugLog::EndLog()
{
	if (m_bInit) {
		time_t rawTime;
		struct tm timeinfo;
		char buffer[32];

		time(&rawTime);
		localtime_s(&timeinfo, &rawTime);
		asctime_s(buffer, &timeinfo);
		m_fileStream << "\nDebug Log Ended: " << buffer;
	}
}


//------------------------------------------------------------------
//
//	WriteEntry(..)
//
//	Params:
//	log			-	Text to log
//
//	Writes entry to text file
//
//------------------------------------------------------------------
void CDebugLog::WriteEntry(const std::string& log)
{
	if (m_bInit)
	m_fileStream << log << "\n";
}


//------------------------------------------------------------------
//
//	WriteTimeStampEntry(..)
//
//	Params:
//	log			-	Text to log
//
//	Writes entry to text file include the time stamp
//
//------------------------------------------------------------------
void CDebugLog::WriteTimeStampEntry(const std::string& log)
{
	if (m_bInit) {
		time_t rawTime;
		struct tm timeinfo;
		char buffer[32];

		time(&rawTime);
		localtime_s(&timeinfo, &rawTime);
		strftime(buffer, 32, "%H:%M:%S", &timeinfo);

		// Replace the new line tag
		std::string textLog(buffer);
		textLog[textLog.length() - 1] = ' ';
		textLog += "- ";

		m_fileStream << textLog << log << "\n";
	}
}