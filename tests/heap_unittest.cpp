// Copyright 2006-2015 Tobias Sargeant (tobias.sargeant@gmail.com).
//
// This file is part of the Carve CSG Library (http://carve-csg.com/)
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <gtest/gtest.h>

#if defined(HAVE_CONFIG_H)
#include <carve_config.h>
#endif

#include <carve/carve.hpp>
#include <carve/heap.hpp>

#include <map>

struct record_t {
  std::map<int, size_t>& pos;
  record_t(std::map<int, size_t>& _pos) : pos(_pos) {}
  void operator()(int x, size_t y) { pos[x] = y; }
};

void test_notify(std::vector<int> heap) {
  std::map<int, size_t> pos;
  carve::heap::make_heap(heap.begin(), heap.end(), std::less<int>(),
                         record_t(pos));

  for (std::map<int, size_t>::iterator i = pos.begin(); i != pos.end(); ++i) {
    ASSERT_EQ(heap[(*i).second], (*i).first);
  }

  ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.end(), std::less<int>()),
            true);

  for (size_t l = heap.size(); l > 0; --l) {
    carve::heap::pop_heap(heap.begin(), heap.begin() + l, std::less<int>(),
                          record_t(pos));
    if (l) {
      ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.begin() + l - 1), true);
    }
    for (std::map<int, size_t>::iterator i = pos.begin(); i != pos.end(); ++i) {
      ASSERT_EQ(heap[(*i).second], (*i).first);
    }
  }
  ASSERT_EQ(carve::is_sorted(heap.begin(), heap.end()), true);
}

void test_cmp(std::vector<int> heap) {
  carve::heap::make_heap(heap.begin(), heap.end(), std::greater<int>());

  ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.end(), std::greater<int>()),
            true);

  for (size_t l = heap.size(); l > 0; --l) {
    carve::heap::pop_heap(heap.begin(), heap.begin() + l, std::greater<int>());
    if (l) {
      ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.begin() + l - 1,
                                     std::greater<int>()),
                true);
    }
  }
  ASSERT_EQ(carve::is_sorted(heap.begin(), heap.end(), std::greater<int>()),
            true);
}

void test_heap(std::vector<int> heap) {
  carve::heap::make_heap(heap.begin(), heap.end());

  ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.end()), true);

  for (size_t l = heap.size(); l > 0; --l) {
    carve::heap::pop_heap(heap.begin(), heap.begin() + l);
    if (l) {
      ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.begin() + l - 1), true);
    }
  }
  ASSERT_EQ(carve::is_sorted(heap.begin(), heap.end()), true);
}

void test_push(std::vector<int> heap) {
  for (size_t i = 2; i < heap.size(); ++i) {
    carve::heap::push_heap(heap.begin(), heap.begin() + i);
    ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.begin() + i), true);
  }

  for (size_t l = heap.size(); l > 0; --l) {
    carve::heap::pop_heap(heap.begin(), heap.begin() + l);
    if (l) {
      ASSERT_EQ(carve::heap::is_heap(heap.begin(), heap.begin() + l - 1), true);
    }
  }
  ASSERT_EQ(carve::is_sorted(heap.begin(), heap.end()), true);
}

void test_sort(std::vector<int> heap) {
  carve::heap::make_heap(heap.begin(), heap.end());
  carve::heap::sort_heap(heap.begin(), heap.end());
  ASSERT_EQ(carve::is_sorted(heap.begin(), heap.end()), true);
}

TEST(HeapTest, MakeHeapNotify) {
  int data[] = {14, 9, 16, 1,  8,  2, 10, 18, 3,  11,
                15, 4, 6,  19, 17, 5, 13, 7,  12, 0};
  std::vector<int> heap(data, data + sizeof(data) / sizeof(data[0]));

  test_notify(heap);
}

TEST(HeapTest, MakeHeapGt) {
  int data[] = {14, 9, 16, 1,  8,  2, 10, 18, 3,  11,
                15, 4, 6,  19, 17, 5, 13, 7,  12, 0};
  std::vector<int> heap(data, data + sizeof(data) / sizeof(data[0]));

  test_cmp(heap);
}

TEST(HeapTest, MakeHeap) {
  int data[] = {14, 9, 16, 1,  8,  2, 10, 18, 3,  11,
                15, 4, 6,  19, 17, 5, 13, 7,  12, 0};
  std::vector<int> heap(data, data + sizeof(data) / sizeof(data[0]));

  test_heap(heap);
}

TEST(HeapTest, Push) {
  int data[] = {14, 9, 16, 1,  8,  2, 10, 18, 3,  11,
                15, 4, 6,  19, 17, 5, 13, 7,  12, 0};
  std::vector<int> heap(data, data + sizeof(data) / sizeof(data[0]));

  test_push(heap);
}

TEST(HeapTest, Sort) {
  int data[] = {14, 9, 16, 1,  8,  2, 10, 18, 3,  11,
                15, 4, 6,  19, 17, 5, 13, 7,  12, 0};
  std::vector<int> heap(data, data + sizeof(data) / sizeof(data[0]));

  test_sort(heap);
}
