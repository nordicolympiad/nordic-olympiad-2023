#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 problem_directory"; exit 1; }
CURDIR=$1
FILENAME="$CURDIR/problem.yaml"
AUTHOR_CHECK="^author:"
SOURCE_CHECK="^source: Nordic Olympiad in Informatics 2023$"
RIGHTS_OWNER_CHECK="^rights_owner: Nordic Olympiad in Informatics 2023$"
LICENSE_CHECK="^license: cc by-sa$"
TEST_DATA_CHECK="show_test_data_groups: true"
result=0
echo "Checking config"
if ! grep -q -E "$AUTHOR_CHECK" "$FILENAME"; then
    echo "::error file=$FILENAME,line=1,title=Missing author in problem configuration::Missing author in problem.yaml"
    result=1
fi
if ! grep -q -E "$SOURCE_CHECK" "$FILENAME"; then
    echo "::error file=$FILENAME,line=2,title=Incorrect source in problem configuration::Incorrect source in problem.yaml"
    result=1
fi
if ! grep -q -E "$RIGHTS_OWNER_CHECK" "$FILENAME"; then
    echo "::error file=$FILENAME,line=3,title=Incorrect rights_owner in problem configuration::Incorrect rights_owner in problem.yaml"
    result=1
fi
if ! grep -q -E "$LICENSE_CHECK" "$FILENAME"; then
    echo "::error file=$FILENAME,line=4,title=Incorrect license in problem configuration::Incorrect license in problem.yaml"
    result=1
fi
if ! grep -q -E "$TEST_DATA_CHECK" "$FILENAME"; then
    echo "::error file=$FILENAME,line=7,title=Incorrect grading.show_test_data_groups in problem configuration::Incorrect grading.show_test_data_groups in problem.yaml"
    result=1
fi
exit $result
