#include <kipr/wombat.h>
#include <time.h>

void drive(int, int);
void linefollow(int);

int main()
{
    enable_servos();
    //wait for light

    float z;
    clock_t begin, end;

    begin = clock();

    set_servo_position(1,600);
    set_servo_position(0,400);

    drive(720, -50);

    motor(0,-50);
    motor(2,50);
    msleep(1225);
    ao();
    msleep(500);

    drive(8000, -60);

    drive(1000,50);

    motor(0,60);
    msleep(1200);
    ao();

    set_servo_position(1,1800);

    drive(1900,-50);


    set_servo_position(0,950);
    msleep(1000);

    drive(600,50);

    set_servo_position(1,550);
    msleep(1000);

    drive(900,50);

    motor(0,60);
    motor(2,-60);
    msleep(600);
    ao();

    motor(2,-80);
    motor(0,-40);
    msleep(3375);
    ao();

    linefollow(7000);

    motor(2,-80);
    msleep(1000);
    ao();

    drive(2000,-50);
    drive(2000,50);

    motor(2,80);
    msleep(800);
    ao();

    linefollow(6600);

    drive(2000,50);

    set_servo_position(1,1750);
    msleep(1000);

    drive(900,-50);

    motor(2,20);
    msleep(100);
    ao();

    do
    {
        end = clock();
        z = end - begin;

    }while(z < 18500000);

    motor(0,-80);
    motor(2,80);
    msleep(1000);

    while(analog(1) < 2500)
    {
        motor(0,-50);
        motor(2,50);
    }
    ao();

    linefollow(4000);

    motor(0,-50);
    motor(2,50);
    msleep(700);

    drive(500,-50);

    set_servo_position(0,400);

    drive(500,50);

    motor(0,50);
    motor(2,-50);
    msleep(700);

    set_servo_position(1,1000);

    linefollow(13000);

    drive(2000,60);

    set_servo_position(1,1750);

    motor(0,-30);
    motor(2,50);
    msleep(950);
    ao();

    drive(2950,-50);

    drive(700,-50);

    set_servo_position(0,1200);
    msleep(1000);

    drive(1600,50);
    ao();

    set_servo_position(1,600);
    msleep(1000);

    motor(2,15);
    motor(0,-80);
    msleep(2100);

    drive(3000,50);
    ao();

    drive(4000,-100);

    while(analog(1) < 2500){

        motor(0,-70);
        motor(2,-70);
    }
    ao();

    set_servo_position(1,1500);
    msleep(1000);
    set_servo_position(0,300);
    msleep(1000);

    ao();

    disable_servos();

    return 0;
}

void drive(int time, int speed)
{
    motor(0,speed);
    motor(2,speed);
    msleep(time);
    ao();

}

void linefollow(int distance)
{
    cmpc(0);

    while(gmpc(0) > -distance)
    {
        if(analog(2) > 2500)
        {
            motor(0,-80);
            motor(2,-20);
        }

        if(analog(1) > 2500)
        {
            motor(0,-20);
            motor(2,-80);
        }
        motor(0,-50);
        motor(2,-50);

    }
    ao();
}
