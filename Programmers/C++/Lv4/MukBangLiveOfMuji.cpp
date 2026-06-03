#include <string>
#include <vector>
#include <algorithm>
#include <numeric> // vector<int> 내 모든 요소를 더하는데 필요

using namespace std;

struct Food
{
    int index;
    int time;
};

int solution(vector<int> food_times, long long k) 
{
    // 초기값을 0LL로 설정하여 합산 시 오버플로우 방지
    if (accumulate(food_times.begin(), food_times.end(), 0LL) <= k)
    {
        return -1;
    }
    
    vector<Food> foods;
    
    for (int i = 0; i < food_times.size(); i++)
    {
        foods.push_back({i + 1, food_times[i]});
    }
    
    // 시간이 적은 순으로 정렬
    sort(foods.begin(), foods.end(), [](const Food& a, const Food& b) 
         {
             return a.time < b.time;
         });
    
    // 주의: elapsed, previous, length는 반드시 long long이어야 함.
    // [이유] 음식 시간의 최댓값(1억) * 남은 음식 개수의 최댓값(20만) = 최대 20조(2 * 10^13).
    // C++의 int 최댓값은 약 21억이므로, int로 연산할 경우 곱셈 과정에서 오버플로우가 발생하여 쓰레기값이 들어갑니다.
    long long elapsed = 0;            // 지금까지 음식 먹는데 소모된 시간
    long long previous = 0;           // 지난 음식 하나 먹는데 소모된 시간
    long long length = foods.size();  // 남은 음식 개수
    int pointer = 0;            // 시간이 낮은 순대로 정렬하고, 이를 가리키는 포인터
    
    // 정확히 k초에 다 먹은 경우를 처리하기 위해 <= 로 변경
    while (elapsed + (foods[pointer].time - previous) * length <= k)
    {
        Food now = foods[pointer];
        
        elapsed += (now.time - previous) * length;
        previous = now.time;
        length -= 1;
        pointer += 1;
    }
    
    // 이제는 인덱스가 낮은 순으로 정렬
    sort(foods.begin() + pointer, foods.end(), [](const Food& a, const Food& b)
         {
             return a.index < b.index;
         });
    
    return foods[pointer + ((k - elapsed) % length)].index;
}
