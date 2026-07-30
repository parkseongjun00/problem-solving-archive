#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// bandage_len은 배열 bandage의 길이입니다.
// attacks_rows는 2차원 배열 attacks의 행 길이, attacks_cols는 2차원 배열 attacks의 열 길이입니다.
int solution(
    int bandage[], 
    size_t bandage_len, 
    int health, 
    int** attacks, 
    size_t attacks_rows, 
    size_t attacks_cols) 
{
    int curHealth = health;
    int comboCount = 0;
    int curAttackIndex = 0;
    int finalAttackTime = attacks[attacks_rows - 1][0];
    
    for (int i = 1; i <= finalAttackTime; i++)
    {
        //현재 공격 받음
        if (i == attacks[curAttackIndex][0])
        {
            curHealth -= attacks[curAttackIndex][1];
            comboCount = 0;
            curAttackIndex++;
            
            if (curHealth <= 0)
            {
                return -1;
            }
            
            continue;
        }
    
        curHealth += bandage[1];
        comboCount++;
        
        if (comboCount == bandage[0])
        {
            curHealth += bandage[2];
            comboCount = 0;
        }
        
        if (curHealth > health)
        {
            curHealth = health;
        }
    }
    
    return curHealth;
}
