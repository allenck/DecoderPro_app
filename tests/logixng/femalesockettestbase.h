#ifndef FEMALESOCKETTESTBASE_H
#define FEMALESOCKETTESTBASE_H

#include <QObject>
#include "manager.h"
#include "atomicboolean.h"
#include "malesocket.h"
#include "logixng.h"
#include "symboltable.h"

class FemaleSocketTestBase : public QObject
{
    Q_OBJECT
public:
    explicit FemaleSocketTestBase(QObject *parent = nullptr);
    /*public*/  /*final*/ bool isConnectionClassesEquals(
            QHash<Category*, QList</*Class<? extends Base>*/QString>> expectedMap,
            QHash<Category*, QList</*Class<? extends Base>*/QString>> actualMap);

signals:
public slots:
    /*public*/  void testBadSocketName();
    /*public*/  void testSetup() /*throws SocketAlreadyConnectedException*/;
    /*public*/  void testConnectIncompatibleSocket();
    /*public*/  void testConnect();
    /*public*/  void testDisconnect() /*throws SocketAlreadyConnectedException*/;
    /*public*/  void testSetParentForAllChildren() /*throws SocketAlreadyConnectedException */;
    /*public*/  void testValidateName();
    /*public*/  void testSetName();
    /*public*/  void testDisposeWithoutChild();
    /*public*/  void testDisposeWithChild() /*throws SocketAlreadyConnectedException*/;
    /*public*/  void testMethodsThatAreNotSupported();
    /*public*/  void testCategory();
    /*public*/  void testSWISystemName();

private:
    /*private*/ /*SortedSet*/QSet<QString> getClassNames(QList</*Class<? extends Base>*/QString> classes);
    /*private*/ bool isSetsEqual(Category* category, /*SortedSet*/QSet<QString> set1, /*SortedSet*/QSet<QString> set2);
    /*private*/ bool setName_verifyException(QString newName, QString expectedExceptionMessage);
    /*private*/ class IncompatibleMaleSocket : MaleSocket {
    public:
        //@Override
        /*public*/  void setEnabled(bool enable) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setEnabledFlag(bool enable) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool isEnabled() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  Base* getObject() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setDebugConfig(DebugConfig* config)override {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  DebugConfig* getDebugConfig() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  DebugConfig* createDebugConfig() override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  QString getSystemName()const override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  QString getUserName() const override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setUserName(QString s) /*throws NamedBean.BadUserNameException*/ {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  QString getComment() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setComment(QString s) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  QString getShortDescription(QLocale locale) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  QString getLongDescription(QLocale locale) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  ConditionalNG* getConditionalNG() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  LogixNG* getLogixNG() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  LogixNG* getRoot() override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  Base* getParent() const override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setParent(Base* parent) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  bool setParentForAllChildren(QList<QString> errors) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  int getChildCount() override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  Category* getCategory() override {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void dispose() {
            throw new UnsupportedOperationException("Not supported.");
        }
/*
        //@Override
        public  void registerListeners() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        public  void unregisterListeners() override{
            throw new UnsupportedOperationException("Not supported.");
        }
*/
        //@Override
        /*public*/  void printTree(PrintTreeSettings* settings, PrintWriter* writer, QString indent, /*MutableInt*/int* lineNumber)override {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void printTree(PrintTreeSettings* settings, QLocale locale, PrintWriter* writer, QString indent, /*MutableInt*/int* lineNumber) override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void printTree(PrintTreeSettings* settings, QLocale locale, PrintWriter* writer, QString indent, QString currentIndent, /*MutableInt*/int* lineNumber)override {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  bool isActive() override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(PropertyChangeListener* listener)override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener)override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  QVector<PropertyChangeListener*> getPropertyChangeListeners() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void removePropertyChangeListener(PropertyChangeListener* listener) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  ErrorHandlingType::TYPES getErrorHandlingType() override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setErrorHandlingType(ErrorHandlingType errorHandlingType) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(PropertyChangeListener* listener, QString name, QString listenerRef) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener, QString name, QString listenerRef)override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void updateListenerRef(PropertyChangeListener* l, QString newName) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  QString getListenerRef(PropertyChangeListener* l) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  QList<QString> getListenerRefs()override {
            throw new UnsupportedOperationException("Not supported");
        }

        /** {@inheritDoc} */
        //@Override
        /*public*/  void getListenerRefsIncludingChildren(QList<QString> list) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  int getNumPropertyChangeListeners() override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  QList<PropertyChangeListener*> getPropertyChangeListenersByReference(QString name) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  BaseManager/*<? extends NamedBean>*/* getManager() override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addLocalVariable(QString name, InitialValueType::TYPES initialValueType, QString initialValueData) override {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void addLocalVariable(VariableData* variableData) override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void clearLocalVariables() override{
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  QSet<VariableData*> getLocalVariables()override {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void registerListeners() override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void unregisterListeners()override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  Base* getDeepCopy(QHash<QString, QString> map, QHash<QString, QString> map1) /*throws JmriException*/ {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  Base* deepCopyChildren(Base* base, QHash<QString, QString> map, QHash<QString, QString> map1) /*throws JmriException*/ {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool getListen()override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setListen(bool listen)override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool isLocked()override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setLocked(bool locked)override {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool isSystem() override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setSystem(bool system) override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool getCatchAbortExecution() override{
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setCatchAbortExecution(bool catchAbortExecution) override{
            throw new UnsupportedOperationException("Not supported");
        }
     QObject* bself() override {return (QObject*)this;}
    };
protected:
    /*protected*/ Manager/*<? extends NamedBean>*/* manager;
    /*protected*/ AtomicBoolean* flag;
    /*protected*/ AtomicBoolean* errorFlag;
    /*protected*/ MaleSocket* maleSocket;
    /*protected*/ MaleSocket* otherMaleSocket;
    /*protected*/ FemaleSocket* _femaleSocket;
    /*protected*/ /*abstract*/virtual  Manager/*<? extends NamedBean>*/* getManager()=0;
    /*protected*/ /*abstract*/ virtual FemaleSocket* getFemaleSocket(QString name)=0;
    /*abstract*/ /*protected*/ virtual bool hasSocketBeenSetup()=0;

};

#endif // FEMALESOCKETTESTBASE_H
