#!/bin/sh



# Usage:
# $ ./UEBuild.sh {PROJECT_FULL_PATH} {PLATFORM} {CONFIG} {ARCHIVE_FULL_PATH}
# * {1}: {PROJECT_FULL_PATH}: full_project_path_and_project_name.uproject
# * {2}: {PLATFORM}: ex: Win64, Win32, Android...
# * {3}: {CONFIG}: ex: Development
# * {4}: {ARCHIVE_FULL_PATH}: full_archive_dir



UERunUAT(){
   ext=bat
   return ${UE4_ENGINE_PATH}/Engine/Build/BatchFiles/RunUAT.${ext}
}


UEBuildClient () {
   ext=bat
   ${UE4_ENGINE_PATH}/Engine/Build/BatchFiles/RunUAT.${ext} BuildCookRun \
   -project=${1} \
   -noP4 -platform=${2} \
   -clientconfig=${3} -serverconfig=${3} \
   -cook -allmaps -build -stage \
   -pak -archive -archivedirectory=${4} 
}



UEBuildClientOnlyCook(){
   RunUAT BuildCookRun \
   -project=${PROJECT_FULL_PATH} \
   -noP4 -platform=${PLATFORM} -clientconfig=${CONFIG} -serverconfig=${CONFIG} \ 
   -cook -allmaps -NoCompile -stage \
   -pak -archive -archivedirectory=${ARCHIVE_FULL_PATH}
}



UEBuildServer () {
   ${UE4_ENGINE_PATH}/Engine/Build/BatchFiles/RunUAT BuildCookRun \
   -project=${PROJECT_FULL_PATH} \
   -noP4 -platform=${PLATFORM} -clientconfig=${CONFIG} -serverconfig=${CONFIG} \
   -cook -server -serverplatform=${PLATFORM} -noclient -build -stage \
   -pak -archive -archivedirectory=${ARCHIVE_FULL_PATH}
}


UEBuildServerOnlyCook(){
   ${UE4_ENGINE_PATH}/Engine/Build/BatchFiles/RunUAT BuildCookRun \
   -project=${PROJECT_FULL_PATH} \
   -noP4 -platform=${PLATFORM} -clientconfig=${CONFIG} -serverconfig=${CONFIG} \
   -cook -server -serverplatform=${PLATFORM} -noclient -NoCompile -stage \
   -pak -archive -archivedirectory=${ARCHIVE_FULL_PATH} 
}

