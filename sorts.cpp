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

int main()
{
     test_sort(select_sort, "Selection Sort");
     return 0;
}