#!/bin/bash

read -p "Please enter the name of this experiment: " experiment_name

read -p "Please enter the description of this experiment: " experiment_description

echo "Please paste the Codeforces test logs (50 test cases expected):"
readarray -t test_logs

if [ "${#test_logs[@]}" -ne 50 ]; then
    echo "Error: There are not exactly 50 test cases. Received ${#test_logs[@]} cases." >&2
    exit 1
fi

experiment_name_snake_cased=$(echo $experiment_name | tr '[:upper:]' '[:lower:]' | tr ' ' '_')

experiment_number=$(find Experiments -maxdepth 1 -type d | wc -l)

formatted_experiment_name="exp${experiment_number}_${experiment_name_snake_cased}"

mkdir -p "Experiments/$formatted_experiment_name/Classes"

cp Main.cpp "Experiments/$formatted_experiment_name/Main.cpp"

cp -r Classes/* "Experiments/$formatted_experiment_name/Classes/"

echo "{
  \"name\": \"$experiment_name\",
  \"description\": \"$experiment_description\"
}" > "Experiments/${formatted_experiment_name}/Description.json"

csv_file="Experiments/${formatted_experiment_name}/codeforcesResult.csv"

temp_file="$(mktemp)"

echo "Case,Status,Time (ms),Memory (MB),Points" > "$temp_file"

total_points=0

for log in "${test_logs[@]}"; do
    if [[ $log =~ ^#([0-9]+):[[:space:]]+([a-zA-Z ]+)[[:space:]]+\[([0-9]+)[[:space:]]ms,[[:space:]]([0-9]+)[[:space:]]MB,[[:space:]]([0-9]+\.[0-9]+)[[:space:]]points\] ]]; then
        case_number=${BASH_REMATCH[1]}
        status=${BASH_REMATCH[2]}
        time=${BASH_REMATCH[3]}
        memory=${BASH_REMATCH[4]}
        points=${BASH_REMATCH[5]}

        if [[ "$status" == "Accepted" ]]; then
            total_points=$(echo "$total_points + $points" | bc -l)
        fi
        
        echo "$case_number,$status,$time,$memory,$points" >> "$temp_file"
    fi
done
echo "Total Score: $total_points" > "$csv_file"
echo "" >> "$csv_file"
cat "$temp_file" >> "$csv_file"
rm "$temp_file"
