#include <iostream>
#include <string>
#include <vector>
#include <sstream>      //stringstream 사용을 위해서 필요
#include <algorithm>    //정렬 알고리즘 사용을 위해서 필요

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
        start = getTime(plan[1]);
        playtime = getTime(plan[2]);
    }
};

bool comparePlanByStart(const Plan& a, const Plan& b);

vector<string> solution(
    vector<vector<string>> plans) 
{
    vector<string> answer;
    vector<Plan> planList;
    vector<Plan> stack;      // 일시중단한 과제 관리를 위해 필요
    int curTime = 0;         // 현재 시각
    int pointer = 0;         // 새로운 과목의 순차 실행을 위한 planList 내 현재 포인터 (포인터보다 더 좋은, 새로운 과제 시작을 위한 방법이 있을 것 같다.)
    
    //planList 초기화
    for (int i = 0; i < plans.size(); i++)
    {
        //구조체의 생성자로 바로 인자를 던짐
        planList.emplace_back(plans[i]);
    }
    
    // 시작 시간 오름차순으로 planList 정렬
    sort(planList.begin(), planList.end(), comparePlanByStart);
    
    //curTime 초기화 및 stack 초기화
    curTime = planList[0].start;
    stack.push_back(planList[0]);
    
    for (; answer.size() < planList.size(); curTime++)
    {
        // hh:mm 형식의 시간 관리 (근데 시간 관리 이렇게 안 하면 이득 취할 수 있음.)
        if (curTime % 100 == 60)
        {
            curTime += 100 - 60;
        }
        
        // 현재 시간에 새롭게 시작해야 하는 과목이 있는지?
        // 있으면: 현재 과목을 stack에 저장해두고 새로운 과목 시작
        if (pointer + 1 < planList.size())
        {
            Plan& nextPlan = planList[pointer + 1];
            if (curTime >= nextPlan.start)
            {
                stack.push_back(nextPlan);
                pointer++;
            }
        }
        
        // 현재 과목 처리
        // 현재 과목이 비어있다면 생략 
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
    vector<int> result;
    
    while (getline(ss, token, ':')) 
    {
        result.push_back(stoi(token));
    }
    
    // 형식이 hh:mm일 경우
    if (result.size() == 2) 
    {
        return result[0]*100 + result[1];
    }
    //그렇지 않을 경우 분(mm)으로 간주
    else 
    {
        return result[0];
    }
}
