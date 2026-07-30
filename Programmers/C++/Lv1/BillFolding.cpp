#include <string>
#include <vector>

using namespace std;

bool IsEnableToPutIn(vector<int> wallet, vector<int> bill)
{
    bool cond1 = bill[0] <= wallet[0] && bill[1] <= wallet[1];
    bool cond2 = bill[0] <= wallet[1] && bill[1] <= wallet[0];
    
    return cond1 || cond2;
}

int solution(vector<int> wallet, vector<int> bill) 
{
    int answer = 0;
    
    while (!IsEnableToPutIn(wallet, bill))
    {
        if (bill[0] > bill[1])
        {
            bill[0] /= 2;
        }
        else
        {
            bill[1] /= 2;
        }
        
        answer++;
    }
    
    
    return answer;
}

