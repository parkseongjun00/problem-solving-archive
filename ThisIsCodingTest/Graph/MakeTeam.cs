using System;
using System.Collections.Generic;

class Program 
{
  public static void Main(string[] args) 
  {
    List<string> answer = new();
    const int UNION = 0;
    const int CHECK = 1;
    string[] inputs = Console.ReadLine().Split(' ');
    List<int> studentList = new List<int>();
    int n = int.Parse(inputs[0]);
    int m = int.Parse(inputs[1]);

    // 학생들 초기화
    for (int i = 0; i <= n; i++)
    {
      studentList.Add(i);
    }

    for (int i  = 0; i < m; i++)
    {
      inputs = Console.ReadLine().Split(' ');
      int x = int.Parse(inputs[0]);
      int a = int.Parse(inputs[1]);
      int b = int.Parse(inputs[2]);

      
      if (x == UNION)
      {
        UnionTeam(a, b);
      }

      if (x == CHECK)
      {
        a = FindTeam(a);
        b = FindTeam(b);

        
        if (a == b) answer.Add("YES");
        else answer.Add("NO");
      }
    }

    for (int i = 0; i < answer.Count; i++)
    {
      Console.WriteLine(answer[i]);
    }

    // [성능 최적화 가이드] 
    // 현재는 가독성을 위해 지역 함수를 사용 중이나, 
    // 호출 빈도가 극도로 높을 경우 멤버 함수로 분리하여 캡처 오버헤드 제거할 것.
    int FindTeam(int index)
    {
      if (studentList[index] == index) 
      {
        return index;
      }

      return FindTeam(studentList[index]);
      // 위 방식도 답을 얻는 데 문제는 없지만, 부모를 찾을 때마다 트리를 타고 올라가야 한다.
      // 찾은 값을 부모로 바로 갱신해주면 좋다.
      // studentList[index] = FindTeam(studentList[index]);
    }

    void UnionTeam(int indexA, int indexB)
    {
      int a = FindTeam(indexA);
      int b = FindTeam(indexB);

      if (a < b) studentList[b] = a;
      else studentList[a] = b;
    }
  }
}
