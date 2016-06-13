#include "abstractmessage.h"

//AbstractMessage::AbstractMessage(QObject *parent) :
//    Message(parent)
//{
//}
/**
 * Add description of class here.
 *
 * @author Bob Jacobsen  Copyright 2007, 2008
 * @version   $Revision: 17977 $
 */
///*public*/ abstract class AbstractMessage implements Message {

/** Creates a new instance of AbstractMessage */
/*public*/ AbstractMessage::AbstractMessage(QObject *parent)
{
 this->parent = parent;
 log = new Logger("AbstractMessage");
 _dataChars = NULL;

 _nDataChars = 0;

}

/*public*/ AbstractMessage::AbstractMessage(int n)
{
 if (n<1)
        log->error("invalid length in call to ctor");
    _nDataChars = n;
    _dataChars = new QByteArray[n];
}

/*public*/ AbstractMessage::AbstractMessage(QString s)
{
 //this(s.length());
 QByteArray ba = s.toLatin1();
 for (int i = 0; i<_nDataChars; i++)
  _dataChars->replace(i, ba.at(i));
}

//@SuppressWarnings("NULL")
/*public*/ AbstractMessage::AbstractMessage(AbstractMessage* m)
{
 if (m == NULL)
  log->error("copy ctor of NULL message throws exception");
 _nDataChars = m->_nDataChars;
 _dataChars = new QByteArray[_nDataChars];
 for (int i = 0; i<_nDataChars; i++) _dataChars->replace(i, m->_dataChars->at(i));
}

/*public*/ int AbstractMessage::getElement(int n) {return _dataChars->at(n);}


// accessors to the bulk data
/*public*/ int AbstractMessage::getNumDataElements() {return _nDataChars;}

/*public*/ void AbstractMessage::setElement(int n, int v) {_dataChars->replace(n, v);  }



//    /*private*/ static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractMessage.class.getName());

//}
