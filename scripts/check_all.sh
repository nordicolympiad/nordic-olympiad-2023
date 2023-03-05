#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 base_directory [should_generate_data]"; exit 1; }
BASEDIR="$1"
GENDATA=$2
GENDATA=${GENDATA:="YES"}
PROBLEMSFILE="$BASEDIR/CHANGED_PROBLEMS"
PROBLEMSDIR="$BASEDIR/problems"
result=0
SCRIPTSDIR="$BASEDIR/scripts"
if [ -f $PROBLEMSFILE ]; then
    PROBLEMS=$(cat $PROBLEMSFILE);
else
    PROBLEMS="$PROBLEMSDIR/*"
fi
echo $PROBLEMS
for problem in $PROBLEMS; do
    problem=${problem##*/}
    CURDIR="$PROBLEMSDIR/$problem"
    echo "Checking problem $problem"
    if ! $SCRIPTSDIR/check_problem.sh $CURDIR $2; then
        result=1
    fi
done
exit $result
