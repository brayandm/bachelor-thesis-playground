#!/bin/bash

bash build.sh

test_dir="Tests/"
output_dir="Tests/Output/"

mkdir -p "$test_dir"
mkdir -p "$output_dir"

for input_file in "$test_dir"*; do
    if [ ! -f "$input_file" ]; then
        continue
    fi

    filename=$(basename -- "$input_file")

    output_file="${output_dir}${filename%.*}.out"

    bash run.sh "$input_file" "$output_file"
done
