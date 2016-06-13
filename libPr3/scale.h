#ifndef SCALE_H
#define SCALE_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT Scale : public QObject
{
    Q_OBJECT
public:
    // Scale definitions
    /*public*/ static /*final*/ const int Z = 0x01;	//  1:220
    /*public*/ static /*final*/ const int N = 0x02;	//  1:160
    /*public*/ static /*final*/ const int TT = 0x03;	//  1:120
    /*public*/ static /*final*/ const int HO = 0x04;  //  1:87
    /*public*/ static /*final*/ const int S = 0x05;   //  1:64
    /*public*/ static /*final*/ const int O = 0x06;	//  1:48
    /*public*/ static /*final*/ const int G = 0x07;   //  1:24
    /*public*/ static /*final*/ const int UK_N = 0x08;  //  1:148
    /*public*/ static /*final*/ const int UK_OO = 0x09; //  1:76.2
    /*public*/ static /*final*/ const int UK_O = 0x0A;  //  1:43.5

    /*public*/ static /*final*/ const int NUM_SCALES = 10;
/**
 * scaleFactor is a number less than 1 representing the
 * reduction from full size.
 */
/*public*/ static double getScaleFactor (int scale);
/**
 * Provide a standard human-readable indication of scale
 * that includes both name (letter) and reduction ratio.
 */
/*public*/ static QString getScaleID(int scale);
/**
 * Provide the short name for the scale.
 */
/*public*/ static QString getShortScaleID(int scale);

explicit Scale(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SCALE_H
