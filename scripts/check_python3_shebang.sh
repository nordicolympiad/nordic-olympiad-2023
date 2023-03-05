#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 problem_directory"; exit 1; }
CURDIR=$1
result=0
echo "Checking for python3 shebangs"
for pyfile in $(find $CURDIR -name *.py); do
    if ! head -n 1 $pyfile | grep -q -E '#!.*python3'; then
        echo "::error file=$pyfile,line=1,title=Missing python3 shebang::Shebang for python3 is missing in this file, it might be treated as python2"
        result=1
    fi
done
exit $result
