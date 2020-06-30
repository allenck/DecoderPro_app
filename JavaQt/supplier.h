#ifndef SUPPLIER_H
#define SUPPLIER_H
template<class T>
class Supplier
{
public:
 Supplier(T t) {this->t = t;}
 T get()const {return t;}
private:
 T t;
};
#endif // SUPPLIER_H
