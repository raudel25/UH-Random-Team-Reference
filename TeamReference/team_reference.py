import os


def find_files(directory, extension):
    l = []

    for root, _, files in os.walk(directory):
        aux = []
        for file in files:
            if file.endswith(extension):
                aux.append(file)
        if len(aux) != 0:
            l.append((root, aux))

    return l


def extract_code(file):
    f = open(file)
    s = f.read()
    f.close()
    s = s.split('// begin\n')

    if len(s) < 2:
        return ''

    s = s[1].split('// end')

    return s[0]


def build_codes(l):
    codes = []

    for section, files in l:
        aux = []
        for file in files:
            c = extract_code(os.path.join(section, file))
            if c == '':
                continue
            aux.append((file[:-4], c))

        if len(aux) != 0:
            codes.append(('Template' if section ==
                          '.' else os.path.basename(section), aux))

    return codes


def build_tex(name, code):
    new_name = ''

    for i in range(len(name)):
        if i == 0 or name[i-1] == '_':
            new_name += name[i].upper()
            continue
        if name[i] == '_':
            new_name += ' '
            continue

        new_name += name[i]

    s = new_name + '\n'
    s += '\\begin{multicols}{2}\n'
    s += '\\begin{lstlisting}[language=C++]\n'
    s += code+'\n'
    s += '\\end{lstlisting}\n'
    s += '\\end{multicols}\n'

    return s


def build_reference(l):
    f = open('./TeamReference/template.tex')
    template = f.read()
    f.close

    template = template.split('% code hear')

    reference = template[0]

    for section, codes in l:
        reference += ('\\section{'+section+'}\n')

        for name, code in codes:
            reference += build_tex(name, code)

    reference += template[1]

    f = open('./TeamReference/team_reference.tex', 'w')
    f.write(reference)
    f.close()


l = find_files('.', '.cpp')
l = build_codes(l)
build_reference(l)
