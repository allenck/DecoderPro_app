#ifndef FILEUTILSUPPORTTEST_H
#define FILEUTILSUPPORTTEST_H

#include <QObject>
#include "exceptions.h"
#include "file.h"
#include "fileutilsupport.h"

class FileUtilSupportTest : public QObject
{
  Q_OBJECT
 public:
  explicit FileUtilSupportTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp() throw (Exception) ;
 Q_INVOKABLE /*public*/ void tearDown();

 signals:

 public slots:
  /*public*/ void testGEFRel();
  /*public*/ void testGEFAbs();
  /*public*/ void testGEFProgramRel();
  /*public*/ void testGEFProgramAbs();
  /*public*/ void testGEFPrefRel();
  /*public*/ void testGEFPrefAbs();
  /*public*/ void testGEFHomeRel();
  /*public*/ void testGEFHomeAbs();
  /*public*/ void testGetpfPreferenceF() /*throw (IOException)*/;
  /*public*/ void testGetpfPreferenceS();
  /*public*/ void testGetpfResourceF() /*throw (IOException)*/;
  /*public*/ void testGetpfPrefF() /*throw (IOException)*/;
  /*public*/ void testGetpfProgramF() /*throw (IOException)*/;
  /*public*/ void testGetpfProgramS();
  /*public*/ void testGetpfProgramDirS();
  /*public*/ void testGetpfHomeS();
  /*public*/ void testGetpfHomeF() /*throw (IOException)*/;
  /*public*/ void testGAFRel();
  /*public*/ void testGAFProgRel() /*throw (IOException)*/;
  /*public*/ void testGAFProgAbs() /*throw (IOException)*/;
  /*public*/ void testGAFPrefRel() /*throw (IOException)*/;
  /*public*/ void testGAFPrefAbs() /*throw (IOException)*/;
  /*public*/ void testGAFHomeRel() /*throw (IOException)*/;
  /*public*/ void testGAFHomeAbs() /*throw (IOException)*/;
//  /*public*/ void testCopyFile() throw (FileNotFoundException);
//  /*public*/ void testCopyDirectoryToExistingDirectory() throw (FileNotFoundException, IOException);
//  /*public*/ void testDeleteFile() /*throw (IOException)*/;
//  /*public*/ void testAppendTextToFile() /*throw (IOException)*/;
//  /*public*/ void testFindURIPath();
//  /*public*/ void testFindURIPathLocation();
//  /*public*/ void testFindURIPathSearchPaths();
//  /*public*/ void testFindExternalFilename();

 private:
  /*private*/ File* programTestFile;
  /*private*/ File* preferencesTestFile;
  /*private*/ FileUtilSupport* instance;

};

#endif // FILEUTILSUPPORTTEST_H
