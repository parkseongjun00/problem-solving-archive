#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int DIA = 0;
const int IRON = 1;
const int STONE = 2;
const int DUR = 5;      // 곡괭이의 내구도

struct Sector
{
    int index;
    int score;
    vector<string> minerals;
};

int dig(int pick_index, vector<string>& minerals);
int get_fatigue(int pick_index, string mineral);
int get_sector_score(const vector<string>& sector);
bool compare_sector_by_score(const Sector& a, const Sector& b);

/// ---------------
/// 원래는 1차로 모든 곡괭이 사용에 대한 조합을 구하려고 했으나 너무 어려워서 실패.
/// 그래서 2차로 minerals를 5개 단위의 섹터로 구분하고, 점수를 매겨서, 높은 점수 섹터에 좋은 곡괭이 할당.
/// ---------------
int solution(
    vector<int> picks, 
    vector<string> minerals) 
{
    int answer = 0;
    vector<Sector> sectors;
    vector<string> cur_sector_minerals; 
    int possible_sector_count = 0;      // 총 곡괭이 수를 기준으로 처리할 수 있는 섹터 수
    int cur_sector_index = 0;           // sectors 초기화하는 과정에서의 현재 섹터 인덱스
    
    // possible_sector_count 초기화
    for (int i = 0; i < picks.size(); i++) { possible_sector_count += picks[i]; }
    
    // sectors 초기화, 조건문의 경우 ||가 아니고 &&여야 한다!
    for (int i = 0; i < minerals.size() && cur_sector_index < possible_sector_count; i++)
    {
        cur_sector_minerals.push_back(minerals[i]);
        
        // 괄호를 쳐야 우선순위가 올바르게 인식
        if ((i + 1) % 5 == 0 || i == minerals.size() - 1)
        {
            sectors.push_back({
                cur_sector_index++,
                get_sector_score(cur_sector_minerals),
                cur_sector_minerals
            });
 
            cur_sector_minerals.clear();
        }
    }
    
    //sector 정렬 (내림차순, 올림차순으로 하고 한 번 뒤집음)
    sort(sectors.begin(), sectors.end(), compare_sector_by_score);
    reverse(sectors.begin(), sectors.end());
    
    for (int i = 0; i < sectors.size(); i++)
    {
        int cur_pick_index = -1;
        
        if (picks[DIA] > 0)         { cur_pick_index = DIA; }
        else if (picks[IRON] > 0)   { cur_pick_index = IRON; }
        else                        { cur_pick_index = STONE; }
        
        picks[cur_pick_index]--;    // 한 번 사용한 곡괭이는 차감했어야 했는데 안 했다. 
        answer += dig(cur_pick_index, sectors[i].minerals);
    }
    
    
    return answer;
}

int dig(int pick_index, vector<string>& minerals)
{
    int total_fatigue = 0;      // 이 곡괭이에서 비롯된 총 피로도
    
    for (int i = 0; i < DUR; i++)
    {
        if (i == minerals.size())
        {
            break;
        }
        
        total_fatigue += get_fatigue(pick_index, minerals[i]);
    }
    
    return total_fatigue;
}

int get_fatigue(int pick_index, string mineral)
{
    switch (pick_index)
    {
        case DIA:
            return 1;
        case IRON:
            if (mineral == "diamond") return 5;
            return 1;
        case STONE:
            if (mineral == "diamond") return 25;
            if (mineral == "iron") return 5;
            return 1;
    }
}

int get_sector_score(const vector<string>& sector)
{
    int score = 0;
    
    for (int i = 0; i < sector.size(); i++)
    {
        // 근데 사실 점수 부여하는 기준이 이게 맞나 의문점이 들긴 함.
        if (sector[i] == "diamond") score += 25;
        else if (sector[i] == "iron") score += 5;
        else if (sector[i] == "stone") score += 1;
    }
    
    return score;
}

bool compare_sector_by_score(const Sector& a, const Sector& b)
{
    return a.score < b.score;
}
