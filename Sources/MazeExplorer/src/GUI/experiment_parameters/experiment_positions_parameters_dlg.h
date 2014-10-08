#ifndef CEXPERIMENTPARAMSMAZEDLG_H
#define CEXPERIMENTPARAMSMAZEDLG_H

#include <memory>
#include <QWidget>
#include <QStandardItem>
#include <Data/experiment/CExperimentSettings.h>

class experiment_positions_parameters_dlg_private;

class experiment_positions_parameters_dlg : public QWidget
{
    Q_OBJECT
public:
	experiment_positions_parameters_dlg(QWidget *parent = 0);
	~experiment_positions_parameters_dlg();

	void setExperimentSettings(experiment_settings & cExperimentSettings);
	void getExperimentSettings(experiment_settings & cExperimentSettings);
Q_SIGNALS:
	//send signal about change in start positions
	void on_set_start_position(int ,int);	//wysyla informacja o ustawieniu nowej pozycji startowej
	void setFinishPosition(int ,int);	//wysyla informacja o ustawieniu nowej pozycji ko�cowej
	//wysyla informacja o ustawieniu nowej pozycji ko�cowej
	void setFinishPositions(std::vector< std::pair<int,int> >);	
	//send info about change of start direction (on argument perform cast into eRobotDir)
	void setStartDirection(int);
public Q_SLOTS:
	//sets maximum limit values to start and finish positions
	void onMazeGeneration(maze_settings);
	//user selected new start position on Maze Draw
	void onNewStartPosition(int ,int);
	//user selected first of finish position on Maze Draw
	void onNewFinishPosition(int ,int);
	//user add new finish position on Maze Draw
	void onAddFinishPosition(int ,int);

	void onButtonAddFinishPos();
	void onButtonRemFinishPos();
protected Q_SLOTS:
	//starting position has been change
	void onInternalStartPosChange();		
	//entry in finish position has been changed - send entire list of positions to update
	void onInternalFinishPostionChanged(QStandardItem *);
	//user changed starting direction of agent by highlighting entry in comboBox
	void onInternalDirectionChanged(int iIndex);
private:
	std::unique_ptr<experiment_positions_parameters_dlg_private> pimpl;
};

#endif
