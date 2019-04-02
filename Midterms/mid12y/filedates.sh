#!/bin/bash

names=1
if [ "$1" = -n ]; then
  names=0
  shift
fi

for f in "$@"; do
  if [ $names -eq 1 ]; then
    echo $f `date -r $f`
  else
    echo `date -r $f`
  fi
done
