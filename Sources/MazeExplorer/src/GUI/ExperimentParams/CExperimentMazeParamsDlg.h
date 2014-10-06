#ifndef _EXPERIMENT_GENERATION_PARAMS_DLG_H
#define _EXPERIMENT_GENERATION_PARAMS_DLG_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QVBoxLayout>

#include <Maze/maze_settings.h>

class CExperimentMazeParamsDlg : public QWidget
{
    Q_OBJECT
public:
    CExperimentMazeParamsDlg(QWidget *parent = 0);
	void set_maze_settings(maze_settings & stMazeSettings);
	void get_maze_settings(maze_settings & stMazeSettings);

Q_SIGNALS:
	void generate_maze(maze_settings);
protected Q_SLOTS:
	//reaction on Generate Maze button click
	void on_generate_maze(bool);
private:
    void setup_ui();
    void setupStochasticMazeChanges();
    void retranslate_ui();
    void setConnections();
	EMazeTypes getMazeGenerationMethod();
	void setMazeGenerationMethod(EMazeTypes eType);

private:
    QGridLayout *		mainLayout;

//	QGridLayout *		gboxMazeGenerationLayout;

    QLabel		*	labelSizeX;
    QSpinBox	*	spinSizeX;
    QLabel		*	labelSizeY;
    QSpinBox	*	spinSizeY;
    QLabel		*	labelMazeGenMethod;
    QComboBox	*	comboGenerationMethod;
    QPushButton *		button_generate_maze;
    QCheckBox	*	checkBoxMazeIsPerfect;

    QGroupBox *		groupStochasticMazeChanges;
    QGridLayout *		gboxMazeStochasticLayout;
    QLabel		*	labelRandomnessValue;
    QSpinBox	*	spinRandomnessValue;
    QCheckBox *		checkBoxCumulativeRandomness;

};
#endif	/* _EXPERIMENT_GENERATION_PARAMS_DLG_H */
