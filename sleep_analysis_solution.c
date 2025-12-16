#include <stdio.h>

int to_minutes(int hhmm) {
    int h = hhmm / 100;
    int m = hhmm % 100;
    return h * 60 + m;
}

int calculate_sleep_minutes(int sleep_time, int wake_time) {
    int sleep_min = to_minutes(sleep_time);
    int wake_min = to_minutes(wake_time);

    if (wake_min > sleep_min) {
        return wake_min - sleep_min;
    } else {
        return (24 * 60 - sleep_min) + wake_min;
    }
}

int is_irregular(int sleep_time, int wake_time) {
    int sleep_h = sleep_time / 100;
    int sleep_m = sleep_time % 100;
    int wake_h = wake_time / 100;
    int wake_m = wake_time % 100;

    // خواب بعد از 00:00
    if (sleep_h > 0 && sleep_h < 5)
        return 1;
    if (sleep_h == 00 && sleep_m > 0) return 1;
    // بیداری بعد از 10:00
    if (wake_h > 10 || (wake_h == 10 && wake_m > 0))
        return 1;

    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    int total_sleep = 0;
    int low_sleep_nights = 0;
    int irregular_nights = 0;

    for (int i = 0; i < n; i++) {
        int sleep_time, wake_time;
        scanf("%d-%d", &sleep_time, &wake_time);

        int sleep_minutes = calculate_sleep_minutes(sleep_time, wake_time);
        total_sleep += sleep_minutes;

        if (sleep_minutes < 360)
            low_sleep_nights++;

        if (is_irregular(sleep_time, wake_time))
            irregular_nights++;
    }

    double average_sleep = (double)total_sleep / n;

    printf("Total Sleep: %d minutes\n", total_sleep);
    printf("Average Sleep: %.2f minutes\n", average_sleep);
    printf("Low Sleep Nights: %d\n", low_sleep_nights);
    printf("Irregular Nights: %d\n", irregular_nights);

    return 0;
}
