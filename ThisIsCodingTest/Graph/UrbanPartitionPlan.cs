using System;
using System.Collections.Generic;

class Program
{
    // 다차원 배열[,]과 가변 배열[][] 이 존재한다.
    // 전자는 행마다 크기가 동일하며, 후자는 다를 수 있다.
    // 그러나 정렬 등의 연산이 요구될 때는 이중 리스트가 낫다.
    public static void Main(string[] args)
    {
        string[] inputs = Console.ReadLine().Split(' ');
        int n = int.Parse(inputs[0]);
        int m = int.Parse(inputs[1]);
        List<int> parent = new() { 0 };      // 인덱스 일치를 위해 하나 더 할당
        List<List<int>> pathList = new();
        int answer = 0;
        int maxPathCost = 0;                 // 최소 신장 트리에서의 최대 간선 비용

        // 부모를 자기 자신으로 초기화
        for (int i = 1; i <= n; i++)
        {
            parent.Add(i);
        }

        for (int i = 0; i < m; i++)
        {
            inputs = Console.ReadLine().Split(' ');
            int a = int.Parse(inputs[0]);
            int b = int.Parse(inputs[1]);
            int c = int.Parse(inputs[2]);

            pathList.Add(new List<int>() { a, b, c });
        }

        // 리스트 정렬 
        pathList.Sort((a, b) => a[2].CompareTo(b[2]));

        for (int i = 0; i < m; i++)
        {
            List<int> curPath = pathList[i];
            int a = FindParent(parent, curPath[0]);
            int b = FindParent(parent, curPath[1]);
            int c = curPath[2];

            // 사이클을 발생시키지 않게 해줘야 함.
            // 맨 처음에는 break로 했으나, continue로 해야 한다.
            if (a == b) continue;

            if (a < b) parent[b] = a;
            else parent[a] = b;
            maxPathCost = c;  // pathList를 비용 순으로 정렬했으므로, 뒤로 갈수록 비싸다.
            answer += c;
        }

        // 출력하기 전에, 문제 조건에 따라 가장 비용이 비싼 간선을 제거하여
        // 큰 마을 하나를 작은 마을 2개로 분리해야 한다.
        answer -= maxPathCost;

        Console.WriteLine(answer);
    }

    public static int FindParent(List<int> parent, int index)
    {
        if (parent[index] == index) return index;
        return parent[index] = FindParent(parent, parent[index]);
    }
}
