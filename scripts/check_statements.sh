#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 problem_directory"; exit 1; }
CURDIR=$1
declare -A REQUIRED_LANGUAGES=( [en]="English" )
declare -A ADDITIONAL_LANGUAGES=( [da]="Danish" [fi]="Finnish" [is]="Icelandic" [no]="Norwegian" [sv]="Swedish" )
declare -a LANGUAGE_LABELS=()
ACCEPTEDDIR="$CURDIR/problem_statement"
result=0
echo "Checking problem statement languages"
for language in ${!REQUIRED_LANGUAGES[@]}; do
    lookup="problem.$language.tex"
    if [[ -z $(find $ACCEPTEDDIR -name $lookup) ]]; then
        echo "::error title=Missing statement in required language::No $lookup file for problem $CURDIR"
        result=1
    else
        LANGUAGE_LABELS+=(${REQUIRED_LANGUAGES[$language]})
    fi
done
for language in ${!ADDITIONAL_LANGUAGES[@]}; do
    lookup="problem.$language.tex"
    if [[ -z $(find $ACCEPTEDDIR -name $lookup) ]]; then
        echo "::warning title=Missing statement in additional language::No $lookup file for problem $CURDIR"
    else
        LANGUAGE_LABELS+=(${ADDITIONAL_LANGUAGES[$language]})
    fi
done
LABEL_OUTPUT=$(printf ", \\\"%s\\\"" ${LANGUAGE_LABELS[@]})
LABEL_OUTPUT=${LABEL_OUTPUT:2}
if [ -z ${PR_NUMBER+x} ]; then
    :
else
    echo "Setting statement language labels"
    curl --location --request POST 'https://api.github.com/repos/'"$ORG_NAME"'/'"$REPOSITORY_NAME"'/issues/'"$PR_NUMBER"'/labels' \
    --header 'Accept: application/vnd.github.v3+json' \
    --header 'Authorization: Bearer '"$USER_TOKEN" \
    --header 'Content-Type: application/json' \
    --data-raw '{
        "labels": ['"$LABEL_OUTPUT"']
    }'
fi
exit $result
