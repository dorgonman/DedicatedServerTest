#!/bin/sh

<<LICENSE
Boost Software License - Version 1.0 - 2016/10/06 

Copyright (c) 2016 dorgon chang
http://dorgon.horizon-studio.net/

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
LICENSE
source ~/.bash_profile
if  [ "${UE4_ENGINE_ROOT}" = "" ]
then
	echo "UE4_ENGINE_ROOT not Exists"
   	#UE4_ENGINE_ROOT=/d/UnrealEngine/UnrealEngineGit/
   	UE4_ENGINE_ROOT=${1}

else
   echo "ENV UE4_ENGINE_ROOT Exists"
fi

echo "Current UE4_ENGINE_ROOT:${UE4_ENGINE_ROOT}"

GIT_BRANCH=$(git symbolic-ref --short HEAD)
GIT_REV_COUNT=$(git rev-list HEAD --count)
BUILD_CONFIG="Development"
BUILD_PLATFORM="Mac"
PROJECT_NAME=DedicatedServerTest
echo "-----------------------------------------------------"
echo "start ${BUILD_PLATFORM} build - branch=${GIT_BRANCH}, revision=${GIT_REV_COUNT}, CONFIG=${BUILD_CONFIG}"
echo "-----------------------------------------------------"



BASE_PATH=$(cd "$(dirname "$0")"; pwd)
PROJECT_ROOT=$(cd "${BASE_PATH}/../../../../"; pwd)
pushd ${PROJECT_ROOT}


PROJECT_FILE="${PROJECT_ROOT}/${PROJECT_NAME}.uproject"
ARCHIVE_DIR="${PROJECT_ROOT}/../${PROJECT_NAME}_ci_build/${BUILD_PLATFORM}/${GIT_BRANCH}/${GIT_REV_COUNT}/${BUILD_CONFIG}/"
mkdir -p ${ARCHIVE_DIR}
ARCHIVE_DIR=$(cd "${ARCHIVE_DIR}"; pwd)

EXT=$(python ./ci_scripts/function/python/get_shell_ext.py)




"${UE4_ENGINE_ROOT}/Engine/Binaries/DotNET/UnrealBuildTool.exe"  \
 ${PROJECT_NAME} Mac Development \
 -project="${PROJECT_FILE}"      \
 -editorrecompile -progress -noubtmakefiles -NoHotReloadFromIDE -2015


CMD=" \
 '${UE4_ENGINE_ROOT}/Engine/Build/BatchFiles/RunUAT.${EXT}' -ScriptsForProject='${PROJECT_FILE}' BuildCookRun \
 -NoCompileEditor -NoP4  -Verbose -UTF8Output -NoCompile -CrashReporter\
 -project='${PROJECT_FILE}' \
 -cook -allmaps -unversionedcookedcontent -pak -compressed -stage -archive -archivedirectory='${ARCHIVE_DIR}'     \
 -package  -clientconfig=${BUILD_CONFIG} \
 -SKIPEDITORCONTENT -pak -prereqs -nodebuginfo -targetplatform=${BUILD_PLATFORM}        \
 -build  -createreleaseversion=${BUILD_PLATFORM} \
 "
# -nocompile 
 #UAT flag, if we want to compile Source\Programs\AutomationTool

eval ${CMD}

#REMOTE_ARCHIVE_PATH=//xxx/Packaged-Build/${PROJECT_NAME}/${BUILD_PLATFORM}/${GIT_BRANCH}/${GIT_REV_COUNT}/${BUILD_CONFIG}/
#mkdir -p ${REMOTE_ARCHIVE_PATH}

#pushd ${ARCHIVE_DIR}
#tar cvf ${REMOTE_ARCHIVE_PATH}/${GIT_REV_COUNT}_${BUILD_PLATFORM}_${BUILD_CONFIG}.tar .
#popd #pushd ${ARCHIVE_DIR}

popd #pushd ${PROJECT_ROOT}