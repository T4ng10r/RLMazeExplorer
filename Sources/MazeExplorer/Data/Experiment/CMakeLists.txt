  include_directories (${RL_MazeExplorer_SOURCE_DIR}/Data)
  include_directories (${RL_MazeExplorer_SOURCE_DIR}/Data/KnowledgeBase)
  include_directories (${RL_MazeExplorer_SOURCE_DIR}/Experiment)
  include_directories (${RL_MazeExplorer_SOURCE_DIR}/GUI)
  include_directories (${RL_MazeExplorer_SOURCE_DIR}/GUI/Drawers)

SET ( SOURCES_EXPERIMENT
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CEnviroment.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CEnviroment.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CExperiment.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CExperiment.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CExperimentSettings.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CExperimentSettings.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CExplorationResult.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CExplorationResult.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CMazeSettings.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CMazeSettings.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/COneExplorationResultDlg.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/COneExplorationResultDlg.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CRobot.cpp
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/CRobot.h
      ${RL_MazeExplorer_SOURCE_DIR}/Experiment/EnviromentVariables.h
      PARENT_SCOPE )
