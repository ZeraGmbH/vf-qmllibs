#!/usr/bin/env python

import glob, os
import polib

def basename(filename):
    return os.path.basename(filename)

def language(filename):
    return basename(filename).replace(".po", "").replace(".ts", "")

def find_po_files():
    po_files = []
    script_dir = os.path.dirname(os.path.realpath(__file__))
    for file in glob.glob(script_dir + "/*.po"):
        po_files.append(file)
    return po_files

def po_name_to_ts(po_file):
    return po_file.replace(".po", ".ts")

def tryPreferred(text, textTr, po_dict, po_file):
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
        print("Different translation for '%s': Avail: '%s' / New: '%s'" % (text, po_dict[text], textTr))

def tryAdd(text, textTr, po_dict, po_file):
    if text == textTr: # do not add not translated
        return
    if not text in po_dict: # add new
        po_dict[text] = textTr
        return
    if po_dict[text] != textTr: # a different than already stored
        tryPreferred(text, textTr, po_dict, po_file)

def po_to_dict(po_file):
    print("Collect data for %s..." % basename(po_file))
    po_dict = {}
    po_parsed = polib.pofile(po_file)
    for entry in po_parsed:
        text = entry.msgid
        textTr = entry.msgstr
        texts = text.split("/", 1)
        textsTr = textTr.split("/", 1)
        if len(texts) > 1 and len(texts) == len(textsTr):
            for i in range(len(texts)):
                tryAdd(texts[i], textsTr[i], po_dict, po_file)
        else:
            tryAdd(text, textTr, po_dict, po_file)

    return po_dict


po_files = find_po_files()
for po_file in po_files:
    po_dict = po_to_dict(po_file)
    #print(po_dict)
