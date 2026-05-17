#include <iostream>
#include <string>
#include <vector>
#include <sstream>      
#include <algorithm>    
#include <queue>        

using namespace std;

int getTime(string str);

struct Plan
{
    string name;
    int start;
    int playtime;
    
    Plan (const vector<string>& plan)
    {
        name = plan[0];
        start = getTime(plan[1]);   // hh:mm 형식을 총 분(Minute)으로 변환
        playtime = stoi(plan[2]);    // 과제 시간은 문자열에서 바로 정수로 변환
    }
};

bool comparePlanByStart(const Plan& a, const Plan& b);

vector<string> solution(vector<vector<string>> plans) 
{
    vector<string> answer;
    vector<Plan> planList;
    vector<Plan> stack;       // 일시중단한 과제 관리
    queue<Plan> waitingQueue; // 새로운 과제 대기열
    int curTime = 0;          // 현재 시각
    
    // planList 초기화
    for (int i = 0; i < plans.size(); i++)
    {
        planList.emplace_back(plans[i]);
    }
    
    // 시작 시간 오름차순으로 planList 정렬
    sort(planList.begin(), planList.end(), comparePlanByStart);
    
    // waitingQueue 초기화
    for (const auto& plan : planList)
    {
        waitingQueue.push(plan);
    }
    
    // curTime 초기화 및 첫 과제 세팅
    curTime = waitingQueue.front().start;
    stack.push_back(waitingQueue.front());
    waitingQueue.pop(); 
    
    for (; answer.size() < planList.size(); curTime++)
    {
        // 현재 시간에 새롭게 시작해야 하는 과목이 있는지?
        if (!waitingQueue.empty() && curTime == waitingQueue.front().start)
        {
            stack.push_back(waitingQueue.front());
            waitingQueue.pop();
        }
        
        // 현재 과목 처리
        if (stack.empty()) continue;
        
        Plan& curPlan = stack.back();
        curPlan.playtime--;
        
        // 현재 과목을 다 했으면 완료 처리
        if (curPlan.playtime == 0)
        {   
            answer.push_back(curPlan.name);
            stack.pop_back();
        }
    }
    
    return answer;
}

bool comparePlanByStart(const Plan& a, const Plan& b) 
{ 
    return a.start < b.start; 
}

int getTime(string str)
{
    stringstream ss(str);
    string token;
    
    // hh:mm 문자열을 시(h)와 분(m)으로 즉시 분리하여 분 단위로 통합
    getline(ss, token, ':');
    int h = stoi(token);
    
    getline(ss, token, ':');
    int m = stoi(token);
    
    return h * 60 + m; 
}
