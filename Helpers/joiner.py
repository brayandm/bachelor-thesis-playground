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


def main():
    directory = "Classes/"
    main_file = "Main.cpp"
    class_files = get_class_files(directory)

    include_statements = []

    for header_file, cpp_file in class_files:
        include_statements.append(f'#include "{header_file}"')
        include_statements.append(f'#include "{directory}{header_file}"')

    combined_header_content = ""

    for header_file, cpp_file in class_files:
        header_content = extract_file_content(os.path.join(directory, header_file))

        header_content = remove_include_statements(header_content, include_statements)

        combined_header_content += header_content + "\n"

    combined_cpp_content = ""

    for header_file, cpp_file in class_files:
        cpp_content = extract_file_content(os.path.join(directory, cpp_file))

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
