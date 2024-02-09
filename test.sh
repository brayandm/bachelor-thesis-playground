#!/bin/bash

echo "Building..."

if ! bash build.sh > /dev/null 2>&1; then
    echo "Error during build process."
    exit 1
fi

echo "Running tests..."

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

    bash summary.sh "$input_file" "$output_file"
done
