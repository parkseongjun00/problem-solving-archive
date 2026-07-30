#include <string>
#include <vector>
#include <algorithm> //정렬 메서드를 이용하기 위해 필요한 헤더 파일

using namespace std;

bool IsAvailable(vector<vector<string>> park, vector<int> startPos, int length)
{
    for (int row = startPos[0]; row < startPos[0] + length; row++)
    {
        for (int col = startPos[1]; col < startPos[1] + length; col++)
        {
            if (park[row][col] != "-1")
            {
                return false;
            }
        }
    }
    
    return true;
}

int solution(vector<int> mats, vector<vector<string>> park) 
{    
    int rowSize = park.size();
    int colSize = park[0].size();

    //정렬을 이용하는 방법.
    //begin()은 벡터의 시작 주소, end()는 벡터의 끝 주소(마지막 원소 다음 위치), greater<int>()는 큰게 앞으로 오게 하는 비교 함수.
    sort(mats.begin(), mats.end(), greater<int>()); 
    
    for (int i = 0; i < mats.size(); i++)
    {
        int curLength = mats[i];
        int curMaxRow = rowSize - curLength;
        int curMaxCol = colSize - curLength;
        bool failed = false;
        
        for (int curRowIdx = 0; curRowIdx <= curMaxRow; curRowIdx++)
        {
            for (int curColIdx = 0; curColIdx <= curMaxCol; curColIdx++)
            {
                vector<int> curPos = { curRowIdx, curColIdx };
                
                if (IsAvailable(park, curPos, curLength)) return curLength;
            }
        }
    }
    
    return -1;
}
