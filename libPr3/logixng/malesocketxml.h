#ifndef MALESOCKETXML_H
#define MALESOCKETXML_H
#include <QtXml>

class MaleSocket;
/**
 * Handle XML configuration for MaleSocketXML objects.
 *
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class MaleSocketXml {

 public:
    /*public*/ virtual bool load(QDomElement maleSocketElement, MaleSocket* maleSocket)=0;

};
Q_DECLARE_INTERFACE(MaleSocketXml, "MaleSocketXml")
#endif // MALESOCKETXML_H
