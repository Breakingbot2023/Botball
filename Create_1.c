#include <kipr/wombat.h>
#include <time.h>

int LINE_SEARCH_SPEED = 50;
int THRESHOLD = 2750;

void fahren(int, int);
void turn(int, int);
void lineSearch(int, int);
void driveTillCrash(int);
void botDriving();

int main()
{
    clock_t t;
    t = clock();

    create_connect();

    botDriving();

    create_disconnect();
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken: %.2f", time_taken);
    return 0;
}

void fahren(int weg, int speed)
{
    set_create_distance(0);

    if (weg < 0)
    {
        while (get_create_distance() > weg)
        {
            create_drive_direct(-speed, -speed);
        }
    }
    else if (weg > 0)
    {
        while (get_create_distance() < weg)
        {
            create_drive_direct(speed, speed);
        }
    }
    printf("Fuhr: %dmm\n", weg);
}

void turn(int winkel, int speed)
{
    if (winkel < 0)
    {
        set_create_total_angle(0);
        while (get_create_total_angle() > winkel)
        {
            create_drive_direct(speed, -speed);
        }
        printf("Hat sich: %dB0 nach rechts gedreht.\n", winkel * -1);
    }
    else if (winkel > 0)
    {
        set_create_total_angle(0);
        while (get_create_total_angle() < winkel)
        {
            create_drive_direct(-speed, speed);
        }
        printf("Hat sich: %dB0 nach links gedreht.\n", winkel);
    }
}

void lineSearch(int speedAngleChange, int angleChange)
{
    set_create_distance(0);
    while (get_create_rbump() == 0 || get_create_lbump() == 0)
    {
        if (get_create_lfcliff_amt() > THRESHOLD && get_create_rfcliff_amt() > THRESHOLD)
        {
            create_drive_direct(LINE_SEARCH_SPEED, LINE_SEARCH_SPEED);
            printf("Nothing to correct.\n");
        }
        else if (get_create_lfcliff_amt() > THRESHOLD)
        {
            set_create_total_angle(0);
            while (get_create_total_angle() > -angleChange)
            {
                create_drive_direct(speedAngleChange, -speedAngleChange);
            }
            printf("Turned %dB0 right, to the line\n", angleChange * -1);
        }
        else if (get_create_rfcliff_amt() > THRESHOLD)
        {
            set_create_total_angle(0);
            while (get_create_total_angle() < angleChange)
            {
                create_drive_direct(-speedAngleChange, speedAngleChange);
            }
            printf("Turned %dB0 left, to the line\n", angleChange);
        }
        else if (get_create_lfcliff_amt() > THRESHOLD && get_create_rfcliff_amt() > THRESHOLD)
        {
            printf("I dont think so buddy\n");
            create_disconnect();
            //return 0;
        }
        printf("Left Sensor: %d    |   Right Sensor: %d\n", get_create_lfcliff_amt(), get_create_rfcliff_amt());
    }
}

void driveTillCrash(int speed)
{
    set_create_distance(0);
    while (get_create_rbump() == 0 || get_create_lbump() == 0)
    {
        create_drive_direct(speed, speed);
    }
    printf("KRESHHHHH! at: %dmm\n", get_create_distance());
}

void botDriving()
{
    fahren(600, 200);

    turn(-90, 200);

    fahren(-130, 200);

    while (get_create_lfcliff_amt() > THRESHOLD)
    {
        create_drive_direct(400, 400);
    }
    fahren(150, 200);

    turn(107, 150);

    lineSearch(50, 4);

    // Greifen einsetzen

    fahren(-50, 200);

    turn(80, 300);

    driveTillCrash(100);

    fahren(-20, 50);

    turn(80, 500);

    while (get_create_lfcliff_amt() > THRESHOLD && get_create_rfcliff_amt() > THRESHOLD)
    {
        create_drive_direct(1000, 1000);
    }

    // Botgirl Abliefern

    turn(190, 200);

    driveTillCrash(100);

    fahren(-40, 50);

    turn(-90, 100);

    fahren(-140, 50);

    turn(25, 100);

    while (get_create_lfcliff_amt() > THRESHOLD)
    {
        create_drive_direct(100, 100);
    }

    fahren(40, 50);

    turn(55, 100);

    fahren(-140, 50);
}
