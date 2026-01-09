#!/bin/bash

echo Event Processing Utility

while IFS= read -r line; do
  ./seascaAP "$line"
done < staging/events.txt

