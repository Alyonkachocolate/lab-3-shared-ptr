// Copyright [2020] <Alyona Dorodnyaya>

#ifndef LAB_3_SHARED_PTR_APP_SHAREDPTR_H
#define LAB_3_SHARED_PTR_APP_SHAREDPTR_H

#include <atomic>
#include <iostream>

template <typename T>
class SharedPtr {
 private:
  T* ptr_;
  std::atomic_uint* counter_;

 public:
  SharedPtr();
  explicit SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r) noexcept;
  ~SharedPtr();

  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset() noexcept;
  void reset(T* ptr);
  void swap(SharedPtr& r) noexcept;
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  [[nodiscard]] auto use_count() const -> size_t;
};

template <typename T>
SharedPtr<T>::SharedPtr() : ptr_(nullptr), counter_(nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
  ptr_ = ptr;
  counter_ = new std::atomic_uint;
  (*counter_) = 1;
}

// конструктор копирования
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r) {
  ptr_ = r.ptr_;
  counter_ = r.counter_;
  (*counter_)++;
}

// конструктор перемещения
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r) noexcept {
  ptr_ = r.ptr_;
  counter_ = r.counter_;
  r.ptr_ = nullptr;
  r.counter_ = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (ptr_ != nullptr) {
    (*counter_)--;
    if (*counter_ == 0) {
      delete ptr_;
      delete counter_;
    }
  }
}

// оператор присваивания копированием
template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr& {
  if (&r == this) return *this;

  // проверяем объект, которым владеет сейчас указатель
  if (ptr_ != nullptr) {
    (*counter_)--;
    if (*counter_ == 0) {
      delete ptr_;
      delete counter_;
    }
  }
  ptr_ = r.ptr_;
  counter_ = r.counter_;
  (*counter_)++;
  return *this;
}

// оператор присваивания перемещением
template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) noexcept -> SharedPtr& {
  if (&r == this) return *this;

  // проверяем объект, которым владеет сейчас указатель
  if (ptr_ != nullptr) {
    (*counter_)--;
    if (*counter_ == 0) {
      delete ptr_;
      delete counter_;
    }
  }
  ptr_ = r.ptr_;
  counter_ = r.counter_;
  r.ptr_ = nullptr;
  r.counter_ = nullptr;
  return *this;
}

// проверяет, указывает ли указатель на объект
template <typename T>
SharedPtr<T>::operator bool() const {
  return (ptr_ != nullptr);
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
  return *ptr_;
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
  return ptr_;
}
template <typename T>
auto SharedPtr<T>::get() -> T* {
  return ptr_;
}

template <typename T>
void SharedPtr<T>::reset() noexcept {
  (*counter_)--;
  if (*counter_ == 0) {
    delete ptr_;
    delete counter_;
  }
  ptr_ = nullptr;
  counter_ = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T* ptr) {
  (*counter_)--;
  if (*counter_ == 0) {
    delete ptr_;
    delete counter_;
  }
  ptr_ = ptr;
  counter_ = new std::atomic_uint;
  *counter_ = 1;
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& r) noexcept {
  if (&r != this) {
    std::swap(ptr_, r.ptr_);
    std::swap(counter_, r.counter_);
  }
}

// возвращает количество ссфлающихся на SharedPtr объектов
template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  if (ptr_ != nullptr) return (*counter_);
  return 0;
}

#endif  // LAB_3_SHARED_PTR_APP_SHAREDPTR_H
