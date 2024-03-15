#!/bin/bash

: '
Get all files starting with 'float'
for oldfile in float*; do
    # Replace 'float' with 'double' for the new file name
    newfile="${oldfile/float/double}"
    # Copy the old file to the new file
    cp "$oldfile" "$newfile"
done
Find all files with prefix "double"
for file in double*; do
    # Check if file is a regular file
    if [ -f "$file" ]; then
        # Apply the sed commands and write the output to a temporary file
        sed 's/float/double/g' "$file" | sed 's/\%f/\%lf/g' > temp.txt
        # Move the temporary file to the original file
        mv temp.txt "$file"
    fi
done
'
