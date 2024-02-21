#!/bin/bash

read -p "Please enter the name of the algorithm: " algorithm_name

mkdir -p Algorithms

header_file="Algorithms/$algorithm_name.h"
cpp_file="Algorithms/$algorithm_name.cpp"

cat > "$header_file" <<EOF
#ifndef ${algorithm_name^^}_H
#define ${algorithm_name^^}_H

class $algorithm_name
{
public:
};

#endif // ${algorithm_name^^}_H
EOF

cat > "$cpp_file" <<EOF
#include "$algorithm_name.h"
EOF

echo "$algorithm_name algorithm files have been created."