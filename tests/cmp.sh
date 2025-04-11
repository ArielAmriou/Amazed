#!/bin/bash
SUCCESS=0
FAILED=0
TOTAL=0

return_value() {
    TOTAL=$((TOTAL+1))
    if [ ! -f $1 ]
    then
        echo "$1: no such file or directory"
        return
    fi
    IS=$(timeout 1 ./amazed < $1 &> /dev/null; echo $?)
    SHOULD=$(./tests/B-CPE-200_Amazed_binaries/amazed < $1 &> /dev/null; echo $?)
    if [ $IS != 0 ]
    then
        IS=1
    fi
    if [ $IS = $SHOULD ]
    then
        SUCCESS=$((SUCCESS+1))
        echo -ne "\033[32mCorrect return value ($IS).\033[0m\n"
    else
        FAILED=$((FAILED+1))
        echo -ne "\033[31mERROR:\033[0m\n"
        echo "is: $IS but should be $SHOULD"
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

echo "=============================="
if test "$TOTAL" != 0
then
    echo -ne "\033[34mTOTAL : $TOTAL\033[0m\n"
    echo -------------------------------
fi
if test "$SUCCES" != 0
then
    echo -ne "\033[32mSUCCESS : $SUCCESS\033[0m\n"
    echo -------------------------------
fi
if test "$FAILED" != 0
then
    echo -ne "\033[31mFAILED : $FAILED\033[0m\n"
    echo -------------------------------
fi
if test "$FAILED" = 0
then
    echo -ne "\033[32mALL TESTS SUCCEDED\033[0m\n"
    echo ===============================
else
    echo -ne "\033[31mONE OR MORE FAILED\033[0m\n"
    echo ===============================
fi
SUCCESS_POURCENTS=$(($((SUCCESS * 100)) / $((TOTAL * 5)) - 1))
FAILED_POURCENTS=$(($((FAILED * 100)) / $((TOTAL * 5)) - 1))
echo "completion: $(($((SUCCESS * 100)) / TOTAL))%"
echo ===============================
while test $SUCCESS_POURCENTS -ge 0
do
    echo -ne "\033[32m#\033[0m"
    SUCCESS_POURCENTS=$((SUCCESS_POURCENTS - 1))
done
while test $FAILED_POURCENTS -ge 0
do
    echo -ne "\033[31m#\033[0m"
    FAILED_POURCENTS=$((FAILED_POURCENTS - 1))
done
echo
echo ===============================
if [ $(($((SUCCESS * 100)) / TOTAL)) -lt 75 ]
then
    exit 1
fi