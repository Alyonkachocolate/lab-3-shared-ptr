// Copyright [2020] <Alyona Dorodnyaya>

#include <gtest/gtest.h>

#include "SharedPtr.h"

struct Item {
  bool &create;
  int value;
  ~Item() { create = false; }
};

TEST(SharedPtr, ConstructorEmpty) {
  SharedPtr<int> item;
  EXPECT_FALSE(item);
  EXPECT_EQ(item.use_count(), 0);
}

TEST(SharedPtr, ConstructorParametr) {
  auto *str = new std::string;
  SharedPtr<std::string> item(str);
  EXPECT_TRUE(item);
  EXPECT_EQ(item.use_count(), 1);
}

TEST(SharedPtr, ConstructorCopy) {
  bool cr = true;  // объект не создан
  {
    SharedPtr<Item> item(new Item{cr, 10});
    EXPECT_TRUE(cr);  // объект создан
    EXPECT_EQ(item.use_count(), 1);
    EXPECT_EQ(item->value, 10);

    {
      SharedPtr<Item> item1(item);
      EXPECT_TRUE(cr);  // объект всё еще создан
      EXPECT_EQ(item1.use_count(), 2);
      EXPECT_EQ(item1->value, 10);
      EXPECT_EQ(item.use_count(), 2);
      EXPECT_EQ(item->value, 10);
    }
  }
  EXPECT_FALSE(cr);  // объект удалён
}

TEST(SharedPtr, ConstructorMove) {
  bool cr = true;  // объект не создан
  {
    SharedPtr<Item> item(new Item{cr, 20});
    EXPECT_TRUE(cr);  // объект создан
    EXPECT_EQ(item.use_count(), 1);
    EXPECT_EQ(item->value, 20);

    SharedPtr<Item> item1(std::move(item));
    EXPECT_TRUE(cr);  // объект всё еще создан
    EXPECT_EQ(item1.use_count(), 1);
    EXPECT_EQ(item1->value, 20);
    EXPECT_FALSE(item);
    EXPECT_EQ(item.use_count(), 0);
  }
  EXPECT_FALSE(cr);  // объект удалён
}

TEST(SharedPtr, Copy) {
  bool cr = true;  // объект не создан
  {
    SharedPtr<Item> item(new Item{cr, 30});
    EXPECT_TRUE(cr);  // объект создан
    EXPECT_EQ(item.use_count(), 1);
    EXPECT_EQ(item->value, 30);

    {
      SharedPtr<Item> item1;
      item1 = item;
      EXPECT_TRUE(cr);  // объект всё еще создан
      EXPECT_EQ(item1.use_count(), 2);
      EXPECT_EQ(item1->value, 30);
      EXPECT_EQ(item.use_count(), 2);
      EXPECT_EQ(item->value, 30);
    }
  }
  EXPECT_FALSE(cr);  // объект удалён
}

TEST(SharedPtr, Move) {
  bool cr = true;  // объект не создан
  {
    SharedPtr<Item> item(new Item{cr, 40});
    EXPECT_TRUE(cr);  // объект создан
    EXPECT_EQ(item.use_count(), 1);
    EXPECT_EQ(item->value, 40);

    SharedPtr<Item> item1;
    item1 = std::move(item);
    EXPECT_TRUE(cr);  // объект всё еще создан
    EXPECT_EQ(item1.use_count(), 1);
    EXPECT_EQ(item1->value, 40);
    EXPECT_FALSE(item);
    EXPECT_EQ(item.use_count(), 0);
  }
  EXPECT_FALSE(cr);  // объект удалён
}

TEST(SharedPtr, Bool) {
  SharedPtr<int> item;
  EXPECT_FALSE(item);
  auto *x = new int;
  SharedPtr<int> item1(x);
  EXPECT_TRUE(item1);
}

TEST(SharedPtr, Operator_1) {
  auto *str = new std::string("Operator *");
  SharedPtr<std::string> item(str);
  EXPECT_EQ(*item, *str);
}

TEST(SharedPtr, Operator_2) {
  auto *str = new std::string("Operator ->");
  SharedPtr<std::string> item(str);
  EXPECT_EQ(item->at(0), 'O');
}

TEST(SharedPtr, Get) {
  auto *str = new std::string("Get");
  SharedPtr<std::string> item(str);
  EXPECT_EQ(item.get()->at(0), 'G');
}

TEST(SharedPtr, Reset) {
  auto *str = new std::string;
  SharedPtr<std::string> item(str);
  EXPECT_TRUE(item);
  EXPECT_EQ(item.use_count(), 1);

  item.reset();

  EXPECT_FALSE(item);
  EXPECT_EQ(item.use_count(), 0);
}

TEST(SharedPtr, ResetParametr) {
  auto *str = new std::string("First");
  SharedPtr<std::string> item(str);
  EXPECT_TRUE(item);
  EXPECT_EQ(*item.get(), "First");

  item.reset(new std::string("Second"));

  EXPECT_TRUE(item);
  EXPECT_EQ(*item.get(), "Second");
}

TEST(SharedPtr, Swap) {
  auto *str1 = new std::string("X");
  auto *str2 = new std::string("Y");
  SharedPtr<std::string> item1(str1);
  SharedPtr<std::string> item2(str2);
  EXPECT_EQ(*item1.get(), "X");
  EXPECT_EQ(*item2.get(), "Y");

  item1.swap(item1);
  EXPECT_EQ(*item1.get(), "X");
  EXPECT_EQ(*item2.get(), "Y");

  item1.swap(item2);
  EXPECT_EQ(*item1.get(), "Y");
  EXPECT_EQ(*item2.get(), "X");
}