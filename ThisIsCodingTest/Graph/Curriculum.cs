using System;
using System.Collections.Generic;

class Program
{
    public static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        int[] time = new int[n + 1];
        int[] result = new int[n + 1];
        int[] indegrees = new int[n + 1];
        // 인덱스는 '수강을 완료한 특정 과목', 내부는 '그로 인해 들을 수 있게 된 후속 과목들'을 의미
        List<int>[] graph = new List<int>[n + 1];
        Queue<int> queue = new Queue<int>();
        
        for (int i = 1; i < n + 1; i++)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            time[i] = int.Parse(inputs[0]);
            graph[i] = new List<int>();

            for (int k = 1; k < inputs.Length && inputs[k] != "-1"; k++)
            {
                int num = int.Parse(inputs[k]);
                graph[num].Add(i);
                indegrees[i] += 1;
            }
        }

        result = (int[])time.Clone();

        for (int i = 1; i < n + 1; i++)
        {
            if (indegrees[i] == 0)
            {
                queue.Enqueue(i);
            }
        }

        while (0 < queue.Count)
        {
            int now = queue.Dequeue();

            for (int i = 0; i < graph[now].Count; i++)
            {
                // [회고 1] 루프 인덱스(i)를 직접 참조(삽입)하는 실수를 막기 위해, 
                // 탐색 요소를 지역 변수(num)에 명시적으로 할당하여 사용하는 것이 안전하다.
                int num = graph[now][i];
                indegrees[num] -= 1;
                result[num] = Math.Max(result[num], result[now] + time[num]);

                // [회고 2] 진입차수를 갱신하는 반복문과 큐 삽입 대상을 찾는 반복문을 분리해서는 안 된다. 
                // 상태 갱신과 검증이 같은 루프 내에서 즉각적으로 이루어지지 않으면, 
                // 특정 노드가 큐에 중복 삽입되는 논리적 오류가 발생하기 때문이다.
                if (indegrees[num] == 0)
                {
                    queue.Enqueue(num);
                }
            }
        }

        for (int i = 1; i < n + 1; i++)
        {
            Console.WriteLine(result[i]);
        }
    }
}
