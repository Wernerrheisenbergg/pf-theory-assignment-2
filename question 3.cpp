#include <stdio.h>

void inputReadings(int temp[][50], int sensors, int hours)
{
    int i, j;

    for (i = 0; i < sensors; i++)
    {
        printf("Enter %d readings for sensor %d: ", hours, i + 1);
        for (j = 0; j < hours; j++)
        {
            scanf("%d", &temp[i][j]);
        }
    }
}

float analyzeSensor(int readings[], int hours, int sensorNo)
{
    int j, total = 0, high, low;
    int critical = 0, warning = 0, streak = 0, longest = 0;
    float average;

    high = readings[0];
    low = readings[0];

    for (j = 0; j < hours; j++)
    {
        total = total + readings[j];

        if (readings[j] > high)
            high = readings[j];
        if (readings[j] < low)
            low = readings[j];

        if (readings[j] >= 40)
            critical++;
        else if (readings[j] >= 35)
            warning++;

        if (readings[j] >= 35)
        {
            streak++;
            if (streak > longest)
                longest = streak;
        }
        else
        {
            streak = 0;
        }
    }

    average = (float)total / hours;

    printf("\nSensor %d Report\n", sensorNo);
    printf("Total: %d\n", total);
    printf("Average: %.2f\n", average);
    printf("Highest: %d\n", high);
    printf("Lowest: %d\n", low);
    printf("Critical readings: %d\n", critical);
    printf("Warning readings: %d\n", warning);
    printf("Longest streak at 35 or above: %d hour(s)\n", longest);

    return average;
}

int highestAverage(float avg[], int sensors)
{
    int i, best = 0;

    for (i = 1; i < sensors; i++)
    {
        if (avg[i] > avg[best])
            best = i;
    }
    return best;
}

int main()
{
    int temp[50][50];
    float avg[50];
    int sensors, hours, i, best;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    inputReadings(temp, sensors, hours);

    for (i = 0; i < sensors; i++)
    {
        avg[i] = analyzeSensor(temp[i], hours, i + 1);
    }

    best = highestAverage(avg, sensors);

    printf("\nSensor with the highest average: Sensor %d\n", best + 1);
    printf("Its average reading: %.2f\n", avg[best]);

    return 0;
}
