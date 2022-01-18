#include "cmake-build-debug/db.h"

void Scenario() {
    printf("%s","Hi, now we are going to walk through the script that was written earlier.\n");
    printf("%s","Now we will insert 5 master inserts(insert_m)\n");
    for(int i = 0; i < 5; i++)
        insert_m();
    printf("%s","Now we will insert 1 slave to first master, 2 to second and 3 to third.\n");
    for(int i = 0; i < 6;i++)
        insert_s();
    printf("%s", "Now we will output our tabs.\n");
    ut_m();
    ut_s();
    printf("%s","Now we will delete second master.\n");
    del_m();
    printf("%s", "Now we will delete slave from third master.\n");
    del_s();
    printf("%s", "Now we will output our tabs.\n");
    ut_m();
    ut_s();
    printf("%s", "Now we will insert one more master and slave for it.\n");
    insert_m();
    insert_s();
    printf("%s","Now we will update first master and his slave.\n");
    update_m();
    update_s();
    printf("%s", "Now we will output our tabs.\n");
    ut_m();
    ut_s();
    printf("%s","That's all, thank you for attention.\n");
}

void help(){
    printf("----COMMANDS----\n");
    printf(" [1] get-m\n"
           " [2] get-s\n"
           " [3] del-m\n"
           " [4] del--s\n"
           " [5] update-m\n"
           " [6] update-s\n"
           " [7] insert-m\n"
           " [8] insert-s\n"
           " [9] count-m\n"
           "[10] count-s\n"
           "[11] ut-m\n"
           "[12] ut-s\n"
           "[13] end\n");
    printf("----------enter: ");
}

void Interactive() {
    int action;
    int check = 1;
    while(1) {
        help();
        printf("enter the [action]:\n");
        scanf("%d", &action);
        switch (action) {
            case 1:
                get_m();
                break;
            case 2:
                get_s();
                break;
            case 3:
                del_m();
                break;
            case 4:
                del_s();
                break;
            case 5:
                update_m();
                break;
            case 6:
                update_s();
            case 7:
                insert_m();
                break;
            case 8:
                insert_s();
                break;
            case 9:
                count_m();
                break;
            case 10:
                count_s();
                break;
            case 11:
                ut_m();
                break;
            case 12:
                ut_s();
                break;
            case 13:
                check = 0;
                exit(0);
                break;
            default:
                perror("Number not found");
        }

    }
}

int main() {
    //Interactive();
    Scenario();
    return 0;
}

