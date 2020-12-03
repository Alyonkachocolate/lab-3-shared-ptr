//// Copyright [2020] <Alyona Dorodnyaya>
//
//#include "SharedPtr.h"
//
//class Item {
// private:
//  int i = 0;
//
// public:
//  explicit Item(int j) : i(j) {
//    std::cout << "Constructor <Item>" << std::endl;
//  }
//
//  ~Item() { std::cout << "Destructor <Item>" << std::endl; }
//
//  void print() const { std::cout << "It is Item. i = " << i << std::endl; }
//};
//
//int main() {
//  Item *item = new Item(1);
//  SharedPtr<Item> item1(item);
//  SharedPtr<Item> item2(item1);
//  SharedPtr<Item> item3(item2);
//  auto a = item3.get();
//  a->print();
//
//  std::cout << "Function use_count() before reset() in item2 = "
//            << item2.use_count() << std::endl;
//  item3.reset();
//  std::cout << "Function use_count() after reset() in item3 = "
//            << item3.use_count() << std::endl;
//
//  if (item2)
//    std::cout << "Bool before reset(): true" << std::endl;
//  else
//    std::cout << "Bool before reset(): false" << std::endl;
//  item2.reset();
//  if (item2)
//    std::cout << "Bool after reset(): true" << std::endl;
//  else
//    std::cout << "Bool after reset(): false" << std::endl;
//
//  SharedPtr<Item> item5(new Item(4));
//  item5->print();
//
//  return 0;
//}
