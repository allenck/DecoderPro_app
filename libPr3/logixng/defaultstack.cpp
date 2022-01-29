#include "defaultstack.h"
#include "exceptions.h"
/**
 * The default implementation of a NamedTable
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultStack implements Stack {




    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultStack::push(QVariant value) {
//        System.out.format("Stack.push: %s, count: %d%n", value, _count);
        if (_count+1 >= _size) {
            QVector<QVariant> newStack = QVector<QVariant>(_size + GROW_SIZE);
            //System.arraycopy(_stack, 0, newStack, 0, _size);
            for (int i = 0; i< _stack.length(); i++)
             newStack.replace(i, _stack.at(i));
            _stack = newStack;
            _size += GROW_SIZE;
        }
        _stack[_count++] = value;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant DefaultStack::pop() {
//        System.out.format("Stack.pop: %s, count: %d%n", _stack[_count-1], _count);
        if (_count <= 0) throw new ArrayIndexOutOfBoundsException("Stack is empty");
        return _stack[--_count];
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant DefaultStack::getValueAtIndex(int index) {
//        System.out.format("Stack.getValueAtIndex: %d, %s%n", index, _stack[index]);
        return _stack[index];
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultStack::setValueAtIndex(int index, QVariant value) {
//        System.out.format("Stack.setValueAtIndex: %d, %s%n", index, value);
        _stack[index] = value;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int DefaultStack::getCount() {
        return _count;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultStack::setCount(int newCount) {
        if ((newCount < 0) || (newCount > _count))
         throw new IllegalArgumentException("newCount has invalid value: " + QString::number(newCount));
        _count = newCount;
    }
