#!/bin/bash

read -p "Please enter the name of the class: " class_name

mkdir -p Classes

header_file="Classes/$class_name.h"
cpp_file="Classes/$class_name.cpp"

cat > "$header_file" <<EOF
#ifndef ${class_name^^}_H
#define ${class_name^^}_H

class $class_name
{
public:
};

#endif // ${class_name^^}_H
EOF

cat > "$cpp_file" <<EOF
#include "$class_name.h"
EOF

echo "$class_name class files have been created."