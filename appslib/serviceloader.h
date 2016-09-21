#ifndef SERVICELOADER_H
#define SERVICELOADER_H

#include <QObject>

class ClassLoader;
template <typename S>
class ServiceLoader : public QObject
{
 Q_OBJECT
public:
 explicit ServiceLoader(QObject *parent = 0);

signals:

public slots:
private:
 /*private*/ static /*final*/ QString PREFIX;// = "META-INF/services/";
 // The class or interface representing the service being loaded
 /*private*/ /*final*/ Class<S> service;

 // The class loader used to locate, load, and instantiate providers
 /*private*/ /*final*/ ClassLoader* loader;

 // The access control context taken when the ServiceLoader is created
 ///*private*/ final AccessControlContext acc;

 // Cached providers, in instantiation order
 /*private*/ LinkedHashMap<String,S> providers = new LinkedHashMap<>();

 // The current lazy-lookup iterator
 /*private*/ LazyIterator lookupIterator;

};

#endif // SERVICELOADER_H
