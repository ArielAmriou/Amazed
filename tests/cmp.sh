#!/bin/bash


return_value() {
    if [ ! -f $1 ]
    then
        echo "$1: no such file or directory"
        return
    fi
    IS=$(./amazed < $1 > /dev/null; echo $?)
    SHOULD=$(./tests/B-CPE-200_Amazed_binaries/amazed < $1  > /dev/null; echo $?)
    if [ $SHOULD != 0 ]
    then
        SHOULD=84
    fi
    if [ $IS = $SHOULD ]
    then
        echo Success
    else
        echo Error
        echo "Is: $IS but should be $SHOULD"
    fi
}

FILES="$(ls -1 tests/files/*)"
for X in $FILES
do
    echo ===============================
    echo "$X"
    echo "*******************************"
    return_value "$X"
done