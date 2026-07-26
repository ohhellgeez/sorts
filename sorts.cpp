#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

template <typename SortFunction>
void test_sort(SortFunction sf, const std::string& sort_name)
{
     std::vector<std::vector<int>> test_cases = {
          {},                             
          {1},                            
          {1, 2, 3, 4, 5},                
          {5, 4, 3, 2, 1},                
          {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, 
          {42, -5, 0, 100, -10, 8}        
     };

     std::mt19937 gen(42);
     std::uniform_int_distribution<int> dist(-1000, 1000);
     std::vector<int> random_large(1000);
     for (int& x : random_large) x = dist(gen);
     test_cases.push_back(random_large);

     bool all_passed = true;

     for (size_t i = 0; i < test_cases.size(); ++i)
     {
          std::vector<int> original = test_cases[i];
          
          std::vector<int> expected = original;
          std::sort(expected.begin(), expected.end());

          std::vector<int> actual = original;
          sf(actual);

          if (actual != expected)
          {
               std::cout << "[ОШИБКА] " << sort_name << " - Провалил тест #" << i + 1 << "\n";
               all_passed = false;
          }
     }

     if (all_passed)
     {
          std::cout << "[УСПЕХ] " << sort_name << " прошел все тесты!\n";
     }
}

void select_sort(std::vector<int>& v)
{
     if (v.empty()) return;
     for (size_t i = 0; i < v.size() - 1; ++i)
     {
          size_t min_idx = i;
          for (size_t j = i + 1; j < v.size(); ++j)
          {
               if (v[j] < v[min_idx])
               {
                    min_idx = j;
               }
          }
          std::swap(v[i], v[min_idx]);
     }
}

void insertion_sort(std::vector<int>& v)
{
     if (v.empty()) return;
     for (size_t i = 1; i < v.size(); ++i) 
     {
          int tmp = v[i];
          int j = i - 1; 
          while (j >= 0 && v[j] > tmp)
          {
               v[j + 1] = v[j];
               --j;
          }
          v[j + 1] = tmp; 
     }
}

namespace merge_srt
{

void merge(std::vector<int>& v, size_t lo, size_t mid, size_t hi)
{
     std::vector<int> tmp;
     tmp.reserve(hi - lo + 1);
     size_t i, j;
     i = lo;
     j = mid + 1;
     while (i <= mid && j <= hi )
     {
          if (v[i] < v[j])
          {
               tmp.push_back(v[i]);
               ++i;
          }
          else
          {
               tmp.push_back(v[j]);
               ++j;
          }
     }
     while (j <= hi)
     {
          tmp.push_back(v[j]);
          ++j;
     }
     while (i <= mid)
     {
          tmp.push_back(v[i]);
          ++i;
     }
     std::copy(tmp.begin(), tmp.end(), v.begin() + lo);

}

void r_sort(std::vector<int>& v, size_t lo, size_t hi)
{
     if (hi > lo)
     {
          size_t mid = (lo + hi) / 2;
          r_sort(v, lo, mid);
          r_sort(v, mid + 1, hi);
          merge(v, lo, mid, hi);
     }
}

void merge_sort(std::vector<int>& v)
{
     if (v.empty() || v.size() == 1) return;
     r_sort(v, 0, v.size() - 1);
}

}

namespace quick_sort
{

size_t partition(std::vector<int>& v, size_t lo, size_t hi)
{
     int pivot = v[lo];
     size_t left = lo + 1;
     size_t right = hi;
     while (true)
     {
          while (left <= right && v[left] < pivot)
          {
               ++left;
          }
          while (left <= right && v[right] > pivot)
          {
               --right;
          }
          if (left <= right)
          {
               std::swap(v[left], v[right]);
               ++left;
               --right;
          }
          else
          {
               break;
          }
     }
     std::swap(v[right], v[lo]);
     return right;
}

void qsort(std::vector<int>& vec, size_t lo, size_t hi)
{
     if (hi > lo)
     {
          size_t location = partition(vec, lo, hi);
          if (location > lo)
          {
               qsort(vec, lo, location - 1);
          }
          qsort(vec, location + 1, hi);
     }
}

void quick_sort(std::vector<int>& v)
{
     if (v.empty() || v.size() == 1) return;
     qsort(v, 0, v.size() - 1);
}

}

int main()
{
     test_sort(select_sort, "Selection Sort");
     test_sort(insertion_sort, "Insertion Sort");
     test_sort(merge_srt::merge_sort, "Merge Sort");
     test_sort(quick_sort::quick_sort, "Quick Sort");
     return 0;
}