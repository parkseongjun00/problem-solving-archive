#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Pos
{
    int x;
    int y;
    
    void operator+= (const Pos& other) 
    {
        this->x += other.x;
        this->y += other.y;
    }
    
    Pos operator+ (const Pos& other) const
    {
        return { this->x + other.x, this->y + other.y};
    }
    
    Pos operator- (const Pos& other) const
    {
        return { this->x - other.x, this->y - other.y};
    }
    
    bool operator== (const Pos& other) const
    {
        return this->x == other.x && this->y == other.y;
    }
};

void get_relative_poses(vector<Pos>& pos_list, const Pos& origin);
void rotate_clockwise(vector<Pos>& list);
void Move(vector<Pos>& list, const Pos& delta);

bool solution(vector<vector<int>> key, vector<vector<int>> lock) 
{
    bool answer = true;
    
    vector<Pos> key_pos_list;   // 열쇠 돌기
    vector<Pos> lock_pos_list;  // 자물쇠 돌기
    vector<Pos> lock_hole_list; // 자물쇠 홈
    
    // key_pos_list 초기화
    for (int i = 0; i < key.size(); i++)
    {
        for (int k = 0; k < key[i].size(); k++)
        {
            if (key[i][k] == 1)
            {
                key_pos_list.push_back({k, i});
            }
        }
    }
    
    // lock_pos_list 및 lock_hole_list 초기화
    for (int i = 0; i < lock.size(); i++)
    {
        for (int k = 0; k < lock[i].size(); k++)
        {
            if (lock[i][k] == 1)
            {
                lock_pos_list.push_back({k, i});
            }
            else
            {
                lock_hole_list.push_back({k, i});
            }
        }
    }
    
    // 해볼 가치도 없음
    // 열쇠 저 멀리 던지면 됨
    if (lock_hole_list.size() == 0)
    {
        return true;
    }
     
    // key_pos_list를 순회하면서 각 요소가 원점이 되어 
    // lock_pos_list[0]에 위치시키고, 4방향 회전시키고, 유효한지 확인
    // 유효 조건: Lock의 모든 홈을 채웠는가? && key와 lock 간 겹치는 게 없는가?
    for (int i = 0; i < key_pos_list.size(); i++)
    {
        Pos now = key_pos_list[i];
        get_relative_poses(key_pos_list, now);
        
        for (int rotate_count = 0; rotate_count < 4; rotate_count++)
        {
            // 회전시키기 전에 한 번 위치가 움직였다면 다시 원점으로 옮겨줌.
            // 변환 누적 방지
            if (0 < rotate_count)
            {
                Move(key_pos_list, { -lock_hole_list[0].x, -lock_hole_list[0].y });
            }
            
            rotate_clockwise(key_pos_list);
            Move(key_pos_list, lock_hole_list[0]);
            
            // 유효성 검사
            bool isInvalid = false;
            // 1. Lock의 모든 홈을 채웠는가?
            for (int k = 0; k < lock_hole_list.size(); k++)
            {
                Pos target = lock_hole_list[k];
                
                if (find(key_pos_list.begin(), key_pos_list.end(), target) == key_pos_list.end())
                {
                    isInvalid = true;
                    break;
                }
            }
            
            if (isInvalid)
            {
                continue;
            }
            
            // 2. key와 lock 간 겹치는 것이 없는가?
            for (int k = 0; k < key_pos_list.size(); k++)
            {
                Pos target = key_pos_list[k];
                
                if (find(lock_pos_list.begin(), lock_pos_list.end(), target) != lock_pos_list.end())
                {
                    isInvalid = true;
                    break;
                }
            }
            
            if (!isInvalid)
            {
                return true;
            }
            
        }
        
        
    }

    return false;
}

// 상대 좌표를 구하는 함수
void get_relative_poses(vector<Pos>& pos_list, const Pos& origin)
{
    for (int i = 0; i < pos_list.size(); i++)
    {
        pos_list[i] = pos_list[i] - origin;
    }
}

// 이거 Gemini의 도움을 구함
// 원점이 (0, 0)이라 가정했을 때 90도 회전하면 (y, -x)
// 근데 지능 이슈 있어서 30분 걸림
void rotate_clockwise(vector<Pos>& list)
{
    for (int i = 0; i < list.size(); i++)
    {
        list[i] = { list[i].y, -list[i].x };
    }
}

void Move(vector<Pos>& list, const Pos& delta)
{
    for (int i = 0; i < list.size(); i++)
    {
        list[i] += delta;
    }
}
