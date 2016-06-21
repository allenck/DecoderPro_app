 #!/bin/bash

# run this script to generate python bindings for classes specified in "wrappers.h"

export QTDIR=/home/allen/Qt5.4.1/5.4/gcc_64
../../../../PythonQt3.0/generator/pythonqt_generator --include-paths=../libPr3/:/Roster --output-directory=. wrappers.h typesystem_jmri.xml

