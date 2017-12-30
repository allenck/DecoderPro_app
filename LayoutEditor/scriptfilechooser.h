#ifndef SCRIPTFILECHOOSER_H
#define SCRIPTFILECHOOSER_H
#include "jfilechooser.h"

class ScriptFileChooser : public JFileChooser
{
public:
 ScriptFileChooser(QObject* parent = 0);
 /*public*/ ScriptFileChooser(QString path, QObject* parent = 0) ;
 /*public*/ ScriptFileChooser(File* dir, QObject* parent = 0);

private:
 /*private*/ QString fileForLanguage(QString language);
 /*private*/ void init();

};

#endif // SCRIPTFILECHOOSER_H
