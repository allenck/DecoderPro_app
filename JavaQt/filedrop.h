#ifndef FILEDROP_H
#define FILEDROP_H

#include <QObject>
#include "component.h"
#include "droptargetlistener.h"

class MyDropTargetListener;
class Logger;
class PrintStream;
class DropTargetListener;
class Border;
class File;
class FileDrop : public QObject
{
 Q_OBJECT
public:
 /*public*/ /*interface*/class Listener {

    /**
     * This method is called when files have been successfully dropped.
     *
     * @param files An array of <tt>File</tt>s that were dropped.
     * @since 1.0
     */
    /*public*/ /*abstract*/void filesDropped(QList<File*> /*files*/) {}
  friend class MyDropTargetListener;
 };   // end inner-interface Listener

 /*public*/ FileDrop(
         Component* c,
         /*final*/ Listener* listener, QObject* parent = 0);
 /*public*/ FileDrop(
         PrintStream* out,
         Component* c,
         Border* dragBorder,
         bool recursive,
         Listener* listener, QObject* parent);
 /*public*/ static bool remove(Component* c);
 /*public*/ static bool remove(PrintStream* out, Component* c, bool recursive);   // Make sure we support dnd.
 Listener* listener;

signals:
 void dropFiles(QList<File*>);


private:
 /*private*/ Border* normalBorder;
 /*private*/ MyDropTargetListener* dropListener;
 void common(PrintStream* out, Component* c, Border* dragBorder, bool recursive, Listener* listener);
 /*private*/ static bool supportsDnD();   // Static Boolean
 /*private*/ void makeDropTarget(PrintStream* out, Component* c, bool recursive);
 Component* c;
 Border* dragBorder;

 /**
  * Discover if the running JVM is modern enough to have drag and drop.
  */
 /*private*/ static bool _supportsDnD;
 PrintStream* out;

 // Default border color
 /*private*/ static QColor defaultBorderColor;// = new java.awt.Color(0f, 0f, 1f, 0.25f);
 Logger * log;
 /*private*/ bool isDragOk(PrintStream* out, /*final*/ QDropEvent* evt);

 friend class MyDropTargetListener;
};  // end class FileDrop

class MyDropTargetListener : public DropTargetListener
{
 Q_OBJECT
 FileDrop* fileDrop;
 MyDropTargetListener(FileDrop* fileDrop, QObject* parent = 0);
public:
 /*public*/ void dragEnter(QDragEnterEvent* evt);
 /*public*/ void dragOver(QDragMoveEvent* evt);
 /*public*/ void drop(QDropEvent* evt);
 /*public*/ void dragExit(QDragLeaveEvent* evt);
 /*public*/ void dropActionChanged(QDropEvent* evt);

signals:
 void dropFiles(QList<File*>);

private:
 Logger* log;

 friend class FileDrop;
};

#endif // FILEDROP_H
