#ifndef INSETS_H
#define INSETS_H

#include <QObject>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT Insets : public QObject
{
    Q_OBJECT
public:
    explicit Insets(QObject *parent = 0);
    /**
     * The inset from the top.
     * This value is added to the Top of the rectangle
     * to yield a new location for the Top.
     *
     * @serial
     * @see #clone()
     */
    /*public*/ int top;

    /**
     * The inset from the left.
     * This value is added to the Left of the rectangle
     * to yield a new location for the Left edge.
     *
     * @serial
     * @see #clone()
     */
    /*public*/ int left;

    /**
     * The inset from the bottom.
     * This value is subtracted from the Bottom of the rectangle
     * to yield a new location for the Bottom.
     *
     * @serial
     * @see #clone()
     */
    /*public*/ int bottom;

    /**
     * The inset from the right.
     * This value is subtracted from the Right of the rectangle
     * to yield a new location for the Right edge.
     *
     * @serial
     * @see #clone()
     */
    /*public*/ int right;
    /*public*/ Insets(int top, int left, int bottom, int right, QObject* parent = 0);
    /*public*/ void set(int top, int left, int bottom, int right);
    /*public*/ bool equals(QObject* obj);
    /*public*/ int hashCode();
    /*public*/ QString toString();
    /*public*/ QObject* clone();

signals:

public slots:

};

#endif // INSETS_H
