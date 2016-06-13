#ifndef LOADXMLVSDECODERACTION_H
#define LOADXMLVSDECODERACTION_H

#include "abstractaction.h"
#include "xmlfile.h"
#include "appslib_global.h"

/**
 * An extension of the abstract XmlFile. No changes made to that class.
 *
 * @author glen
 * @version $Revision: 28746 $
 */
/*static*/ class APPSLIBSHARED_EXPORT VSDecoderPrefs : public XmlFile
{
 Q_OBJECT
};

class APPSLIBSHARED_EXPORT LoadXmlVSDecoderAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit LoadXmlVSDecoderAction(QObject *parent = 0);
 /*public*/ LoadXmlVSDecoderAction(QString s, QObject *parent);
 /*public*/ bool loadVSDecoderProfile(File* f); //throws java.io.IOException

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 Logger* log;
 JFileChooser* fileChooser;
 void common();

};

#endif // LOADXMLVSDECODERACTION_H
