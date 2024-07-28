#!/bin/bash
# Run the following command under "..src/StringTools" not under the "docs" folder!
# Run: `chmod +x ./docs/init.sh && ./docs/init.sh`
# In case of errors, read:
# https://stackoverflow.com/questions/46830847/pdflatex-not-found-pdflatex-is-needed-for-pdf-output

cd ./docs

# Run Doxygen
doxygen Doxyfile

cd ./latex

# Run makeindex and pdflatex commands to generate the PDF
makeindex ./refman.idx
# Run pdflatex multiple times to resolve references
pdflatex ./refman.tex

cd ../

# Move the generated PDF to docs
mv -v ./latex/refman.pdf ./StringTools.pdf
