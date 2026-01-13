using System;

class Program 
{
  public static void Main(string[] args) 
  {
    string[] inputs = Console.ReadLine().Split(' ');
    int n = int.Parse(inputs[0]); //전체 회사의 개수
    int m = int.Parse(inputs[1]); //전체 경로의 개수
    const int INF = 1000001;
    int[,] graph = new int[n + 1, n + 1]; //행부터 열까지 가는 거리를 의미

    //Graph 초기화
    for (int i = 1; i < n + 1; i++)
    {
      for (int j = 1; j < n + 1; j++)
      {
        graph[i, j] = i == j ? 0 : INF;
      }
    }
    
    for (int i = 0; i < m; i++)
    {
      inputs = Console.ReadLine().Split(' ');
      int start = int.Parse(inputs[0]);
      int end = int.Parse(inputs[1]);

      graph[start, end] = 1;
      graph[end, start] = 1; //양방향 도로이므로
    }

    inputs = Console.ReadLine().Split(' ');
    int x = int.Parse(inputs[0]);
    int k = int.Parse(inputs[1]);

    for (int middle = 1; middle < n + 1; middle++)
    {
      for (int start = 1; start < n + 1; start++)
      {
        for (int end = 1; end < n + 1; end++)
        {
          graph[start, end] = (int)MathF.Min(graph[start, end], graph[start, middle] + graph[middle, end]);
        }
      }
    }

    int result = graph[1, k] + graph[k, x];

    Console.WriteLine(result >= INF ? -1 : result);
    }
  }
}
