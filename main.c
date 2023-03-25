#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    int accum = 0;
    bool quit = false;
    //Pas fonctionnel
    // clockid_t clock_id = CLOCK_MONOTONIC;
    // /* code */
    //         //
    //     MLV_create_window( "beginner - 1 - hello world", "hello world", 640, 480 );
    //     while(!quit){
    //         clock_gettime(clock_id, &last);

    //         accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / 1000000);
    //         if(accum < (1.0/48.0)){
    //             MLV_wait_milliseconds((((1.0/48.0) - accum)*1000));
    //         }
    //     }

        MLV_free_window();
    return 0;
}
