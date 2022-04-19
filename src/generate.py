from os import getcwd, mkdir, listdir
from os.path import basename, isfile, isdir, join, splitext
from shutil import copy, rmtree

def generate_subsection(out, subsection_file):
    name, ext = splitext(subsection_file)
    if ext == '.cpp' and not name.endswith('.test'):
        subsection = subsection_file.replace(' ', '\\ ')
        print(f"\subsection{{{basename(name)}}}", file=out)
        print(f"\code{{{subsection}}}", file=out)


def generate_section(out, section_dir):
    print(f"\section{{{basename(section_dir)}}}", file=out)
    for subsection in sorted(listdir(section_dir)):
        subsection = join(section_dir, subsection)
        if isfile(subsection):
            generate_subsection(out, subsection)


def generate(out, data_dir):
    for section in sorted(listdir(data_dir)):
        section = join(data_dir, section)
        if isdir(section):
            generate_section(out, section)


if __name__ == '__main__':
    build_dir = join(getcwd(), 'build')
    data_dir = join(getcwd(), 'data')
    src_dir = join(getcwd(), 'src')

    rmtree(build_dir, ignore_errors=True)
    mkdir(build_dir)
    with open(join(build_dir, 'code.tex'), 'w+') as out:
        generate(out, data_dir)
        copy(join(src_dir, 'template.tex'), build_dir)

