#ifndef _EXPERIMENT_GENERATION_PARAMS_DLG_H
#define _EXPERIMENT_GENERATION_PARAMS_DLG_H

#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>

#include <Maze/CMazeSettings.h>

class CExperimentMazeParamsDlg : public QWidget
{
    Q_OBJECT
public:
    CExperimentMazeParamsDlg(QWidget *parent = 0);
	void setMazeSettings(CMazeSettings & stMazeSettings);
	void getMazeSettings(CMazeSettings & stMazeSettings);

signals:
    void generateMaze(CMazeSettings &);
protected slots:
	//reaction on Generate Maze button click
	void onGenerateMaze(bool);
private:
    void setupUI();
    void setupStochasticMazeChanges();
    void retranslateUI();
    void setConnections();
	eMazeTypes getMazeGenerationMethod();
	void setMazeGenerationMethod(eMazeTypes eType);

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
