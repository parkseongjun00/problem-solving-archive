#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 풀이 방법에 잘못 접근하면 치명적이다.

// 방법 1. 취약점 간 거리를 모두 파악
// 1. 각 취약점마다 인덱스를 붙이기
// 2. 각 취약점 간 거리를 모두 파악 (시계 방향인지, 반시계 방향인지 결정 근거는 뭐가 더 짧은지)

// 방법 2. dist[i]가 긴 놈을 찾아서 1명씩 보내보기
// 1. n명으로는 안 되어서, n+1명을 시도해봐야 할 때, 그 전까지 애들은 최적이어야 함. 
// 2. 그러니까, 모두가 다 각자 자신이 커버할 수 있는 최대한 넓은 범위를 커버해야 함. → 근데 이게 불가능.

// 방법 3. (Claude의 도움을 받음) 긴 거리를 파악할 수 있는 놈부터 보내는 건 올바른 접근법이 아니었다.

const int MAX = 9; // dist의 길이는 1 이상 8 이하이므로, 정답의 최대값은 8이다. 따라서 실패 시 9를 유도.

void get_cases(
    const vector<int>& source,
    const vector<int>& indices, 
    vector<int> current_case, 
    vector<vector<int>>& result);

void inspect(
    const vector<int>& weak,
    const vector<int>& dist,
    int n,
    int weak_idx,
    int dist_idx,
    int& result);

int get_last_checked_weak_idx(
    const vector<int>& weak,
    int n, 
    int dist, 
    int start_weak_idx);

int solution(int n, vector<int> weak, vector<int> dist) 
{
    int answer = MAX;
    vector<int> dist_indices;
    vector<vector<int>> dist_cases;
    
    //indices 초기화
    //dist의 중복 요소 허용을 간과했다. 그래서 값 기반 → 인덱스 기반으로 스위칭
    for (int i = 0; i < dist.size(); i++) { dist_indices.push_back(i); }

    // 모든 dist 순열 구하기
    get_cases(dist, dist_indices, vector<int>{}, dist_cases);
    
    // 모든 순열에 대해서 검사
    for (int i = 0; i < dist_cases.size(); i++)
    {   
        for (int k = 0; k < weak.size(); k++)
        {
            int temp = weak[0];
            weak.erase(weak.begin());
            weak.push_back(temp);
            
            inspect(weak, dist_cases[i], n, 0, 0, answer);
        }
    }
    
    // 모든 사람을 다 써도 전체 파악이 불가능할 때
    return MAX <= answer ? -1 : answer;
}

// 모든 순열을 구하는 함수
void get_cases(
    const vector<int>& source,
    const vector<int>& indices, 
    vector<int> current_case, 
    vector<vector<int>>& result)
{
    if (current_case.size() == indices.size())
    {
        for (int i = 0; i < current_case.size(); i++)
        {
            current_case[i] = source[current_case[i]];
        }
        
        result.push_back(current_case);
    }
    else
    {
        for (int i = 0; i < indices.size(); i++)
        {
            int now = indices[i];
            
            // 해당 인덱스가 이미 있을 경우
            if (find(current_case.begin(), current_case.end(), now) != current_case.end())
            {
                continue;
            }
            
            current_case.push_back(now);
            get_cases(source, indices, current_case, result);
            current_case.erase(current_case.end() - 1);
        }
    }
}

void inspect(
    const vector<int>& weak,
    const vector<int>& dist,
    int n,
    int weak_idx,
    int dist_idx,
    int& result)
{
    //weak_idx는 "아직 체크되지 않은 것 중 제일 앞선 인덱스"를 의미한다.
    if (weak_idx == weak.size())
    {
        if (dist_idx < result)
        {
            result = dist_idx;
        }
    }
    else if (dist_idx < dist.size())
    {
        int last_checked_weak_idx = get_last_checked_weak_idx(weak, n, dist[dist_idx], weak_idx);
        inspect(weak, dist, n, last_checked_weak_idx + 1, dist_idx + 1, result);
    }
}

int get_last_checked_weak_idx(
    const vector<int>& weak,
    int n, 
    int dist, 
    int start_weak_idx)
{
    int last_checked_weak_idx = start_weak_idx;
    int current = weak[start_weak_idx]; // 원 위의 실제 점
    
    for (int i = 0; i < dist; i++)
    {  
        // 혹시 현재 모든 취약점을 다 파악했다면
        if (last_checked_weak_idx == weak.size() - 1)
        {
            return last_checked_weak_idx;
        }
        
        //한 칸씩 전진
        current = (current + 1) % n;
        
        if (weak[last_checked_weak_idx + 1] == current)
        {
            last_checked_weak_idx += 1;
        }
        
        // 만약에 한바퀴 돌았으면
        if (((current + 1) % n) == weak[start_weak_idx])
        {
            break;
        }
    }
    
    return last_checked_weak_idx;
}
