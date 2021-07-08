//
// Created by Gilberto Dougal on 7/8/21.
//
#pragma once

namespace ft {

template<typename T>
struct optional {

  bool is_val() const { return is_val_; }

  const T &get_or(const T &alt_ret) const {
    if (is_val_)
      return value_;
    return alt_ret;
  };

  const T &get() const {
    return value_;
  };

  void set_value(const T& value) {
    value_ = value;
    is_val_ = true;
  }
  optional(): is_val_(false) {};
  explicit optional(const T& value): is_val_(true), value_(value) {}
  optional(const optional<T>& ref) = default;
  optional& operator=(const optional<T>& ref)  = default;
  virtual ~optional() {}
private:
  bool	is_val_;
  T			value_;
};

}
