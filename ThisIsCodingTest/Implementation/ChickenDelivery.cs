using System;
using System.Collections.Generic;
class Program
{
    public static void Main(string[] args)
    {
        int n, m;

        const int HOUSE = 1;
        const int CHICKEN = 2;
        List<(int row, int col)> houseList = new();
        List<(int row, int col)> chickenList = new();

        string[] inputs = Console.ReadLine().Split(' ');

        n = int.Parse(inputs[0]);
        m = int.Parse(inputs[1]);

        // houseList와 chickenList 초기화
        for (int i = 0; i < n; i++)
        {
            inputs = Console.ReadLine().Split(' ');

            for (int k = 0; k < n; k++)
            {
                int num = int.Parse(inputs[k]);

                if (num == HOUSE)
                {
                    houseList.Add((i, k));
                }
                else if (num == CHICKEN)
                {
                    chickenList.Add((i, k));
                }
            }
        }

        List<(int row, int col)> candChickenList = new List<(int row, int col)>();
        int minValue = int.MaxValue;

        Backtrack(0, chickenList.Count, m);

        Console.WriteLine(minValue);

        void Backtrack(int start, int n, int m)
        {
            if (candChickenList.Count == m)
            {
                int value = GetTotalChickenDistance(houseList, candChickenList);

                if (value < minValue)
                {
                    minValue = value;
                }
            }
            else
            {
                for (int i = start; i < n; i++)
                {
                    candChickenList.Add(chickenList[i]);
                    Backtrack(i + 1, n, m);
                    candChickenList.Remove(chickenList[i]);
                }
            }
        }
    }

    public static int GetTotalChickenDistance(List<(int row, int col)> houseList, List<(int row, int col)> chickenList)
    {
        int sum = 0;

        for (int i = 0; i < houseList.Count; i++)
        {
            sum += GetChickenDistance(houseList[i], chickenList);
        }

        return sum;
    }

    public static int GetChickenDistance((int row, int col) pos, List<(int row, int col)> chickenList)
    {
        int minDist = int.MaxValue;

        for (int i = 0; i < chickenList.Count; i++)
        {
            int curDist = GetDistance(pos, chickenList[i]);

            if (curDist < minDist)
            {
                minDist = curDist;
            }
        }

        return minDist;
    }

    public static int GetDistance((int row, int col) pos1, (int row, int col) pos2)
    {
        return Math.Abs(pos1.row - pos2.row) + Math.Abs(pos1.col - pos2.col);
    }
}
