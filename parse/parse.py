import json
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


def build_name(name):
    new_name = ''

    for i in range(len(name)):
        if i == 0 or name[i-1] == '_':
            new_name += name[i].upper()
            continue
        if name[i] == '_':
            new_name += ' '
            continue

        new_name += name[i]

    return new_name


def build_parse(l):
    json_obj = {}
    for _, files in l:
        for name, code in files:
            lines = code.split('\n')
            json_code = {'prefix': name, 'body': lines, 'description': ''}
            json_obj[build_name(name)] = json_code

    return json_obj


l = find_files('.', '.cpp')
l = build_codes(l)
# build_parse(l)
# print(l)


# f = open('parse/in.txt', 'r')
# file = f.read()
# f.close()

# file = file.split('\n')

# name = file[0]
# prefix = name.lower()
# file = file[1:]

json_obj = build_parse(l)
json_obj = json.dumps(json_obj)

f = open('parse/out.json', 'w')
f.write(json_obj)
f.close()
