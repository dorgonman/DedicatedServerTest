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
UE4_ENGINE_ROOT=${1}

if  [ "${UE4_ENGINE_ROOT}" = "" ]
then
	echo "UE4_ENGINE_ROOT not Exists"
   	UE4_ENGINE_ROOT=/d/UnrealEngine/UnrealEngineGit/
   	#UE4_ENGINE_ROOT="/d/UnrealEngine/Epic Games/4.13/"

else
   echo "ENV UE4_ENGINE_ROOT Exists"
fi

echo "Current UE4_ENGINE_ROOT:${UE4_ENGINE_ROOT}"

GIT_BRANCH=$(git symbolic-ref --short HEAD)
GIT_REV_COUNT=$(git rev-list HEAD --count)
BUILD_CONFIG="Development"
PLATFORM="Win64"

echo "-----------------------------------------------------"
echo "start win64 build - branch=${GIT_BRANCH}, revision=${GIT_REV_COUNT}, CONFIG=${BUILD_CONFIG}"
echo "-----------------------------------------------------"



BASE_PATH=$(cd "$(dirname "$0")"; pwd)
PROJECT_ROOT=$(cd "${BASE_PATH}/../../../../"; pwd)
pushd ${PROJECT_ROOT}


PROJECT_FILE="${PROJECT_ROOT}/DedicatedServerTest.uproject"
ARCHIVE_DIR="${PROJECT_ROOT}/../DedicatedServerTest_ci_build/${PLATFORM}/${GIT_BRANCH}/${GIT_REV_COUNT}/${BUILD_CONFIG}/"
mkdir -p ${ARCHIVE_DIR}
ARCHIVE_DIR=$(cd "${ARCHIVE_DIR}"; pwd)

echo {PROJECT_ROOT}: ${PROJECT_ROOT}
echo {ARCHIVE_DIR}: ${ARCHIVE_DIR}
echo {BUILD_CONFIG}: ${BUILD_CONFIG}
echo {PLATFORM}: 	${PLATFORM}
echo {PROJECT_FILE}: ${PROJECT_FILE}

#./git_clean.sh
python -u ${PROJECT_ROOT}/ci_scripts/function/python/HorizonBuildTool/HorizonBuildTool/Source/HorizonUE4Build/Main.py \
	 --buildserver  \
	 --engine "${UE4_ENGINE_ROOT}" \
	 --project "${PROJECT_FILE}" \
	 --build_platform ${PLATFORM} \
	 --build_config ${BUILD_CONFIG} \
	 --archive "${ARCHIVE_DIR}"


popd #pushd ${PROJECT_ROOT}
