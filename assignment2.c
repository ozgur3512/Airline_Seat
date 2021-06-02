#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows, sprow, ais_num;
    int low_i = 1, low_j = 1;
    int array[20][99];
    float score[20][99];
    float family[20][99];
    double score_wo[20][99];
    int ais[5];
    float temp;
    double dist;
    double adjusted;

    printf("Number of rows:"); /* Gathering all the data*/
    scanf("%d", &rows);
    printf("Number of seats per row:");
    scanf("%d", &sprow);

    printf("Number of aisles:");
    scanf("%d", &ais_num);

    if (ais_num != 0) { /* getting aisle array*/

        for (int i = 0; i < ais_num; i++) {
            printf("Add aisle %d after seat:", i + 1);
            scanf("%d", &ais[i]);
        }
    }

    int x = 65;

    for (int i = 1; i <= sprow; i++) { /* adding letters to array*/

        array[0][i] = x;
        x++;
    }

    char c[] = "-";
    for (int i = 1; i <= rows; i++) { /* making the layout*/
        for (int j = 0; j <= sprow; j++) {
            if (j == 0) {
                array[i][j] = (i);
            } else {
                array[i][j] = *c;
            }
        }
    }

    for (int z = 0; z < ais_num; z++) { /* adding aisle index +1 so I can find out exact location */
        ais[z] = ais[z] + 1;
    }
    int temp_ais[5];
    for (int z = 0; z < ais_num; z++) { /* Creating temporary aisle array for one_zero and score arrays to adjust*/
        temp_ais[z] = ais[z];
    }

    for (int corri = 0; corri < ais_num; corri++) { /* adjusting the temporary aisle */
        int corridor_num = 0;
        for (int z = 0; z < ais_num; z++) {

            if (ais[corri] > ais[z]) {
                corridor_num++;
            }
        }

        temp_ais[corri] = temp_ais[corri] + corridor_num;
    }
    int one_zero[25][104];
    int one_zero_wo[25][104]; /* declaring _wo array to not mess with aisles */
    for (int i = 1; i <= rows; i++) { /* making the layout of one_zero array*/
        for (int j = 1; j <= sprow + ais_num; j++) {
            one_zero[i][j] = 2;
            for (int z = 0; z < ais_num; z++) {
                if (j == temp_ais[z]) {
                    one_zero[i][j] = 0;
                    break;
                }
            }
            if (one_zero[i][j] != 0) {
                one_zero[i][j] = 1;
            }
        }
    }

    for (int i = 0; i <= rows; i++) { /* printing the layout*/
        for (int j = 0; j <= sprow; j++) {
            if (j == 0 && i == 0) {
                printf("%c", array[i][j]);

            } else if (j == 0 && i != 0) {

                printf("%d", array[i][j]);

            } else {

                printf("%3c", array[i][j]);
                for (int z = 0; z < ais_num; z++) {
                    if (j + 1 == ais[z]) {
                        printf(" |  |");
                    }
                }
            }
        }
        printf(" \n");
    }
    /* starting of calculations */
    int number_of;
    while (1) { /* Looping the seat reservation */

        printf("The number of people in the reservation\n (0: print current reservations, -1: exit):");
        scanf("%d", &number_of);

        char cross[] = "X";
        char add[] = "+";

        for (int i = 1; i < rows + 1; i++) { /* making +'s x'es from the last reserv*/
            for (int j = 1; j < sprow + 1; j++) {
                if (array[i][j] == *add) {
                    array[i][j] = *cross;
                }
            }
        }

        if (number_of == -1) {
            break;
        } else if (number_of == 0) {
            for (int i = 0; i <= rows; i++) { /* printing the layout*/
                for (int j = 0; j <= sprow; j++) {
                    if (j == 0 && i == 0) {
                        printf("%c", array[i][j]);

                    } else if (j == 0 && i != 0) {
                        printf("%d", array[i][j]);
                    } else {
                        int reped = 0;
                        for (int z = 0; z < ais_num; z++) {
                            if (temp_ais[z] < low_j) {
                                reped++;
                            }
                        }
                        if (i == low_i && j == (low_j - reped)) {

                            printf("%3c", array[i][j]);

                            for (int z = 0; z < ais_num; z++) {
                                if (j + 1 == ais[z]) {
                                    printf(" |  |");
                                }
                            }
                        }

                        else {
                            printf("%3c", array[i][j]);
                            for (int z = 0; z < ais_num; z++) {
                                if (j + 1 == ais[z]) {
                                    printf(" |  |");
                                }
                            }
                        }
                    }
                }
                printf(" \n");
            }

        } else if (number_of == 1) {

            /**/

            for (int i = 1; i < rows + 1; i++) { /* creating score array layout */
                for (int j = 1; j < sprow + 1 + ais_num; j++) {
                    for (int z = 0; z < ais_num; z++) {
                        if (temp_ais[z] == j) {
                            score[i][j] = -20000;
                            break;
                        } else {
                            score[i][j] = 0;
                        }
                    }
                }
            }
            

            for (int i = 1; i <= rows; i++) { /* Calculation of scores */
                for (int j = 1; j <= sprow + ais_num; j++) {
                    if (one_zero[i][j] != 0) {

                        double score1 = 0;
                        for (int a = 1; a <= rows; a++) {
                            for (int b = 1; b <= sprow + ais_num; b++) {
                                if (one_zero[a][b] != 0 && one_zero[a][b] == 2) {

                                    dist = abs(i - a) + (abs(j - b) / 2.0);

                                    if (dist != 0) {
                                        adjusted = 100 - pow(100, (1 / dist));
                                    } else {
                                        adjusted = dist;
                                    }
                                    score1 += adjusted;

                                    score[i][j] = score1;
                                }
                            }
                        }
                    }
                }
            }

            temp = -40000;
            for (int i = 1; i < rows + 1; i++) { /* Finding the highest seat score */
                for (int j = 1; j < sprow + 1 + ais_num; j++) {
                    if (one_zero[i][j] != 2 && one_zero[i][j] != 0) {
                        if (score[i][j] > temp) {

                            temp = score[i][j];
                            low_i = i;
                            low_j = j;
                        }
                    }
                }
            }

            int number_one = 0;
            for (int corr = 1; corr < rows + 1; corr++) { /* calculating how many empty seats*/
                for (int corr2 = 1; corr2 < sprow + 1 + ais_num; corr2++) {
                    if (one_zero[corr][corr2] == 1) {
                        number_one++;
                    }
                }
            }

            if (number_one == 0) { /* Checking if any empty seats */
                printf("\nNo available seats for the requested reservation!\n");
            } else {

                printf("Reserved Seats: ");
                int reped = 0;
                for (int z = 0; z < ais_num; z++) {
                    if (temp_ais[z] < low_j) {
                        reped++;
                    }
                }
                printf("%d%c", low_i, low_j + 64 - reped);
                one_zero[low_i][low_j] = 2; /* Number 2 in one_zero array means reserved seat 1= empty 0= corridor */
                printf("\n");

                for (int i = 0; i <= rows; i++) { /* printing the layout*/
                    for (int j = 0; j <= sprow; j++) {
                        if (j == 0 && i == 0) {
                            printf("%c", array[i][j]);

                        } else if (j == 0 && i != 0) {
                            printf("%d", array[i][j]);
                        } else {
                            int reped = 0;
                            for (int z = 0; z < ais_num; z++) {
                                if (temp_ais[z] < low_j) {
                                    reped++;
                                }
                            }
                            if (i == low_i && j == (low_j - reped)) {
                                if (number_one != 0) {

                                    char add[] = "+";

                                    array[i][j] = *add;
                                } else {
                                    char cross[] = "X";
                                    array[i][j] = *cross;
                                }

                                printf("%3c", array[i][j]);

                                for (int z = 0; z < ais_num; z++) {
                                    if (j + 1 == ais[z]) {
                                        printf(" |  |");
                                    }
                                }
                            }

                            else {
                                printf("%3c", array[i][j]);
                                for (int z = 0; z < ais_num; z++) {
                                    if (j + 1 == ais[z]) {
                                        printf(" |  |");
                                    }
                                }
                            }
                        }
                    }
                    printf(" \n");
                }
            }
        }

        else if (number_of >= 2) {
            if (number_of > sprow) {
                printf("\nNo available seats for the requested reservation!\n");

            }

            else {

                for (int i = 1; i < rows + 1; i++) { /* Score array inserting points -20000 = aisle */
                    for (int j = 1; j < sprow + 1 + ais_num; j++) {
                        for (int z = 0; z < ais_num; z++) {
                            if (temp_ais[z] == j) {
                                score[i][j] = -20000;
                                break;
                            } else {
                                score[i][j] = 0;
                            }
                        }
                    }
                }
                

                for (int i = 1; i <= rows; i++) { /* Calculating score */
                    for (int j = 1; j <= sprow + ais_num; j++) {
                        if (one_zero[i][j] != 0) {

                            double score1 = 0;
                            for (int a = 1; a <= rows; a++) {
                                for (int b = 1; b <= sprow + ais_num; b++) {
                                    if (one_zero[a][b] != 0 && one_zero[a][b] == 2) {

                                        dist = abs(i - a) + (abs(j - b) / 2.0);

                                        if (dist != 0) {
                                            adjusted = 100 - pow(100, (1 / dist));
                                        } else {
                                            adjusted = dist;
                                        }
                                        score1 += adjusted;

                                        score[i][j] = score1;
                                    }
                                }
                            }
                        }
                    }
                }
                int x1 = 1, x2 = 1, j1 = 1, j2 = 1;
                while (1) { /* Creating score array without aisles so I can calculate easily score_wo*/

                    if (score[x1][j1] != -20000) {
                        score_wo[x2][j2] = score[x1][j1];
                    } else {

                        j1++;
                        score_wo[x2][j2] = score[x1][j1];
                    }

                    j1++;
                    j2++;
                    if (j2 == sprow + 1) {
                        x1++;
                        x2++;
                        j1 = 1;
                        j2 = 1;
                    }

                    if (x2 == rows + 1) {
                        break;
                    }
                }
                /* Returning x and js to original values */
                x1 = 1;
                x2 = 1;
                j1 = 1;
                j2 = 1;
                while (1) { /* Creating one_zero array without aisles so I can calculate easily one_zero_wo*/

                    if (one_zero[x1][j1] != 0) {
                        one_zero_wo[x2][j2] = one_zero[x1][j1];
                    } else {

                        j1++;
                        one_zero_wo[x2][j2] = one_zero[x1][j1];
                    }

                    j1++;
                    j2++;
                    if (j2 == sprow + 1) {
                        x1++;
                        x2++;
                        j1 = 1;
                        j2 = 1;
                    }

                    if (x2 == rows + 1) {
                        break;
                    }
                }

                int repeat = sprow - number_of + 1; /* Calculating how many adjacent number_of's in one row */

                for (int i = 1; i < rows + 1; i++) { /* Calculation of seat block score */
                    int repeat_num = 0;
                    int x = 1;
                    for (int j = 1; j < repeat + 1; j++) {
                        float seat_block_score = 0;
                        seat_block_score += score_wo[i][x];
                        for (int z = 1; z < number_of; z++) {
                            seat_block_score += score_wo[i][x + z];
                            if (z == number_of - 1) {
                                x++;
                            }
                        }

                        repeat_num++;
                        family[i][j] = seat_block_score;
                        if (repeat_num == repeat) {
                            break;
                        }
                    }
                }

                /**/
                int reped_before = 0; /* Calculating how many aisles before the chosen j number */
                for (int z = 0; z < ais_num; z++) {
                    if (ais[z] < low_j) {
                        reped_before++;
                    }
                }

                temp = -40000;
                for (int i = 1; i < rows + 1; i++) { /* Calculation of highest seat_block_score*/

                    for (int j = 1; j < repeat + 1; j++) {
                        int reped_before = 0;
                        for (int z = 0; z < ais_num; z++) {
                            if (ais[z] < j) {
                                reped_before++;
                            }
                        }

                        if (one_zero[i][j + reped_before] != 2) {
                            int number_two = 0;
                            int x = 0;
                            for (int b = 1; b <= number_of + x - 1; b++) {
                                if (one_zero[i][j + b + reped_before] == 0) {
                                    x++;
                                }

                                if (one_zero[i][j + b + reped_before] == 2) {
                                    number_two++;
                                }
                            }

                            if (number_two == 0) {
                                if (family[i][j] > temp) {
                                    temp = family[i][j];
                                    low_i = i;
                                    low_j = j;
                                }
                            }
                        }
                    }
                }

                int row_counter = 0;
                for (int i = 1; i < rows + 1; i++) { /*Calculating 1's on each row*/

                    for (int j = 1; j < repeat + 1; j++) {
                        int number_counter = 0;
                        for (int b = 0; b < number_of; b++) {

                            if (one_zero_wo[i][j + b] == 1) {

                                number_counter++;
                            }
                        }

                        if (number_counter == number_of) {
                            row_counter++;
                        }
                    }
                }

                if (row_counter == 0) {
                    printf("\nNo available seats for the requested reservation!\n");

                } else {

                    printf("Reserved Seats: ");
                    reped_before = 0;
                    for (int z = 0; z < ais_num; z++) {
                        if (ais[z] < low_j) {
                            reped_before++;
                        }
                    }
                    for (int a = 0; a < number_of; a++) { /* Printing out reserved seats */
                        printf(" %d%c ", low_i, low_j + 64 + a);
                    }

                    printf("\n");
                    int reped = 0;
                    for (int a = 0; a < number_of + reped; a++) {
                        for (int z = 0; z < ais_num; z++) {
                            if (temp_ais[z] == low_j + a + reped_before) {
                                reped++;
                            }
                        }

                        if (one_zero[low_i][low_j + a + reped_before] == 1) {

                            one_zero[low_i][low_j + a + reped_before] = 2;
                        }
                    }

                    for (int i = 0; i <= rows; i++) { /* printing the layout*/
                        for (int j = 0; j <= sprow; j++) {
                            if (j == 0 && i == 0) {
                                printf("%c", array[i][j]);

                            } else if (j == 0 && i != 0) {
                                printf("%d", array[i][j]);
                            } else {

                                if (i == low_i && j <= low_j + number_of - 1) {
                                    char add[] = "+";
                                    for (int a = 0; a < number_of; a++) {
                                        array[i][low_j + a] = *add;
                                    }

                                    printf("%3c", array[i][j]);

                                    for (int z = 0; z < ais_num; z++) {
                                        if (j + 1 == ais[z]) {
                                            printf(" |  |");
                                        }
                                    }
                                }

                                else {
                                    printf("%3c", array[i][j]);
                                    for (int z = 0; z < ais_num; z++) {
                                        if (j + 1 == ais[z]) {
                                            printf(" |  |");
                                        }
                                    }
                                }
                            }
                        }
                        printf(" \n");
                    }
                }
            }
        }
    }
}
