# Timezone translations

The po files in this folder were taken from [1].
Note that en_US is missing. Let's assume untranslated texts match en_US.

To add a new translation:

1. Get po-file from [1]
2. Rename file to full locale e.g de.po -> de_DE.po
3. Run script create-translations-from-po-files.py
4. Add *.qm generated to timezonetranslations.qrc


[1] https://gitlab.gnome.org/GNOME/gnome-control-center/-/tree/main/panels/system/datetime/po-timezones
