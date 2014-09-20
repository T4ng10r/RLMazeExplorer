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
	void setMazeSettings(maze_settings & stMazeSettings);
	void getMazeSettings(maze_settings & stMazeSettings);

Q_SIGNALS:
	void generateMaze(maze_settings &);
protected Q_SLOTS:
	//reaction on Generate Maze button click
	void onGenerateMaze(bool);
private:
    void setupUI();
    void setupStochasticMazeChanges();
    void retranslateUI();
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
    QPushButton *		buttonGenerateMaze;
    QCheckBox	*	checkBoxMazeIsPerfect;

    QGroupBox *		groupStochasticMazeChanges;
    QGridLayout *		gboxMazeStochasticLayout;
    QLabel		*	labelRandomnessValue;
    QSpinBox	*	spinRandomnessValue;
    QCheckBox *		checkBoxCumulativeRandomness;

};
#endif	/* _EXPERIMENT_GENERATION_PARAMS_DLG_H */
