#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>


class Control : public QObject
{
 Q_OBJECT
public:
 //explicit Control(QObject *parent = 0);
 /*public*/ static /*final*/ bool showProperty;// = false;
 /*public*/ static /*final*/ bool showInstance;// = false;
    /*public*/ static /*final*/ bool SHOW_PROPERTY;// = false;

 /*public*/ /*static*/ class Type : public QObject
 {
 public:

     // CONTROL TYPE DEFINES

     // INSTANCE VARIABLES

     /**
      * Type name.
      */
     /*private*/ QString name;


     // CONSTRUCTOR
 protected:
     /**
      * Constructs a new control type with the name specified.
      * The name should be a descriptive string appropriate for
      * labelling the control in an application, such as "Gain" or "Balance."
      * @param name  the name of the new control type.
      */
     /*protected*/ Type(QString name, QObject* parent = 0);
 public:

     // METHODS

     /**
      * Finalizes the equals method
      */
     /*public*/ /*final*/ bool equals(QObject* obj);

 //    /**
 //     * Finalizes the hashCode method
 //     */
 //    /*public*/ /*final*/ int hashCode() {
 //        return super.hashCode();
 //    }

     /*public*/ /*final*/ QString toString();
 }; // class Type
 /*public*/ Type* getType();
 /*public*/ QString toString();

signals:

public slots:
private:
 // INSTANCE VARIABLES

 /**
  * The control type.
  */
 /*private*/ /*final*/ Type* type;
protected:
 /*protected*/ Control(Type* type, QObject* parent = 0);

};

#endif // CONTROL_H
