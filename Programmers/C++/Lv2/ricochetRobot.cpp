#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm> 
#include <utility>      // pair 자료구조를 사용하기 위해 필요.

using namespace std;

struct Pos
{
    int x = -1;
    int y = -1;
    
    bool operator==(const Pos& other) const 
    {
        return x == other.x && y == other.y;
    }
    
    Pos operator+(const Pos& other) const
    {
        return { x + other.x, y + other.y };
    }
    
    Pos operator+(const vector<int>& other) const
    {
        return { x + other[0], y + other[1] };
    }
    
    bool is_null() const
    {
        return x == -1 && y == -1;
    }
};

bool is_visited_pos(vector<vector<bool>>& visited, Pos pos)
{
    return visited[pos.y][pos.x] == true;
}

bool is_valid_pos(const vector<string>& board, vector<vector<bool>>& visited, Pos pos)
{
    return 
        pos.x < board[0].size() && 0 <= pos.x
        && pos.y < board.size() && 0 <= pos.y
        && board[pos.y][pos.x] == '.' 
        && !is_visited_pos(visited, pos);
}

bool is_valid_pos(const vector<string>& board, Pos pos)
{
    return 
        pos.x < board[0].size() && 0 <= pos.x
        && pos.y < board.size() && 0 <= pos.y
        && board[pos.y][pos.x] != 'D';
}

const int TOTAL_DIRECTION = 4;

int solution(vector<string> board) 
{
    int count = -1;   
    queue<pair<Pos, int>> queue;
    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
    vector<vector<int>> directions;
    Pos cur_pos;
    
    // directions 초기화
    directions.push_back({ 0, -1 });
    directions.push_back({ 0, 1 });
    directions.push_back({ -1, 0 });
    directions.push_back({ 1, 0 });
    
    // 시작 위치 찾기
    for (int i = 0; i < board.size(); i++)
    {
        for (int k = 0; k < board[i].length(); k++)
        {
            if (board[i][k] == 'R')
            {
                queue.push({{ k, i }, 0});
                break;
            }
        }
    }
    
    // 도착했거나 더 이상 할 수 있는 선택지가 없을 때까지 반복
    while (queue.size() != 0)
    {
        // 큐에서 하나 뽑아서 방문 처리
        cur_pos = queue.front().first;
        int cost = queue.front().second;
        queue.pop();
        visited[cur_pos.y][cur_pos.x] = true;
        
        // 목적지에 도착
        if (board[cur_pos.y][cur_pos.x] == 'G')
        {
            return cost;
        }
        
        // 현재 위치에서 상하좌우 별 갈 수 있는 다음 위치 파악
        for (int i = 0; i < TOTAL_DIRECTION; i++)
        {
            Pos next_pos = cur_pos;
            
            while (is_valid_pos(board, next_pos + directions[i]))
            {
                next_pos = next_pos + directions[i];
            }
            
            if (!is_visited_pos(visited, next_pos))
            {
                queue.push({next_pos, cost + 1});
            }
        }
    }
    
    return -1;
}
