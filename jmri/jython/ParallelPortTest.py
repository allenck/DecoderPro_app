# Try to send some bytes to a parallel port
#
# Author: Bob Jacobsen, copyright 2008
# Part of the JMRI distribution
#
# The next line is maintained by CVS, please don't change it
# $Revision: 27263 $

name = "LPT1" 

# find the port info and open the port
import gnu.io
port = gnu.io.CommPortIdentifier.getPortIdentifier(name)
parallelPort = port.open("JMRI", 50)
outputStream = parallelPort.getOutputStream()
print "Port opened OK"

# setup now complete, try to send some bytes
outputStream.write(184)
outputStream.flush()

outputStream.write(185)
outputStream.flush()

outputStream.write(186)
outputStream.flush()

print "Bytes sent OK"

# done, close and clean up
outputStream.close()
parallelPort.close()

print "End of Script"
