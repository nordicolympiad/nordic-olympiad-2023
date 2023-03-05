#!/bin/bash
set -e
if [ -z ${PR_NUMBER+x} ]; then
    : # only for pull requests in workflow
else
    echo "Clearing PR labels"
    curl --location --request DELETE 'https://api.github.com/repos/'"$ORG_NAME"'/'"$REPOSITORY_NAME"'/issues/'"$PR_NUMBER"'/labels' \
    --header 'Accept: application/vnd.github.v3+json' \
    --header 'Authorization: Bearer '"$USER_TOKEN" \
    --header 'Content-Type: application/json'
fi
exit $result
