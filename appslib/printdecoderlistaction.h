#ifndef PRINTDECODERLISTACTION_H
#define PRINTDECODERLISTACTION_H
#include "abstractaction.h"
#include "jframe.h"
#include "appslib_global.h"

class DecoderFile;
class HardcopyWriter;
class Logger;
class APPSLIBSHARED_EXPORT PrintDecoderListAction : public AbstractAction
{
 Q_OBJECT
public:
 //explicit PrintDecoderListAction(QObject *parent = 0);
 /*public*/ PrintDecoderListAction(QString actionName, JFrame* frame, bool preview, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 /**
  * Frame hosting the printing
  */
 JFrame* mFrame;
 /**
  * Variable to set whether this is to be printed or previewed
  */
 bool isPreview;
 Logger* log;
 void printEntry(DecoderFile* d, HardcopyWriter* w) ;
 void printMfg(DecoderFile* d, HardcopyWriter* w);
 void printFamily(DecoderFile* d, HardcopyWriter* w);

};

#endif // PRINTDECODERLISTACTION_H
