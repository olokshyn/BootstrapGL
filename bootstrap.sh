#!/bin/bash

set -e

project_name=$1
project_path=$2
gl_api=$3

if [ -z "$project_name" -o -z "$project_path" ]; then
	echo "Usage: ./bootstrap.sh [project name] [project path] [gl api]"
	exit 1
fi

if [ -z "$gl_api" ]; then
	gl_api="gl=3.3"
fi

git submodule update --init

if [ ! -d env ]; then
	virtualenv --python=$(which python2) env
fi

source env/bin/activate

if ! python -c "import glad"; then
	cd Src/3rdParty/GLAD
	python setup.py install
	cd -
fi

glad \
	--profile core \
	--out-path Src/3rdParty/glad \
	--api $gl_api \
	--generator c \
	--spec gl \
	--local-files

if [ ! -d "$project_path" ]; then
	mkdir -p "$project_path"
fi

cp -r Src "$project_path"/BootstrapGL
sed "s/%PROJECT_NAME%/$project_name/g" templates/CMakeLists.txt > "$project_path"/CMakeLists.txt
sed "s/%PROJECT_NAME%/$project_name/g" templates/main.cpp > "$project_path"/main.cpp
mkdir "$project_path"/shaders
mkdir "$project_path"/textures

echo "Your project $project_name is completely setup in $project_path."
echo "Enjoy OpenGL!"
