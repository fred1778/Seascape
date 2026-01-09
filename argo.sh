#!/bin/bash

echo SEASCAPE Artefact Processing Utility
g++ seasca_main.cpp -o seasc -l sqlite3

while IFS= read -r line; do
  scode=$(./seasc "$line")
  echo "$scode"
  cd staging
  pdf_file=$(ls *.pdf 2>/dev/null | head -1)
  if [ -n "$pdf_file" ]; then
    mv "$pdf_file" "../archive/${scode}.pdf"
  fi
  cd ..
done < staging/manifest.txt


