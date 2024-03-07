#ifndef TINYSTL_REVERSE_ITERATOR_H
#define TINYSTL_REVERSE_ITERATOR_H

#include "iterator.h"

namespace mystl {
    // 模板类：reverse_iterator
    // 代表反向迭代器，使前进为后退，后退为前进
    template <typename Iterator>
    class reverse_iterator {
    private:
        Iterator current;  // 记录对应的正向迭代器

    public:
        // 反向迭代器的五种相应类型
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;

        typedef Iterator                                                iterator_type;
        typedef reverse_iterator<Iterator>                              self;

    public:
        // 构造函数
        reverse_iterator() = default;
        explicit reverse_iterator(iterator_type i) :current(i) {}
        reverse_iterator(const self &rhs) :current(rhs.current) {}

    public:
        // 取出对应正向迭代器
        iterator_type base() const {
            return current;
        }

        // 重载操作符.由于反向迭代器物理位置和逻辑位置差一位，所以这里 --tmp;
        reference operator*() const {
            auto tmp = current;
            return *--tmp;
        }

        pointer operator->() const {
            return &(operator*());
        }

        self &operator++() {
            --current;
            return *this;
        }

        self operator++(int) {
            self tmp = *this;
            --current;
            return tmp;
        }

        self &operator--() {
            ++current;
            return *this;
        }

        self operator--(int) {
            self tmp = *this;
            ++current;
            return tmp;
        }

        self &operator+=(difference_type n) {
            current -= n;
            return *this;
        }
        self operator+(difference_type n) const {
            return self(current - n);
        }
        self &operator-=(difference_type n) {
            current += n;
            return *this;
        }
        self operator-(difference_type n) const {
            return self(current + n);
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }
    };

    // 重载 operator-
    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator- (const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
        return rhs.base() - lhs.base();
    }

    // 重载比较操作符
    template <typename Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs,
                   const reverse_iterator<Iterator>& rhs) {
        return rhs.base() < lhs.base();
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) {
        return !(lhs == rhs);
    }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs,
                   const reverse_iterator<Iterator> &rhs) {
        return rhs < lhs;
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) {
        return !(rhs < lhs);
    }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator> &rhs) {
        return !(lhs < rhs);
    }

};  // mystl;
#endif //TINYSTL_REVERSE_ITERATOR_H
