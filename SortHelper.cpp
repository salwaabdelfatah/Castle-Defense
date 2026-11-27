#include "SortHelper.h"
#include "Enemy.h"

void SortByFD(Enemy* arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        Enemy* key = arr[i];

        int keyFD =
            key->GetFirstShotTime() - key->GetArrivalTime();

        int j = i - 1;

        while (j >= 0 &&
            (arr[j]->GetFirstShotTime() - arr[j]->GetArrivalTime()) > keyFD)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}