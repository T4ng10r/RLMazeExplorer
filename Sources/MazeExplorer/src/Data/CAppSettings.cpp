#include <Data/CAppSettings.h>
#include <QtCore/QSettings>

bool	bDefaultPrintMazePDF = false;
QString	strDefaultMazePdfPath = "maze.pdf";

CAppSettings& CAppSettings::getAppSettings()
{
	static CAppSettings s_AppSettings;
	return s_AppSettings;
}
CAppSettings::CAppSettings(void){}
void CAppSettings::saveSettings()
{
	QSettings settings("RL", "RL MazeExplorer");
	settings.setValue("bPrintMazePDF",bPrintMazePDF);
	settings.setValue("strMazePdfPath",strMazePdfPath);
}
void CAppSettings::loadSettings()
{
	QSettings settings("RL", "RL MazeExplorer");
	bPrintMazePDF=settings.value("bPrintMazePDF").toString()=="false"?0:1;
	strMazePdfPath=settings.value("strMazePdfPath").toString();

	if (strMazePdfPath.isEmpty())
		strMazePdfPath=strDefaultMazePdfPath;
}
