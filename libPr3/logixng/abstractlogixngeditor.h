#ifndef ABSTRACTLOGIXNGEDITOR_H
#define ABSTRACTLOGIXNGEDITOR_H
#include "eventlistener.h"
/**
 *
 * @author Daniel Bergqvist copyright (c) 2019
 *
 * @param <E> the type of NamedBean supported by this editor
 */
/*public*/ /*interface*/class AbstractLogixNGEditor/*<E extends NamedBean>*/ {
    public:
    /**
     * Create a custom listener event.
     */
    /*public*/ /*interface*/class EditorEventListener : public EventListener {
   public:
    Q_INTERFACES(EventListener)
        /**
         * An event that gets delivered from the editor
         * @param data Contains a list of commands to be processed by the
         *             listener recipient.
         */
        virtual void editorEventOccurred(QMap<QString, QString> data)=0;
    };


    /**
     * Add a listener.
     *
     * @param listener The recipient
     */
  /*public*/ virtual void addEditorEventListener(EditorEventListener* listener){}

    /**
     * Remove a listener -- not used.
     *
     * @param listener The recipient
     */
  /*public*/ virtual void removeEditorEventListener(EditorEventListener* listener){}

  /*public*/ virtual void bringToFront(){}

};
Q_DECLARE_INTERFACE(AbstractLogixNGEditor, "AbstractLogixNGEditor")
#endif // ABSTRACTLOGIXNGEDITOR_H