#!/bin/bash

set -ex

gl_api=$1

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
