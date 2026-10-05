#!/bin/bash

# Ensure we are in the root directory
if [ ! -d "docs" ]; then
    echo "Error: Run this script from the root of the RoveComm_Base repository."
    exit 1
fi

echo "Compiling the RoveComm Protocol Guide into a single Markdown file for Pandoc..."

DOCS_DIR="docs"
OUTPUT_MD="docs/RoveComm_Guide_Pandoc.md"
OUTPUT_PDF="docs/RoveComm_Manual.pdf"

# Clean up previous compiles
rm -f "$OUTPUT_MD" "$OUTPUT_PDF"

# Create title page (Pandoc YAML frontmatter)
cat << TITLE > "$OUTPUT_MD"
---
title: "RoveComm Protocol Guide"
subtitle: "Architecture, Manifest Ecosystem, Multi-Language Implementations, and Diagnostic Tooling"
author: "Mars Rover Design Team"
date: "$(date +'%B %d, %Y')"
geometry: margin=1in
colorlinks: true
---

\newpage

TITLE

# Append files in order from Table of Contents
echo "Reading Table of Contents to compile sections..."
if [ -f "$DOCS_DIR/00_Table_of_Contents.md" ]; then
    grep -o '([0-9a-zA-Z_/]*\.md)' "$DOCS_DIR/00_Table_of_Contents.md" | tr -d '()' | grep -v '00_Table_of_Contents.md' | while read -r file; do
        if [ -f "$DOCS_DIR/$file" ]; then
            echo "Appending $file..."
            cat "$DOCS_DIR/$file" >> "$OUTPUT_MD"
            printf '\n\n\\newpage\n\n' >> "$OUTPUT_MD"
        fi
    done
fi

echo "Compiled markdown saved to $OUTPUT_MD."

# Generate PDF with Pandoc
if command -v pandoc &> /dev/null
then
    echo "Pandoc found. Generating PDF..."
    pandoc "$OUTPUT_MD" \
        -o "$OUTPUT_PDF" \
        --pdf-engine=pdflatex \
        --toc \
        --toc-depth=3 \
        --number-sections \
        --highlight-style tango \
        -V colorlinks=true \
        -V linkcolor=blue \
        -V urlcolor=blue \
        -V toccolor=black

    if [ -f "$OUTPUT_PDF" ]; then
        echo "Successfully generated PDF: $OUTPUT_PDF"
    else
        echo "Failed to generate PDF."
    fi
else
    echo "Pandoc not found! Install via: sudo apt-get install pandoc texlive-latex-base texlive-fonts-recommended"
fi
