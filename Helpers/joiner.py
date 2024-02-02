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


def replace_in_main(main_file, directory, class_contents):
    with open(main_file, "r") as file:
        main_content = file.read()

    for include_statement, class_content in class_contents:
        main_content = main_content.replace(include_statement, class_content)

    with open("Joined.cpp", "w") as file:
        file.write(main_content)


def main():
    directory = "Classes/"
    main_file = "Main.cpp"
    class_files = get_class_files(directory)

    print(class_files)

    class_contents = []
    for header_file, cpp_file in class_files:
        header_content = extract_file_content(os.path.join(directory, header_file))
        cpp_content = extract_file_content(os.path.join(directory, cpp_file))

        cpp_content = remove_include_statements(
            cpp_content, [f'#include "{header_file}"']
        )

        include_statement = f'#include "{directory}{header_file}"'

        combined_content = header_content + "\n" + cpp_content
        class_contents.append((include_statement, combined_content))

        print(combined_content)

    replace_in_main(main_file, directory, class_contents)


if __name__ == "__main__":
    main()
