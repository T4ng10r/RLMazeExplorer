#include "maze_saver.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
#include <Tools/loggers.h>

maze_saver::maze_saver(const maze * const maze_) : maze_data(maze_)
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
	QXmlStreamWriter writer;
	writer.setDevice(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	writer.writeStartElement("maze");
	writer.writeAttribute("size_x", QString::number(maze_data->size_x));
	writer.writeAttribute("size_y", QString::number(maze_data->size_y));
	writer.writeEndElement();

	writer.writeStartElement("content");
	for(int i=0;i<maze_data->size_y;i++)
	{
		writer.writeStartElement("row");
		for(int j=0;j<maze_data->size_x;j++)
		{
			writer.writeStartElement("cell");
			int dir=0;
			boost::optional<location> location_ = maze_data->get_location(j+1, i+1);
			if (location_)
			{
				for (int k = NORTH_DIR; k != COUNT_DIR; k++)
					dir |= 1<<k;
				writer.writeCharacters(QString::number(dir));
			}
			writer.writeEndElement();
		}
		writer.writeEndElement();
	}
	writer.writeEndElement();

	writer.writeEndDocument();
	file.close();
}
