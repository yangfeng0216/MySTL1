#ifndef TINYSTL_HEAP_ALGO_H
#define TINYSTL_HEAP_ALGO_H
// 与heap相关的算法：push_heap, pop_heap, sort_heap, make_heap
// max-heap: 由数组实现
// comp: less<>()
#include "iterator.h"

namespace mystl {
    /*****************************************************************************************/
    // push_heap
    // 该函数接受两个迭代器，表示一个 heap 容器的首尾，并且新元素已经插入到底部容器的最尾端，调整 heap
    /*****************************************************************************************/
    template <typename RandomIter, typename Distance, typename T>
    void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value) {
        auto parent = (holeIndex - 1) / 2;  // 取父节点
        while (holeIndex > topIndex && *(first + parent) < value) {
            // 当尚未到达顶端，且父节点小于新插入节点值，不符合max-heap
            *(first + holeIndex) = *(first + parent);  // 令当前索引值为父节点值
            holeIndex = parent;  // 进行调整
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;  // 插入新节点值
    }

    template <typename RandomIter, typename Distance>
    void push_heap_d(RandomIter first, RandomIter last, Distance*) {
        // 根据隐式表达法的结构特性，last-1表示新插入节点。
        mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
    }

    // 新插入元素应该已置于底部容器的最尾端
    template <typename RandomIter>
    void push_heap(RandomIter first, RandomIter last) {
        mystl::push_heap_d(first, last, distance_type(first));
    }

    template <typename RandomIter, typename Distance, typename T, typename Compared>
    void push_heap_aux(RandomIter first, Distance holeIndex,
                       Distance topIndex, T value, Compared comp) {
        auto parent = (holeIndex - 1) / 2;  // 取父节点
        while (holeIndex > topIndex && comp(*(first + parent), value)) {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <typename RandomIter, typename Distance, typename Compared>
    void push_heap_d(RandomIter first, RandomIter last, Distance *, Compared comp) {
        mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1), comp);
    }

    // 新插入元素应该已置于底部容器的最尾端
    template <typename RandomIter, typename Compared>
    void push_heap(RandomIter first, RandomIter last, Compared comp) {
        mystl::push_heap_d(first, last, distance_type(first), comp);
    }

    /*****************************************************************************************/
    // pop_heap
    // 该函数接受两个迭代器，表示 heap 容器的首尾，将 heap 的根节点取出放到容器尾部，调整 heap
    /*****************************************************************************************/
    template <typename RandomIter, typename T, typename Distance>
    void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value) {
        // 先进行下溯过程
        auto topIndex = holeIndex;
        auto rchild = 2 * holeIndex + 2;  // 右子结点索引
        while (rchild < len) {  // 未超出索引
            if (*(first + rchild) < *(first + (rchild - 1))) {  // 对比左子节点与右子节点
                --rchild;  // 左子节点索引
            }
            // 令较大值为洞值，再令洞号下移至较大子节点处
            *(first + holeIndex) = *(first + rchild);
            holeIndex = rchild;
            rchild = 2 * rchild + 2;  // 找出新的右节点
        }
        if (rchild == len) {  // 没有右子节点, 但存在左子节点
            *(first + holeIndex) = *(first + (rchild - 1));
            holeIndex = rchild - 1;
        }

        // 再执行一次上溯过程
        // 等同于：*（first + holeIndex) = value;
        mystl::push_heap_aux(first, holeIndex, topIndex, value);
    }

    // 先将首值调至尾节点，然后调整[first, last - 1)使之重新成为一个 max-heap
    template <typename RandomIter, typename T, typename Distance>
    void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result,
                       T value, Distance *) {
        *result = *first;
        mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
    }

    // 先调整，后删除
    template <typename RandomIter>
    void pop_heap(RandomIter first, RandomIter last) {
        mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
    }

    template <typename RandomIter, typename T, typename Distance, typename Compared>
    void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value, Compared comp) {
        // 先进行下溯过程
        auto topIndex = holeIndex;
        auto rchild = 2 * holeIndex + 2;  // 右子结点索引
        while (rchild < len) {  // 未超出索引
            if (comp(*(first + rchild), *(first + rchild - 1))) {  // 对比左子节点与右子节点
                --rchild;  // 左子节点索引
            }
            *(first + holeIndex) = *(first + rchild);
            holeIndex = rchild;
            rchild = 2 * rchild + 2;
        }
        if (rchild == len) {  // 没有右子节点, 但存在左子节点
            *(first + holeIndex) = *(first + rchild - 1);
            holeIndex = rchild - 1;
        }

        // 再执行一次上溯过程
        mystl::push_heap_aux(first, holeIndex, topIndex, value, comp);
    }

    // 先将首值调至尾节点，然后调整[first, last - 1)使之重新成为一个 max-heap
    template <typename RandomIter, typename T, typename Distance, typename Compared>
    void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result,
                       T value, Distance *, Compared comp) {
        *result = *first;
        mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
    }

    // 先调整，后删除
    template <typename RandomIter, typename Compared>
    void pop_heap(RandomIter first, RandomIter last, Compared comp) {
        mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first), comp);
    }

    /*****************************************************************************************/
    // sort_heap
    // 该函数接受两个迭代器，表示 heap 容器的首尾，不断执行 pop_heap 操作，直到首尾最多相差1
    /*****************************************************************************************/
    template <typename RandomIter>
    void sort_heap(RandomIter first, RandomIter last) {
        // 大顶堆。每执行一次pop_heap, 最大的元素都被放到尾部，直到容器最多只有一个元素
        while (last - first > 1) {
            mystl::pop_heap(first, last--);
        }
    }

    template <typename RandomIter, typename Compared>
    void sort_heap(RandomIter first, RandomIter last, Compared comp) {
        // 大顶堆。每执行一次pop_heap, 最大的元素都被放到尾部，知道容器最多只有一个元素
        while (last - first > 1) {
            mystl::pop_heap(first, last--, comp);
        }
    }

    /*****************************************************************************************/
    // make_heap
    // 该函数接受两个迭代器，表示 heap 容器的首尾，把容器内的数据变为一个 heap
    /*****************************************************************************************/
    template <typename RandomIter, typename Distance>
    void make_heap_aux(RandomIter first, RandomIter last, Distance *) {
        if (last - first < 2) {
            return ;
        }
        auto len = last - first;
        auto holeIndex = (len - 2) / 2;  // 从最后一个节点的父节点开始
        while (true) {
            // 重排以 holeIndex 为首的子树
            mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
            if(holeIndex == 0) {
                return ;  // 排完根节点，就结束
            }
            --holeIndex;  // 头部向前的一个节点
        }
    }

    template <typename RandomIter>
    void make_heap(RandomIter first, RandomIter last) {
        mystl::make_heap_aux(first, last, distance_type(first));
    }

    template <typename RandomIter, typename Distance, typename Compared>
    void make_heap_aux(RandomIter first, RandomIter last, Distance *, Compared comp) {
        if (last - first < 2) {
            return ;
        }
        auto len = last - first;
        auto holeIndex = (len - 2) / 2;  // 从最后一个节点的父节点开始
        while (true) {
            // 重排以 holeIndex 为首的子树
            mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
            if(holeIndex == 0) {
                return ;
            }
            --holeIndex;
        }

    }

    template <typename RandomIter, typename Compared>
    void make_heap(RandomIter first, RandomIter last, Compared comp) {
        mystl::make_heap_aux(first, last, distance_type(first), comp);
    }
}  // namespace mystl;
#endif //TINYSTL_HEAP_ALGO_H
