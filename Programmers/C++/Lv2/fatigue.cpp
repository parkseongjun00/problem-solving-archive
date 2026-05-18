#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Dungeon
{
    int index;
    int min;
    int req;
};

vector<Dungeon> init_dungeon_list(vector<vector<int>> dungeons);
int dfs(int k, const vector<Dungeon>& dungeon_list, vector<int>& visited_dungeon_indices, int& max);
bool is_visited(const vector<int>& visited_dungeon_indices, int target);

int solution(int k, vector<vector<int>> dungeons) 
{
    vector<int> visited_dungeon_indices;                            // 방문한 던전 인덱스
    vector<Dungeon> dungeon_list = init_dungeon_list(dungeons);     // 던전 구조체 리스트
    int answer = -1;
    return dfs(k, dungeon_list, visited_dungeon_indices, answer);
}

vector<Dungeon> init_dungeon_list(vector<vector<int>> dungeons)
{
    vector<Dungeon> dungeon_list;
    
    for (int i = 0; i < dungeons.size(); i++)
    {
        dungeon_list.push_back({i, dungeons[i][0], dungeons[i][1]});
    }
    
    return dungeon_list;
}

int dfs(int k, const vector<Dungeon>& dungeon_list, vector<int>& visited_dungeon_indices, int& max)
{
    for (int i = 0; i < dungeon_list.size(); i++)
    {
        const Dungeon& cur_dungeon = dungeon_list[i];
        
        // 이미 방문한 던전일 경우
        if (is_visited(visited_dungeon_indices, cur_dungeon.index))
        {
            continue;
        }
        
        // 던전 입장 조건 만족했을 경우
        if (cur_dungeon.min <= k)
        {
            visited_dungeon_indices.push_back(i);
            dfs(k - cur_dungeon.req, dungeon_list, visited_dungeon_indices, max);
            visited_dungeon_indices.pop_back(); // 이거 꼭 해줘야 한다!
        }
    }
    
    int cur_value = visited_dungeon_indices.size();
    max = max < cur_value ? cur_value : max;
    return max;
}

bool is_visited(const vector<int>& visited_indices, int target)
{
    return find(visited_indices.begin(), visited_indices.end(), target) != visited_indices.end();
}
