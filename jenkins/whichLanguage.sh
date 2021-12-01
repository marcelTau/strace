#!/bin/bash

language=""

if [ -f ./Makefile ]; then
    language+="C"
fi

if [ -f ./app/pom.xml ]; then
    language+="Java"
fi

if [ -f ./package.json ]; then
    language+="JavaScript"
fi

if [ -f ./requirements.txt ]; then
    language+="Python"
fi

if [ -f ./app/main.bf ]; then
    language+="Befunge"
fi

echo $language
