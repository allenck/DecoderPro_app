#! /bin/sh
#
# Script to process decoder file with xinclude
#
eval cd ~/NetBeansProjects/jmri/xml/decoders
if [ -e $1 ] 
then
 echo will process $1
 b='.bak'
 backupfile=$1$b
 if [ -e $backupfile ]
 then
  echo $backupfile 'exists'
  infile=$1'.tmp'
  eval mv $1 $infile
 else
  echo $backupfile 'does not exist, creating it first!' 
  eval mv $1 $backupfile
  infile=$backupfile
 fi
  eval xmllint --xinclude $infile > $1
  eval ls -l $1
fi
