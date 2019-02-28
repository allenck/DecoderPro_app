#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <test/testbase.h>



class PythonQtShell_TestBase : public TestBase
{
public:
    PythonQtShell_TestBase(QObject*  parent = nullptr):TestBase(parent),_wrapper(NULL) {}

   ~PythonQtShell_TestBase();

virtual QString  base3();
virtual QString  base4();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_TestBase : public TestBase
{ public:
inline QString  py_q_base3() { return TestBase::base3(); }
inline QString  py_q_base4() { return TestBase::base4(); }
};

class PythonQtWrapper_TestBase : public QObject
{ Q_OBJECT
public:
public slots:
TestBase* new_TestBase(QObject*  parent = nullptr);
void delete_TestBase(TestBase* obj) { delete obj; } 
   QString  base1(TestBase* theWrappedObject);
   QString  base2(TestBase* theWrappedObject);
   QString  base3(TestBase* theWrappedObject);
   QString  py_q_base3(TestBase* theWrappedObject){  return (((PythonQtPublicPromoter_TestBase*)theWrappedObject)->py_q_base3());}
   QString  base4(TestBase* theWrappedObject);
   QString  py_q_base4(TestBase* theWrappedObject){  return (((PythonQtPublicPromoter_TestBase*)theWrappedObject)->py_q_base4());}
   QWidget*  getWidget(TestBase* theWrappedObject);
};





class PythonQtShell_TestIntermediate : public TestIntermediate
{
public:
    PythonQtShell_TestIntermediate(QObject*  parent = nullptr):TestIntermediate(parent),_wrapper(NULL) {}

   ~PythonQtShell_TestIntermediate();

virtual QString  base3();
virtual QString  base4();
virtual QString  intermediate3();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_TestIntermediate : public TestIntermediate
{ public:
inline QString  py_q_base3() { return TestIntermediate::base3(); }
inline QString  py_q_intermediate3() { return TestIntermediate::intermediate3(); }
};

class PythonQtWrapper_TestIntermediate : public QObject
{ Q_OBJECT
public:
public slots:
TestIntermediate* new_TestIntermediate(QObject*  parent = nullptr);
void delete_TestIntermediate(TestIntermediate* obj) { delete obj; } 
   QString  py_q_base3(TestIntermediate* theWrappedObject){  return (((PythonQtPublicPromoter_TestIntermediate*)theWrappedObject)->py_q_base3());}
   QMenu*  getMenu(TestIntermediate* theWrappedObject);
   QString  intermediate1(TestIntermediate* theWrappedObject);
   QString  intermediate2(TestIntermediate* theWrappedObject);
   QString  intermediate3(TestIntermediate* theWrappedObject);
   QString  py_q_intermediate3(TestIntermediate* theWrappedObject){  return (((PythonQtPublicPromoter_TestIntermediate*)theWrappedObject)->py_q_intermediate3());}
};





class PythonQtShell_TestPrimary : public TestPrimary
{
public:
    PythonQtShell_TestPrimary(QObject*  parent = nullptr):TestPrimary(parent),_wrapper(NULL) {}

   ~PythonQtShell_TestPrimary();

virtual QString  base3();
virtual QString  base4();
virtual QString  intermediate3();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_TestPrimary : public TestPrimary
{ public:
inline QString  py_q_base4() { return TestPrimary::base4(); }
};

class PythonQtWrapper_TestPrimary : public QObject
{ Q_OBJECT
public:
public slots:
TestPrimary* new_TestPrimary(QObject*  parent = nullptr);
void delete_TestPrimary(TestPrimary* obj) { delete obj; } 
   QString  py_q_base4(TestPrimary* theWrappedObject){  return (((PythonQtPublicPromoter_TestPrimary*)theWrappedObject)->py_q_base4());}
   int  getInt(TestPrimary* theWrappedObject);
   QString  primary1(TestPrimary* theWrappedObject);
   QString  primary2(TestPrimary* theWrappedObject);
};


