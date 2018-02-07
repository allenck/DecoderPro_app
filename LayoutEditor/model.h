#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Region;
class Model : public QObject
{
 Q_OBJECT
public:
 explicit Model(QObject *parent = nullptr);
 // for now, we only allow one Model
 static Model* _instance;// = null;
 static /*public*/ Model* instance();
 void loadValues();
 /*public*/ void dispose();
 /*public*/ void addRegion(Region* r);
 /*public*/ void removeRegion(Region* r);

signals:

public slots:
private:
 QList<Region*>* regions;// = new ArrayList<Region>();
 void setInitialModel();

};

#endif // MODEL_H
