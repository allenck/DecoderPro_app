# C++ port of the Java JMRI model railroad software.(JmriQt)

This repository contains a port of the Java JMRI Model Railroad Interface software to QT (C++).
The majority of JMRI code has been ported except only Digitrax (LocoNet) and SProg hardware is supported.

In addition, scripting and Audio support still needs more work.


This project was started because I wanted better support for the LocoIO series of boards so users of that
hardware might find this port of interest.

Scripting support requires that Python and Python Qt be installed.
Also, zip files require the Quazip package be installed.
Although this project was started using Qt 4, recent development has
been using Qt 5.
The addition of WebServer support requires that QT version 5.6 or
later be used. Current development has been with Qt 5.11.3

## Suggested steps to compile the first time

   1. Create an Environment variable "PROJ_DIR" that specifies the location of your projects directory where the various packages are kept. The Projects folder well then contain one or more flders/directoried with different projects.
   2. Make sure you have either an installed copy of the Java JMRI app or have downloaded the source from JMRI. It is needed to provide resources like icons and other resources. It is best to insure that you have an environment variable "JMRI_PROG" set to the location of the JMRI code.  (Jmri Code: Getting the Code)
   3. Make sure that you have a copy of QtZeroConf  installed and compiled. (It can be downloaded from https://github.com/jbagg/QtZeroConf It requires that the libavhi-client-dev package be installed.)
   4. In QtCreator open project "jmri.pro". Make sure that  thw shadow build box is not checked!
   5. Build the JavaQt sub-project.
   6. Build the QtWebApp sub-project.
   7. Insure that QuaZip has been installed on your system. (The package (version 0.7.3) can be downloaded from https://sourceforge.net/projects/quazip/files/latest/download)
   8. Modify the appslib.pro  file to comment out each of the parts referencing other libraries: (libPr3, libPref, Tables, LayoutEditor, LocoIO but not JavaQt. DO NOT comment the "INCLUDPATH" or "DEPENDPATH" statements for these libraries! This will allow the initial libappslib.so file to be created although there will be a large number of undefined references to other libraries not built. When the other libraries have been built, the lines commented out here can be restored.  Now build sub-project appslib. Verify that the lib file. appslib.so has been created.
   9. Now do the same for sub-project LayoutEditor.pro; comment out references to other libraries (except JavaQt and appslib which are already built).
  10. Now, build sub-project libPr3. Comment out references to libraries not yet built, e.g. libPref, LocoIO, Tables.
  11. Once libPr3 is complete and libPr3.so has been created, proceed to build sub-project libPref, commening out the reference to lib locoio.
  12. And once libPref is complete, we can build sub-project LocoIO. It won't be necessary to comment any references to any other libs since they should have been built.
  13. Now build sub-project Tables. No library references to other sub-projects need to be commented out as they should have been built.
  14. When Tables has been successfully built, go back and un-comment the lib references in appslib, libPr3, LayoutEditor, lipPref .pro files
  15. After un-commenting the lines in the .pro files that was done earlier, build the sub-projects again to pick up the references to functions and classes in the other lobraries.
  16. Now, we can build the app PanelPro. Build the sub-project PanelPro.
  17. After PanelPro has compiled successfully, you can go click on the Qt Creator "Projects" icon in the left side panel and then select PanelPro executable which can then be run using the run button or the debug button.

  For more information see [Compiling](wiki/Compiling.wiki)
