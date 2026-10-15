# guition_tof_wake: a plugin for Tessera

This repository is one plugin for Tessera, the ESP32 touch screens for Home Assistant. Its rules, docs and tools live
in the plugins repository. Clone it beside this repository and read its AGENTS.md before making changes.

```sh
git clone https://github.com/MaxGramser/tessera-plugins ../tessera-plugins
```

- Rules and docs: `../tessera-plugins/AGENTS.md`
- Check: `python3 ../tessera-plugins/tools/check.py .`
- Preview: `python3 ../tessera-plugins/tools/preview.py . --strict`
- Store image: `python3 ../tessera-plugins/tools/store_image.py .`
