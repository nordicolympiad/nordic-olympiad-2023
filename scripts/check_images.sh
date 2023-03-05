#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 problem_directory"; exit 1; }
CURDIR=$1
declare -a IMAGE_TYPES=( "tif" "tiff" "jpg" "jpeg" "png" "gif" )
pushd $CURDIR
result=0
echo "Checking images"
for tp in ${IMAGE_TYPES[@]}; do
    lookup="*.$tp"
    for file in $(find . -iname $lookup -type f -size +250k); do
        echo "::error title=Image file exceeds 250KB::$file in problem $CURDIR is too large"
        result=1
    done
done
popd
exit $result
