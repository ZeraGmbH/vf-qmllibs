#!/usr/bin/env python

import glob, os
import polib

def main():
    po_files = find_po_files()
    for po_file in po_files:
        po_dict = parse_po_to_dict(po_file)
        lang = language(po_file)
        ts_file = po_name_to_ts(po_file)
        create_ts_file(lang, ts_file, po_dict)

def find_po_files():
    po_files = []
    script_dir = os.path.dirname(os.path.realpath(__file__))
    for file in glob.glob(script_dir + "/*.po"):
        po_files.append(file)
    return po_files

def parse_po_to_dict(po_file):
    print("Collect data for %s..." % basename(po_file))
    po_dict = {}
    po_parsed = polib.pofile(po_file)
    for entry in po_parsed:
        text = entry.msgid
        textTr = entry.msgstr
        texts = text.split("/", 1)
        textsTr = textTr.split("/", 1)
        if len(texts) == 2 and len(texts) == len(textsTr) and \
           not (texts[0].endswith(" ") or texts[1].startswith(" ")):
            for i in range(len(texts)):
                try_add_translation(texts[i], textsTr[i], po_dict, po_file)
        else:
            try_add_translation(text, textTr, po_dict, po_file)
    return po_dict

def try_add_translation(text: str, textTr: str, po_dict: dict[str, str], po_file: str):
    if text == textTr: # do not add not translated
        return
    if text.startswith(" ") or textTr.endswith(" "):
        print("Warning: '%s' contains leading / trailing space(s). Region/city split correct?" % text)
    if not text in po_dict: # add new
        po_dict[text] = textTr
        return
    if po_dict[text] != textTr: # a different than already stored
        try_change_to_preferred_translation(text, textTr, po_dict, po_file)

def try_change_to_preferred_translation(text: str, textTr: str, po_dict: dict[str, str], po_file: str):
        preferred_tr = {
            "es_ES": ["Antártida", "Hawaii", "Indico"],
            "fr_FR": ["Amérique"]
        }
        lang = language(po_file)
        if lang in preferred_tr:
            if po_dict[text] in preferred_tr[lang]:
                return
            elif textTr in preferred_tr[lang]:
                po_dict[text] = textTr
                return
        print("Warning: Different translation for '%s': Avail: '%s' / New: '%s'" % (text, po_dict[text], textTr))

def create_ts_file(lang: str, ts_file: str, po_dict: dict[str, str]):
    print("Create %s..." % basename(ts_file))

    ts_xml_list = []
    create_ts_header(ts_xml_list, lang)
    add_translations(ts_xml_list, po_dict)
    create_ts_footer(ts_xml_list)

    with open(ts_file, 'w', encoding='utf-8') as file:
        for line in ts_xml_list:
            file.write(line + '\n')

def create_ts_header(ts_xml_list: list[str], lang: str):
    ts_xml_list.append('<?xml version="1.0" encoding="utf-8"?>')
    ts_xml_list.append("<!DOCTYPE TS>")
    version_line = '<TS version="2.1" language="' + lang + '">'
    ts_xml_list.append(version_line)
    ts_xml_list.append("<context>")
    ts_xml_list.append("    <name></name>")

def add_translations(ts_xml_list: list[str], po_dict: dict[str, str]):
    for source, translated in po_dict.items():
        ts_xml_list.append("    <message>")
        line = "        <source>" + escapeXml(source) + "</source>"
        ts_xml_list.append(line)
        line = "        <translation>" + escapeXml(translated) + "</translation>"
        ts_xml_list.append(line)
        ts_xml_list.append("    </message>")

def create_ts_footer(ts_xml_list: list[str]):
    ts_xml_list.append("</context>")
    ts_xml_list.append("</TS>")

def escapeXml( str_xml: str ):
    return str_xml \
        .replace("&", "&amp;") \
        .replace("<", "&lt;") \
        .replace(">", "&gt;") \
        .replace("\"", "&quot;") \
        .replace("'", "&apos;") \

def po_name_to_ts(po_file: str):
    base = basename(po_file)
    ts = "timezones_" + base.replace(".po", ".ts")
    return po_file.replace(base, ts)

def basename(filename: str):
    return os.path.basename(filename)

def language(filename: str):
    return basename(filename).replace(".po", "").replace(".ts", "")


if __name__ == "__main__":
    main()

