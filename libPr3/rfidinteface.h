#ifndef RFIDINTEFACE_H
#define RFIDINTEFACE_H

class RfidMessage;
class RfidListener;

/*public*/ class RfidInterface {

 /*public*/ virtual void addRfidListener( RfidListener* l);
 /*public*/ virtual void removeRfidListener( RfidListener* l);

 bool status();   // true if the implementation is operational

 virtual void sendRfidMessage(RfidMessage* m, RfidListener* l);  // 2nd arg gets the reply
};

#endif // RFIDINTEFACE_H
