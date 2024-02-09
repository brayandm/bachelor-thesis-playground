#!/bin/bash

echo "Building..."

if ! bash build.sh > /dev/null 2>&1; then
    echo -e "\033[31mError during build process.\033[0m"
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

     if ! bash validate.sh "$input_file" "$output_file" > /dev/null 2>&1; then
        echo -e "\033[31mError during validation for $input_file.\033[0m"
        continue 
    fi

    bash summary.sh "$input_file" "$output_file"
done
