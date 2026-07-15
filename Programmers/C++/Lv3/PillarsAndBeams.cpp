#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool find_in(const vector<vector<int>>& building, const vector<int>& target);
bool is_valid(const vector<vector<int>>& building, int x, int y, int a);
bool is_valid_in_delete(const vector<vector<int>>& building, int x, int y, int a, int n);

const int VERTICAL = 0;
const int HORIZONTAL = 1;
const int DELETE = 0;
const int CREATE = 1;

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) 
{
    vector<vector<int>> answer;
    
    for (int i = 0; i < build_frame.size(); i++)
    {
        // get value from data
        vector<int>& now = build_frame[i];
        int x = now[0];
        int y = now[1];
        int a = now[2];
        int b = now[3];
      
        if (b == CREATE)
        {
            if (is_valid(answer, x, y, a))
            {
                answer.push_back({x, y, a});
            }
        }
        else if (b == DELETE)
        {
            // it's okay to skip checking position validation
            // delete commands guaranteed to target non-empty position
            answer.erase(find(answer.begin(), answer.end(), vector<int>{x, y, a}));
            
            if (!is_valid_in_delete(answer, x, y, a, n))
            {
                answer.push_back({x, y, a});
            }
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}

bool find_in(const vector<vector<int>>& building, const vector<int>& target)
{
    return find(building.begin(), building.end(), target) != building.end();
}

bool is_valid(const vector<vector<int>>& building, int x, int y, int a)
{
    if (a == VERTICAL)
    {
        if (y == 0) return true;
        if (find_in(building, {x, y-1, VERTICAL})) return true;
        if (find_in(building, {x-1, y, HORIZONTAL})) return true;
        if (find_in(building, {x, y, HORIZONTAL})) return true;
        return false;
    }
    
    if (a == HORIZONTAL)
    {
        // 1. trial and error
        // read problem conditions wrongly
        if (y == 0) return false;
        bool hasLeftVertical = find_in(building, {x-1, y, HORIZONTAL});
        bool hasRightVertical = find_in(building, {x+1, y, HORIZONTAL});
        if (hasLeftVertical && hasRightVertical) return true;
        if (find_in(building, {x, y-1, VERTICAL})) return true;
        if (find_in(building, {x+1, y-1, VERTICAL})) return true; 
        return false;
    }
    
    return false;
}

bool is_valid_in_delete(const vector<vector<int>>& building, int x, int y, int a, int n)
{
    vector<vector<int>> cand;
    
    if (a == VERTICAL)
    {
        cand.push_back({x, y+1, VERTICAL});
        cand.push_back({x-1, y+1, HORIZONTAL});
        cand.push_back({x, y+1, HORIZONTAL});
    }
    if (a == HORIZONTAL)
    {
        cand.push_back({x, y, VERTICAL});
        cand.push_back({x+1, y, VERTICAL});
        cand.push_back({x-1, y, HORIZONTAL});
        cand.push_back({x+1, y, HORIZONTAL});
    }
    
    for (int i = 0; i < cand.size(); i++)
    {
        const vector<int>& now = cand[i];
        
        // if cand itself not valid, skip
        if (!find_in(building, now)) continue;
        
        if (!is_valid(building, now[0], now[1], now[2])) return false;
    }
    
    return true;
}
