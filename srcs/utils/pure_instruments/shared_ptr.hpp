#pragma once


namespace ft {

  template<typename t_val>
  class shared_ptr {
  public:
    shared_ptr() throw():
            value_(nullptr) {
      memory_();
      *count_ = 1; };

    shared_ptr(t_val *value) throw():
            value_(value) {
      memory_();
      *count_ = 1; };

    shared_ptr(const shared_ptr &ref) throw() {
      copy(ref);
    };

    shared_ptr &operator=(const shared_ptr &ref) throw() {
      delete_value();
      copy(ref);
      return *this;
    }

    virtual ~shared_ptr() throw() {
      --(*count_);
      if (*count_ == 0) {
        delete value_;
        delete count_;
      }
    };

    bool is_val() throw() {
      if (value_)
        return true;
      return false;
    }
    t_val &operator*() throw() { return *value_; }
    const t_val &operator*() const throw() { return *value_; }
    t_val *operator->() throw() { return value_; }
    const t_val *operator->() const throw() { return value_; }
    t_val *get() throw() { return value_; }
    const t_val *get() const throw() { return value_; }

  private:
    void copy(const shared_ptr &ref) throw() {
      value_ = ref.value_;
      count_ = ref.count_;
      ++(*(ref.count_));
    }

    void delete_value() throw() {
       --(*count_);
        if (*count_ == 0) {
          delete count_;
          delete value_;
        }
    }

    void memory_() {
        count_ = new size_t;
    }
    t_val *value_;
    size_t *count_;
  };

}
