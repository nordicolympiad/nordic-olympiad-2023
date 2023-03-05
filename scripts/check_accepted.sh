#!/bin/bash
set -e
[ $# -eq 0 ] && { echo "Usage: $0 problem_directory"; exit 1; }
CURDIR=$1
declare -A REQUIRED_LANGUAGES=( [java]="Java" [py]="Python" [cpp]="C++" )
declare -A ADDITIONAL_LANGUAGES=( [c]="C" [cs]="C#" [js]="JavaScript" )
declare -a LANGUAGE_LABELS=()
ACCEPTEDDIR="$CURDIR/submissions/accepted"
result=0
echo "Checking accepted solution languages"
for language in ${!REQUIRED_LANGUAGES[@]}; do
    lookup="*.$language"
    if [[ -z $(find $ACCEPTEDDIR -name $lookup) ]]; then
        echo "::error title=Missing solution in required language::No .$language solution for problem $CURDIR"
        result=1
    else
        LANGUAGE_LABELS+=(${REQUIRED_LANGUAGES[$language]})
    fi
done
for language in ${!ADDITIONAL_LANGUAGES[@]}; do
    lookup="*.$language"
    echo $language
    if [[ -z $(find $ACCEPTEDDIR -name $lookup) ]]; then
        echo "::warning title=Missing solution in additional language::No .$language solution for problem $CURDIR"
    else
        LANGUAGE_LABELS+=(${ADDITIONAL_LANGUAGES[$language]})
    fi
done
LABEL_OUTPUT=$(printf ", \\\"%s\\\"" ${LANGUAGE_LABELS[@]})
LABEL_OUTPUT=${LABEL_OUTPUT:2}
if [ -z ${PR_NUMBER+x} ]; then
    :
else
    echo "Setting accepted solution labels"
    curl --location --request POST 'https://api.github.com/repos/'"$ORG_NAME"'/'"$REPOSITORY_NAME"'/issues/'"$PR_NUMBER"'/labels' \
    --header 'Accept: application/vnd.github.v3+json' \
    --header 'Authorization: Bearer '"$USER_TOKEN" \
    --header 'Content-Type: application/json' \
    --data-raw '{
        "labels": ['"$LABEL_OUTPUT"']
    }'
fi
exit $result
