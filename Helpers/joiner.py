import os


def get_class_files(directory):
    files = os.listdir(directory)
    classes = [file.split(".")[0] for file in files if file.endswith(".h")]
    return [(f"{class_name}.h", f"{class_name}.cpp") for class_name in classes]


def extract_file_content(filepath):
    with open(filepath, "r") as file:
        return file.read()


def remove_include_statements(file, include_statements):
    for include_statement in include_statements:
        file = file.replace(include_statement, "")
    return file


def find_header_dependencies(file, include_statement_header):

    dependencies = set()

    for include_statement in include_statement_header:
        if include_statement in file:
            dependencies.add(include_statement_header[include_statement])

    return dependencies


def topological_sort(dependency_dict):
    visited = set()
    topological_order = []

    def dfs(node):
        if node not in visited:
            visited.add(node)
            for neighbor in dependency_dict.get(node, []):
                dfs(neighbor)
            topological_order.insert(0, node)

    for node in dependency_dict.keys():
        if node not in visited:
            dfs(node)

    return topological_order[::-1]


def main():

    directories = ["Classes/", "Algorithms/"]

    main_file = "Main.cpp"

    include_statements = []

    include_statement_header = {}

    dependencies = {}

    for directory in directories:

        class_files = get_class_files(directory)

        for header_file, cpp_file in class_files:
            include_statements.append(f'#include "{header_file}"')
            include_statements.append(f'#include "{directory}{header_file}"')
            include_statements.append(f'#include "../{directory}{header_file}"')

            include_statement_header[f'#include "{header_file}"'] = (
                f"{directory}{header_file}"
            )
            include_statement_header[f'#include "{directory}{header_file}"'] = (
                f"{directory}{header_file}"
            )
            include_statement_header[f'#include "../{directory}{header_file}"'] = (
                f"{directory}{header_file}"
            )

    for directory in directories:

        class_files = get_class_files(directory)

        for header_file, cpp_file in class_files:

            dependencies[f"{directory}{header_file}"] = find_header_dependencies(
                extract_file_content(os.path.join(directory, header_file)),
                include_statement_header,
            )

    topological_order = topological_sort(dependencies)

    combined_header_content = ""
    combined_cpp_content = ""

    for header_file in topological_order:

        cpp_file = header_file.replace(".h", ".cpp")

        header_content = extract_file_content(header_file)

        header_content = remove_include_statements(header_content, include_statements)

        combined_header_content += header_content + "\n"

        cpp_content = extract_file_content(cpp_file)

        cpp_content = remove_include_statements(cpp_content, include_statements)

        combined_cpp_content += cpp_content + "\n"

    main_content = extract_file_content(main_file)

    main_content = remove_include_statements(main_content, include_statements)

    combined_content = (
        combined_header_content + "\n" + combined_cpp_content + "\n" + main_content
    )

    with open("Joined.cpp", "w") as file:
        file.write(combined_content)


if __name__ == "__main__":
    main()
