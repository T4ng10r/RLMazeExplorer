#include "maze_saver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include <Tools/loggers.h>

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

struct maze_saver_private
{
public:
	maze_saver_private(const maze * const maze_);
	void save(QJsonObject& object);
	void ssve_locations(const QJsonObject & object);
	const maze * const maze_data;
};

maze_saver_private::maze_saver_private(const maze * const maze_) : maze_data(maze_)
{}

void maze_saver_private::save(QJsonObject& object)
{
	object[constants::size_x] = maze_data->get_size_x();
	object[constants::size_y] = maze_data->get_size_y();
	QJsonValue maze_type_val;
	switch(maze_data->type)
	{
		case E_MT_PRIM:
			maze_type_val = QJsonValue(constants::type_prim); break;
		case E_MT_KRUSKAL:
			maze_type_val = QJsonValue(constants::type_kruskal); break;
		case E_MT_RECURSIVE:
			maze_type_val = QJsonValue(constants::type_recursive); break;
		default: break;
	};
	object[constants::type] = maze_type_val;
}

////////////////////////////////////////////////////////////////////////////////
maze_saver::maze_saver(const maze * const maze_) : pimpl(new maze_saver_private(maze_))
{
}

maze_saver::~maze_saver(){}

void maze_saver::save(const std::string& file_path)
{
	QFile file(file_path.c_str());
	if (!file.open(QIODevice::WriteOnly))
	{
		printLog(eDebug, eErrorLogLevel,
				QString("Saving maze - can't open given file \"%1\" due to \"%2\"").arg(file_path.c_str()).
				arg(file.errorString()).toStdString());
		return;
	}

	QJsonObject maze_object;
	pimpl->save(maze_object);
	QJsonDocument document(maze_object);
	file.write(document.toJson());
	file.close();
}
