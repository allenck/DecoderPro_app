#ifndef STOREXMLVSDECODERACTION_H
#define STOREXMLVSDECODERACTION_H
#include "abstractaction.h"

class File;
class StoreXmlVSDecoderAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit StoreXmlVSDecoderAction(QObject *parent);
 /*public*/ StoreXmlVSDecoderAction(QString s,QObject *parent);
 /*public*/ void saveVSDecoderProfile(File* f);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};

#endif // STOREXMLVSDECODERACTION_H
