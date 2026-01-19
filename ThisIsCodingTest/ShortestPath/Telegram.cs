using System;
using System.Collections.Generic;

class Program 
{
  public static void Main(string[] args) 
  {
    const int INF = 1000000;
    string[] inputs = Console.ReadLine().Split(' ');
    int n = int.Parse(inputs[0]);
    int m = int.Parse(inputs[1]);
    int c = int.Parse(inputs[2]);
    int[,] graph = new int[n + 1, n + 1];
    int[] dist = new int[n + 1];
    PriorityQueue<int, int> priorityQueue = new PriorityQueue<int, int>();
    int count = 0;
    int max = 0;

    for (int i = 1; i < n + 1; i++)
    {
      for (int k = 1; k < n + 1; k++)
      {
        if (i == k)
        {
          graph[i, k] = 0;
        }
        else
        {
          graph[i, k] = INF;
        }
      }

      dist[i] = INF;
    }

    for (int i = 0; i < m; i++)
    {
      inputs = Console.ReadLine().Split(' ');
      int x = int.Parse(inputs[0]);
      int y = int.Parse(inputs[1]);
      int z = int.Parse(inputs[2]);

      graph[x, y] = z;
    }

    priorityQueue.Enqueue(c, 0);
    dist[c] = 0;

    while (priorityQueue.Count != 0)
    {
      
      priorityQueue.TryDequeue(out int current, out int curDist);

      if (dist[current] < curDist)
      {
        continue;
      }
      
      Console.WriteLine($"안녕하세요~ current는 {current}이고, curDist는 {curDist}입니다!");

      for (int i = 1; i < n + 1; i++)
      {
        if (curDist + graph[current, i] < dist[i])
        {
          Console.WriteLine($"{i} 값이 들어갔습니다!: {curDist} + {graph[current, i]} < {dist[i]} 라서요!");
          Console.WriteLine($"참고로 current: {current}, i: {i} 입니다!");
          dist[i] = curDist + graph[current, i];
          priorityQueue.Enqueue(i, graph[current, i]);
        }
      }
    }

    for (int i = 1; i < n + 1; i++)
    {
      if (i == c)
      {
        //처음 메시지를 보내는 도시는 Total에서 제외
        continue;
      }
      
      if (dist[i] < INF)
      {
        if (max < dist[i])
        {
          max = dist[i];
        }
        
        count++;
      }
    }

    Console.WriteLine($"{count} {max}");
  }
}
