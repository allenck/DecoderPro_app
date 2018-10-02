#ifndef INITEVENTLISTENER_H
#define INITEVENTLISTENER_H
#include <QObject>
/**
 * Custom listener to respond to redisplay of a tabbed pane.
 */
/*public*/ class InitEventListener : public QObject
{
public:
    virtual void onInitEvent(int /*choice*/, int /*selectedPane*/);
};

#endif // INITEVENTLISTENER_H
