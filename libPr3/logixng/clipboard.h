#ifndef CLIPBOARD_H
#define CLIPBOARD_H
//#include "malesocket.h"
//#include "femalesocket.h"
//#include "defaultfemaleanysocket.h"
#include <QtCore>

class AbstractFemaleSocket;
class MaleSocket;
/**
 * The clipboard with actions and expressions
 *
 * @author Daniel Bergqvist (C) 2020
 */
/*public*/ /*interface*/class  Clipboard
{
    public:
    /**
     * Is the clipboard empty?
     *
     * @return true if empty, false otherwise
     */
  /*public*/ virtual bool isEmpty(){return false;}

    /**
     * Add an item to the clipboard.
     * <P>
     * The last added item is on the top of the clipboard.
     *
     * @param maleSocket the item to add on the clipboard
     * @param errors a list of potential errors
     * @return true if success, false otherwise
     */
  /*public*/ virtual bool add(MaleSocket* maleSocket, QList<QString> errors){return false;}

    /**
     * Get the top item on the clipboard and remove it from the clipboard.
     * <P>
     * The top item is the last item put on the clipboard
     *
     * @return the top item
     */
    /*public*/ virtual MaleSocket* fetchTopItem(){return nullptr;}

    /**
     * Get the top item on the clipboard without removing it from the clipboard.
     * <P>
     * The top item is the last item put on the clipboard
     *
     * @return the top item
     */
    /*public*/ virtual MaleSocket* getTopItem(){return nullptr;}

    /**
     * Get the female socket root of the clipboard tree.
     *
     * @return the root female socket
     */
  /*public*/ virtual AbstractFemaleSocket* getFemaleSocket() {return nullptr;}

    /**
     * Moves an item on the clipboard to the top of the clipboard.
     * <P>
     * If an item on the clipboard that is not the top item is cut, it's
     * placed as the top item on the clipboard until it's pasted elsewhere.
     *
     * @param maleSocket the male socket to put on the top
     */
  /*public*/ virtual void moveItemToTop(MaleSocket* maleSocket){}

    /**
     * Setup this object and its children.
     * This method is used to lookup system names for child sockets.
     */
  /*public*/ virtual void setup(){}
 virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(Clipboard, "Clipboard")
#endif // CLIPBOARD_H
