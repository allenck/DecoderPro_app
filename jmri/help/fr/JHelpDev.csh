#! /bin/csh -f
#
# csh script to launch JHelpDex with the current directory set
#
#($Revision: 1.3 $)
#

java -DHOMEDIR=${PWD} -Djava.io.tmpdir=/tmp -Xmx500m -classpath ".:jhelpdev.jar:lib/jhall.jar:lib/xmlenc.jar" net.sourceforge.jhelpdev.JHelpDevFrame
