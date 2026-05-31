using System;
using System.Collections.Generic;

class Program
{
    public class Lecture
    {
        public int index;
        public int ownTime;
        public int preMaxTime;    // 선행 과목들 중 Maximum Time
        public List<int> preLectureList = new();
        public int indegree => preLectureList.Count;
        public int Time => ownTime + preMaxTime; 

        public Lecture(int index, int ownTime, List<int> preLectureList)
        {
            this.index = index;
            this.ownTime = ownTime;
            this.preLectureList = preLectureList;
        }
    }
    
    public static void Main(string[] args)
    {
        string[] inputs = Console.ReadLine().Split(' ');
        int n = int.Parse(inputs[0]);
        List<Lecture> lectureList = new();
        int[] answer = new int[n + 1];

        // Lecture 리스트 초기화
        for (int i = 1; i <= n; i++)
        {
            inputs = Console.ReadLine().Split(' ');
            List<int> preLectureList = new();
            for (int k = 1; inputs[k] != "-1"; k++)
            {
                int num = int.Parse(inputs[k]);
                preLectureList.Add(num);
            }

            lectureList.Add(new (i, int.Parse(inputs[0]), preLectureList));
        }

        while (lectureList.Count != 0)
        {
            /// 매 루프마다 진입차수(indegree)가 0인 수업들을 수집.
            /// 여기서 해당 수업들은 Time 계산이 다 끝났다고 가정.
            /// 이 때, 자기를 선행으로 하는 다른 수업들의 시간을 늘려주는 방식...?

            // 현재 진입차수가 0인 수업 인덱스 리스트
            var curLectureList = GetZeroIndegreeLectureList(lectureList);

            foreach (var lecture in lectureList)
            {
                // 현재 진입차수가 0인 수업들을 선행 과목으로 하고 있는 수업들 찾기
                var sameLectureList = GetSameLectureList(lecture.preLectureList, curLectureList);
                
                var curMaxTime = GetMaxTime(sameLectureList);
                lecture.preMaxTime = lecture.preMaxTime < curMaxTime ? curMaxTime : lecture.preMaxTime;

                for (int i = 0; i < sameLectureList.Count; i++)
                {
                    lecture.preLectureList.Remove(sameLectureList[i].index);
                }
            }

            foreach (var curTarget in curLectureList)
            {
                lectureList.Remove(curTarget);
                answer[curTarget.index] = curTarget.Time;
            }
        }

        for (int i = 1; i < answer.Length; i++)
        {
            Console.WriteLine(answer[i]);
        }
    }

    public static int GetMaxTime(List<Lecture> targetLectureList)
    {
        int maxTime = 0;
        
        for (int i = 0; i < targetLectureList.Count; i++)
        {
            var curTarget = targetLectureList[i];

            if (maxTime < curTarget.Time)
            {
                maxTime = curTarget.Time;
            }
        }

        return maxTime;
    }

    public static List<Lecture> GetSameLectureList(List<int> preIndexList, List<Lecture> targetLectureList)
    {
        List<Lecture> sameLectureList = new();

        for (int i = 0; i < preIndexList.Count; i++)
        {
            var curIndex = preIndexList[i];

            for (int k = 0; k < targetLectureList.Count; k++)
            {
                var curTarget = targetLectureList[k];

                if (curTarget.index == curIndex)
                {
                    sameLectureList.Add(curTarget);
                }
            }
        }

        return sameLectureList;
    }

    public static List<Lecture> GetZeroIndegreeLectureList(List<Lecture> lectureList)
    {
        List<Lecture> zeroIndegreeLectureList = new();
        
        for (int i = lectureList.Count - 1; 0 <= i; i--)
        {
            var lecture = lectureList[i];
            
            if (lecture.indegree == 0)
            {
                zeroIndegreeLectureList.Add(lecture);
            }
        }

        return zeroIndegreeLectureList;
    }
}
