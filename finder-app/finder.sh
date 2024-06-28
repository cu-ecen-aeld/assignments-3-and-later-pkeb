#!/bin/bash
set -e

filesdir=$1
searchstr=$2

if [ $# -ne 2 ]
then
  echo "Incorrect number of arguments"
  echo "Usage: $0 <directory> <search string>"
  exit 1
fi

if [ ! -d "$filesdir" ]
then
  echo "'${filesdir}' does not exist or is not a directory"
  exit 1
fi

filecount=$(find "$filesdir" -type f | wc -l)
matchcount=$(find "$filesdir" -type f -print0 | xargs -0 grep "$searchstr" | wc -l)

echo "The number of files are ${filecount} and the number of matching lines are ${matchcount}"

exit 0