#include "maze_loader.h"
#include <QIODevice>
#include <QFile>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <Tools/loggers.h>
#include <boost/format.hpp>

namespace constants
{
	const QString size_x("size_x");
	const QString size_y("size_y");
	const QString type("type");
	const QString type_prim("PRIM");
	const QString type_kruskal("KRUSKAL");
	const QString type_recursive("RECURSIVE");
	const QString locations("locations");
};

struct maze_loader_private
{
public:
	void load(const QJsonObject & object);
	void load_locations(const QJsonObject & object);
	maze * maze_data;
};

void maze_loader_private::load(const QJsonObject & object)
{
	maze_data->size_x = object.value(constants::size_x).toString().toLong();
	maze_data->size_y = object.value(constants::size_y).toString().toLong();
	QString type = object.value(constants::type).toString();
	if (type == constants::type_prim)
		maze_data->type = E_MT_PRIM;
	else if (type == constants::type_kruskal)
		maze_data->type = E_MT_KRUSKAL;
	else if (type == constants::type_recursive)
		maze_data->type = E_MT_RECURSIVE;
	maze_data->resize();
	maze_data->reset_locations();
	load_locations(object);
}
void maze_loader_private::load_locations(const QJsonObject & object)
{
	int x(0);
	int y(0);
	QJsonArray locations = object[constants::locations].toArray();
	for (const QJsonValue & single_row : locations)
	{
		QJsonArray rows = single_row.toObject()["row"].toArray();
		for (const QJsonValue & single_cell : rows)
		{
			QJsonObject cell_obj = single_cell.toObject();
			int dir =  cell_obj["cell"].toString().toInt();
			location &location_data = maze_data->get_xlocation(x, y);
			for (int i = NORTH_DIR; i != COUNT_DIR; i++)
			{
				if (dir & (1 << i))
					location_data.set_wall((EDirections)i);
				else
					location_data.set_passage((EDirections)i);
			}
			++x;
		}
		x = 0;
		++y;
	}
}
////////////////////////////////////////////////////////////////////////////////
maze_loader::maze_loader(maze * maze_) : pimpl(new maze_loader_private())
{
	pimpl->maze_data = maze_;
}
maze_loader::~maze_loader(){}
void maze_loader::load(const std::string& file_path)
{
	QFile file(file_path.c_str());
	if (!file.open(QIODevice::ReadOnly))
	{
		printLog(eDebug, eWarningLogLevel, str(boost::format("Can't open file '%1%'") % file_path));
		return;
	}
	QJsonDocument document(QJsonDocument::fromJson(file.readAll()));
	file.close();
	pimpl->load(document.object());
}
