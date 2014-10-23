#include "maze_saver.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <Tools/loggers.h>

maze_saver::maze_saver(maze * maze_) : maze_data(maze_)
{
}

void maze_saver::save(const std::string& file_path)
{
	QFile file(file_path.c_str());
	if (file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
	{
		printLog(eDebug, eErrorLogLevel, "Can't open given file");
		return;
	}
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();

	writer.writeEndDocument();
	file.close();
}
