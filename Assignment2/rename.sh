#!/bin/bash

for file in *.jpg
do 
  mv "$file" "$(date +%F)-$file"
done

echo "Files renamed"
