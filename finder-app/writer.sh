#!/bin/bash
set -e

writefile=$1
writestr=$2

if [ $# -ne 2 ]
then
  echo "Incorrect number of arguments"
  echo "Usage: $0 <filename> <contents>"
  exit 1
fi

if [ ! -f "$writefile" ]
then
  dirname=$(dirname "$writefile")
  if [ ! -e "$dirname" ]
  then
    mkdir -p "$dirname"
  fi
fi

echo "$writestr" > "$writefile"

exit 0