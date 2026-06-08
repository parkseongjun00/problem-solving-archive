#include <string>
#include <vector>

using namespace std;

vector<string> get_substring_list(const string& text, int count);
string get_renewal_text(const vector<string>& text_list);

int solution(string s) 
{
    int length = s.length();
    int answer = length;
    
    // n개 단위로 자르기를 반복
    for (int i = 1; i <= length / 2; i++)
    {
        vector<string> list = get_substring_list(s, i);
        string new_text = get_renewal_text(list);
        
        if (new_text.length() < answer)
        {
            answer = new_text.length();
        }
    }
    
    return answer;
}

vector<string> get_substring_list(const string& text, int count)
{
    vector<string> result;
    int pointer = 0;
    
    for (; pointer + count <= text.length(); pointer += count)
    {
        result.push_back(text.substr(pointer, count));
    }
    
    // 아직 잔여 텍스트가 있을 경우
    if (pointer < text.length())
    {
        result.push_back(text.substr(pointer, text.length() - pointer));
    }
    
    return result;
}

string get_renewal_text(const vector<string>& text_list)
{
    if (text_list.size() == 1)
    {
        return text_list[0];
    }
    
    string prev = "";   // 이전 서브 텍스트
    int count = 1;      // 이전 서브 텍스트의 등장 횟수, 첫 번째 조각을 이미 확인했으므로 1로 시작해야.
    string result = "";
    
    prev = text_list[0];
    
    for (int i = 1; i < text_list.size(); i++)
    {
        string now = text_list[i];
        
        if (prev == now)
        {
            count += 1;
        }
        else
        {
            if (1 < count)
            {
                result += to_string(count);
            }
            
            result += prev;
            prev = now;
            count = 1;
        }
    }
    
    // 반복문 종료 후 남아있는 마지막 서브 텍스트 처리
    // 이전에는 반복문 도중에 마지막인지 검사해서 했었는데, 
    // 조건문이 True이든 False이든 마지막 덩어리만 못 들어가는 버그가 존재했다.
    if (count > 1)
    {
        result += to_string(count);
    }
    result += prev;
    
    return result;
}
