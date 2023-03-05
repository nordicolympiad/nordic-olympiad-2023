#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 problem_directory [should_generate_data]"; exit 1; }
SCRIPTDIR=$(dirname -- "$0")
CURDIR=$1
GENDATA=$2
GENDATA=${GENDATA:="YES"}
result=0
echo "Checking problem $CURDIR"
if [ -d $CURDIR ]; then
    if ! $SCRIPTDIR/check_config.sh $CURDIR; then
        result=1
    fi
    if ! $SCRIPTDIR/check_accepted.sh $CURDIR; then
        result=1
    fi
    if ! $SCRIPTDIR/check_statements.sh $CURDIR; then
        result=1
    fi
    if ! $SCRIPTDIR/check_images.sh $CURDIR; then
        result=1
    fi
    if ! $SCRIPTDIR/check_python3_shebang.sh $CURDIR; then
        result=1
    fi
    pushd "$CURDIR/data"
    if [ "$GENDATA" = "YES" ] && ! ./generator; then
        result=1
    fi
    popd
    pushd "$CURDIR"
    if [[ $(du -sm | cut -f1) -ge 10 ]]; then
        echo "::warning title=Problem directory is too large::Directory for problem $CURDIR exceeds 10MB soft limit"
    fi
    popd
else
    echo "Directory for problem $CURDIR not found, assuming removed"
fi

exit $result
