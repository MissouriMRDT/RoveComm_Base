---
layout: default
title: "10. Pandoc Single Markdown & PDF Compilation"
---

# Chapter 10: Pandoc Single Markdown & PDF Compilation

In addition to serving as a responsive web manual on `docs.themrdt.org`, the RoveComm documentation can be compiled into a single, unified, publication-grade PDF manual: **`RoveComm_Manual.pdf`**.

This enables team members, competition judges at the University Rover Challenge (URC), and new recruits to read the complete protocol manual offline or print physical copies.

---

## 1. Toolchain Prerequisites

Compiling the PDF requires `pandoc` and a LaTeX distribution (`pdflatex`):

### Ubuntu / Debian / WSL2

```bash
sudo apt-get update
sudo apt-get install -y pandoc texlive-latex-base texlive-fonts-recommended texlive-extra-utils texlive-latex-extra
```

### Windows (Native)

- Install [Pandoc](https://pandoc.org/installing.html) via Chocolatey or Windows Installer: `choco install pandoc`
- Install [MiKTeX](https://miktex.org/) or [TeX Live](https://www.tug.org/texlive/).

---

## 2. Compilation Script (`compile_rovecomm_pandoc.sh`)

MRDT provides an automated compiler script in `tools/compile_rovecomm_pandoc.sh`:

```bash
# Execute from the root of RoveComm_Base repository
bash tools/compile_rovecomm_pandoc.sh
```

### Script Execution Pipeline

1. **Table of Contents Parsing**: The script scans `docs/00_Table_of_Contents.md` to extract chapter file paths in sequential order.
2. **Markdown Assembly**: It prepends Pandoc YAML metadata (title, author, date, margin, link coloring) and concatenates every chapter file into an intermediate monolith: `docs/RoveComm_Guide_Pandoc.md`.
3. **LaTeX Page Delimitation**: A `\newpage` macro is inserted between consecutive chapters to ensure each chapter begins on a fresh page.
4. **Pandoc PDF Generation**: Invokes `pandoc` with `--pdf-engine=pdflatex`, generating a hyperlinked table of contents, numbered section headers, and syntax-highlighted code blocks.
5. **Output**: Produces `docs/RoveComm_Manual.pdf`.

---

## 3. Formatting Rules for Pandoc Compatibility

To guarantee clean PDF compilation without LaTeX errors:

- **Strict ASCII Trees**: Directory structures and flowcharts must use ASCII characters (`|--`, `+--`, `\--`, `|`) rather than Unicode box-drawing symbols (`├`, `│`, `└`), as standard `pdflatex` fails on multi-byte unicode box characters.
- **Leading Blank Lines**: All bulleted lists and numbered steps must be preceded by a blank line.
- **Backtick Shielding**: Shell variables containing dollar signs (`$VAR`, `$HOME`) must be enclosed in code backticks to prevent MathJax / LaTeX from interpreting them as inline math.
