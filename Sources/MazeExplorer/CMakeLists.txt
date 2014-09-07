cmake_minimum_required(VERSION 2.6)

project(MazeExplorer)

enable_testing()

  #to get log4qt folder
  include_directories (${RL_MazeExplorer_Libs_SOURCE_DIR})

  #to get Maze
  include_directories (${RL_MazeExplorer_SOURCE_DIR}/include/)

  #to get Maze
  include_directories (${MazeExplorer_SOURCE_DIR})

#dodajemy dane dotyczace QT - sciezki, biblioteki
find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED )
include(${QT_USE_FILE})

####################
SET ( SOURCES_DATA
		${MazeExplorer_SOURCE_DIR}/Data/CRobotPostion.h
		${MazeExplorer_SOURCE_DIR}/Data/CScanResults.cpp
		${MazeExplorer_SOURCE_DIR}/Data/CScanResults.h
		${MazeExplorer_SOURCE_DIR}/Data/CMazeKnowlegdeBase.cpp 
		${MazeExplorer_SOURCE_DIR}/Data/CMazeKnowlegdeBase.h
		${MazeExplorer_SOURCE_DIR}/Data/CDataThread.cpp
		${MazeExplorer_SOURCE_DIR}/Data/CDataThread.h  
		${MazeExplorer_SOURCE_DIR}/Data/CAppSettings.cpp 
		${MazeExplorer_SOURCE_DIR}/Data/CAppSettings.h 
		)

####################
SET ( SOURCES_EXPERIMENT
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CEnviroment.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CEnviroment.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperiment.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperiment.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperimentManager.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperimentManager.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperimentSettings.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperimentSettings.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CMazeExplorationResult.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CMazeExplorationResult.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/COneExplorationResultDlg.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/COneExplorationResultDlg.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CRobot.cpp
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CRobot.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/EnviromentVariables.h
		)

SET ( SOURCES_DATA_MOC
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CEnviroment.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CRobot.h
		${MazeExplorer_SOURCE_DIR}/Data/Experiment/CExperiment.h
		${MazeExplorer_SOURCE_DIR}/Data/CDataThread.h  
  )


####################

SET ( SOURCES_GUI
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentResultDraft.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentResultDraft.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentsDraftsDlg.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentsDraftsDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentsKBGraph.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentsKBGraph.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CKBTreeDraw.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/CKBTreeDraw.h
      ${MazeExplorer_SOURCE_DIR}/GUI/MainWindow.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/MainWindow.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CSingleRobotMoveDlg.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/CSingleRobotMoveDlg.h 
      )

SET ( SOURCES_GUI_EXPERIMENT_SRC
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentParamsDlg.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentParamsDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentParamsExperimentDlg.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentParamsExperimentDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentMazeParamsDlg.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentMazeParamsDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentPositionsParamsDlg.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentPositionsParamsDlg.h 
	)

    SET ( SOURCES_GUI_MOC
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CGraphicsMazeScene.h
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CMazeDraw.h
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentParamsDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentPositionsParamsDlg.h 
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentMazeParamsDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/ExperimentParams/CExperimentParamsExperimentDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentResultDraft.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CExperimentsDraftsDlg.h
      ${MazeExplorer_SOURCE_DIR}/GUI/MainWindow.h
      ${MazeExplorer_SOURCE_DIR}/GUI/CSingleRobotMoveDlg.h 
	)

####################

SET ( SOURCES_GUI_DRAWERS
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CMazeDraw.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CMazeDraw.h
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CGraphicsMazeLocation.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CGraphicsMazeLocation.h
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CGraphicsMazeScene.cpp
      ${MazeExplorer_SOURCE_DIR}/GUI/Drawers/CGraphicsMazeScene.h
		)

####################

SET ( SOURCES_MAIN
	main.cpp
	resources.cpp
	)

    SOURCE_GROUP(Data FILES ${SOURCES_DATA})
    SOURCE_GROUP("Data\\KnowledgeBase" FILES ${SOURCES_DATA_KB})
    SOURCE_GROUP("Data\\MazeStuff" FILES ${SOURCES_MAZE_DATA})
    SOURCE_GROUP("Data\\Experiment" FILES ${SOURCES_EXPERIMENT})
    SOURCE_GROUP(Gui FILES ${SOURCES_GUI})
    SOURCE_GROUP("Gui\\Drawers" FILES ${SOURCES_GUI_DRAWERS})

    SOURCE_GROUP(Gui\\ExperimentParams FILES ${SOURCES_GUI_EXPERIMENT_SRC})


    SET ( SOURCES_GUI_MOC ${SOURCES_GUI_MOC} ${SOURCES_DATA_MOC} )
    qt_wrap_cpp(RL_MazeExplorer SOURCES_MOC ${SOURCES_GUI_MOC})
    SOURCE_GROUP(moc FILES ${SOURCES_MOC})

    add_executable(RL_MazeExplorer ${SOURCES_MAIN} ${SOURCES_MOC}
					${SOURCES_DATA_KB} ${SOURCES_DATA} ${SOURCES_MAZE_DATA}
					${SOURCES_EXPERIMENT} ${SOURCES_GUI_EXPERIMENT_SRC}
					${SOURCES_GUI_DRAWERS} ${SOURCES_GUI}
      )

    target_link_libraries(RL_MazeExplorer ${QT_LIBRARIES} MazeLib KBLib log4qt_lib)

