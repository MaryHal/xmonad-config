#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Update Interval in seconds
#define INTERVAL        45

// Files read for system info:
#define CPU_FILE        "/proc/stat"
#define MEM_FILE        "/proc/meminfo"

#define BATT_NOW        "/sys/class/power_supply/BAT0/charge_now"
#define BATT_FULL       "/sys/class/power_supply/BAT0/charge_full"
#define BATT_STAT       "/sys/class/power_supply/BAT0/status"

// Display format strings:
#define CPU_STR         "Cpu: %d%% "        // CPU percent when below CPU_HI%
#define CPU_HI_STR      "Cpu!: %d%% "       // CPU percent when above CPU_HI%

// Memory
#define MEM_STR         "Free: %d%% Buffers: %d%% Cache: %ld%% "

#define BAT_STR         "%d%% "     // Battery, unplugged, above BATT_LOW%
#define BAT_LOW_STR     "!! %d%% "   // Battery, unplugged, below BATT_LOW% remaining
#define BAT_CHRG_STR    "%d%%C "    // Battery, when charging (plugged into AC)

// This is a strftime format string which is passed localtime
#define DATE_TIME_STR   "%a %b %d, %I:%M %p"

#define BattFmt "^fg()^i(/home/sanford/.xmonad/icons/batt10.xbm) ^fg(#b294bb)%d%%^fg()  "
#define TimeFmt "^fg()^i(/home/sanford/.xmonad/icons/clock2.xbm) %s " 

void displayTime(const char* fmt)
{
    time_t current;
    char buffer[64];

    time(&current);
    strftime(buffer, 38, DATE_TIME_STR, localtime(&current));

    printf(fmt, buffer);
}

void displayBattery(const char* fmt)
{
    FILE* infile;
    long charge, full;

    infile = fopen(BATT_NOW, "r");
    fscanf(infile, "%ld\n", &charge);
    fclose(infile);

    infile = fopen(BATT_FULL, "r");
    fscanf(infile, "%ld\n", &full);
    fclose(infile);

    /* infile = fopen(BATT_STAT, "r"); */
    /* fscanf(infile, "%s\n", statnext); */
    /* fclose(infile); */

    int num = charge * 100 / full;
    printf(fmt, num);
}

void displayTemp(const char* fmt)
{
    FILE* infile;
    long charge, full;

    infile = fopen(BATT_NOW, "r");
    fscanf(infile, "%ld\n", &charge);
    fclose(infile);

    infile = fopen(BATT_FULL, "r");
    fscanf(infile, "%ld\n", &full);
    fclose(infile);

    /* infile = fopen(BATT_STAT, "r"); */
    /* fscanf(infile, "%s\n", statnext); */
    /* fclose(infile); */

    int num = charge * 100 / full;
    printf(fmt, num);
}

int main()
{
    for (;;)
    {
        displayBattery(BattFmt);
        displayTime(TimeFmt);

        printf("\n");

        fflush(stdout);
        sleep(INTERVAL);
    }

    return 0;
}

