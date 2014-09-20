#ifndef _APP_SETTINGS_INCLUDE_
#define _APP_SETTINGS_INCLUDE_

#include <vector>
#include <QtCore/QString>

#define g_AppSettings 	CAppSettings::getAppSettings()
class CMaze;

class CAppSettings
{
	CAppSettings(void);
public:
	static CAppSettings& getAppSettings();
	void saveSettings();
	void loadSettings();

public:
	//after each generation create pdf file with generated maze
	bool		bPrintMazePDF;
	//path to file which will store 
	QString		strMazePdfPath;
};
#endif /*_APP_SETTINGS_INCLUDE_*/
