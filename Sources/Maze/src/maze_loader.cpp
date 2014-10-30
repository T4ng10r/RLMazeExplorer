#include "maze_loader.h"
#include <QIODevice>
#include <QFile>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonObject>
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
	QJsonObject locations = object.value(constants::locations);
	//petla po obiektach row

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

