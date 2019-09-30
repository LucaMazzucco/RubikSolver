
/* RUBIK'S CUBE SOLVER
*
*   created from Luca 11/10/2017
*
*
*
* - MOSSE APPLICABILI SUL CUBO
* LC -> LEFT CLOCKWISE
* LA -> LEFT ANTICLOCKWISE
* RC -> RIGHT CLOCKWISE
* RA -> RIGHT ANTICLOCKWISE
* UC -> UP CLOCKWISE
* UA -> UP ANTICLOCKWISE
* DC -> DOWN CLOCKWISE
* DA -> DOWN ANTICLOCKWISE
* FC -> FRONT CLOCKWISE
* FA -> FRONT ANTICLOCKWISE
* BC -> BACK CLOCKWISE
* BA -> BACK ANTICLOCKWISE
*
* - CUBE RAPPRESENTATION
*
*
*       |- - -|
*       |  O  |
* |- - -|- - -|- - -|- - -|
* |  G  |  W     B     Y  |
* |- - -|- - -|- - -|- - -|
*       |  R  |
*       |- - -|
*
* ASCII CODE FOR COLOR
* B -> 66
* G -> 71
* O -> 79
* R -> 82
* W -> 87
* Y -> 89
*
*/
#include <stdio.h>
#include <stdlib.h>

void cube_init();
void cube_reset();
void show_cube();
void cube_set();
void cube_mix();
void cube_solve_casual();
void cube_solve_tree(int deep, int deepmax);
void cube_solve_tree_with_heuristic(int deep, int deepmax, int prec);

int  cube_evaluation();
void perform_move(int move);
void perform_opposite_move(int move);
void move_LC();
void move_LA();
void move_RC();
void move_RA();
void move_UC();
void move_UA();
void move_DC();
void move_DA();
void move_FC();
void move_FA();
void move_BC();
void move_BA();




int cube[9][12];
int solved[9][12];
int best_evaluation = 0, iter2deep = 0, percentuage=0, beta, iterations  = 0;

int main()
{
    int move;


    cube_init();
    cube_reset();

    while(1){
        system("cls");
        printf("RUBIK'S CUBE SOLVER\n\n");
        show_cube();
        printf("\nChoose an operation:\n1 - Left clockwise    2 - Left anticlockwise\n3 - Right clockwise   4 - Right anticlockwise\n5 - Up clockwise      6 - Up anticlockwise\n7 - Down clockwise    8 - Down anticlockwise\n9 - Front clockwise  10 - Front anticlockwise\n11 - Back clockwise  12 - Back anticlockwise\n-----------------------------------------------\n13 - SET UP CUBE     14 - SOLVE\n15 - RESET CUBE      16 - MIX CUBE\nEnter:");
        scanf("%d", &move);
        perform_move(move);
    }
    return 0;
}

void move_LC(){

    int temp;
    temp = cube[3][1];
    cube[3][1] = cube[4][0];
    cube[4][0] = cube[5][1];
    cube[5][1] = cube[4][2];
    cube[4][2] = temp;

    temp = cube[3][0];
    cube[3][0] = cube[5][0];
    cube[5][0] = cube[5][2];
    cube[5][2] = cube[3][2];
    cube[3][2] = temp;

    temp = cube[0][3];
    cube[0][3] = cube[5][11];
    cube[5][11] = cube[6][3];
    cube[6][3] = cube[3][3];
    cube[3][3] = temp;

    temp = cube[1][3];
    cube[1][3] = cube[4][11];
    cube[4][11] = cube[7][3];
    cube[7][3] = cube[4][3];
    cube[4][3] = temp;

    temp = cube[2][3];
    cube[2][3] = cube[3][11];
    cube[3][11] = cube[8][3];
    cube[8][3] = cube[5][3];
    cube[5][3] = temp;

    return;
}

void move_LA(){

    move_LC();
    move_LC();
    move_LC();
    return;
}
void move_RC(){

    int temp;
    temp = cube[3][7];
    cube[3][7] = cube[4][6];
    cube[4][6] = cube[5][7];
    cube[5][7] = cube[4][8];
    cube[4][8] = temp;

    temp = cube[3][6];
    cube[3][6] = cube[5][6];
    cube[5][6] = cube[5][8];
    cube[5][8] = cube[3][8];
    cube[3][8] = temp;

    temp = cube[0][5];
    cube[0][5] = cube[3][5];
    cube[3][5] = cube[6][5];
    cube[6][5] = cube[5][9];
    cube[5][9] = temp;

    temp = cube[1][5];
    cube[1][5] = cube[4][5];
    cube[4][5] = cube[7][5];
    cube[7][5] = cube[4][9];
    cube[4][9] = temp;

    temp = cube[2][5];
    cube[2][5] = cube[5][5];
    cube[5][5] = cube[8][5];
    cube[8][5] = cube[3][9];
    cube[3][9] = temp;

    return;
}
void move_RA(){

    move_RC();
    move_RC();
    move_RC();
    return;
}
void move_UC(){

    int temp;
    temp = cube[3][4];
    cube[3][4] = cube[4][3];
    cube[4][3] = cube[5][4];
    cube[5][4] = cube[4][5];
    cube[4][5] = temp;

    temp = cube[3][3];
    cube[3][3] = cube[5][3];
    cube[5][3] = cube[5][5];
    cube[5][5] = cube[3][5];
    cube[3][5] = temp;

    temp = cube[2][3];
    cube[2][3] = cube[5][2];
    cube[5][2] = cube[6][5];
    cube[6][5] = cube[3][6];
    cube[3][6] = temp;

    temp = cube[2][4];
    cube[2][4] = cube[4][2];
    cube[4][2] = cube[6][4];
    cube[6][4] = cube[4][6];
    cube[4][6] = temp;

    temp = cube[2][5];
    cube[2][5] = cube[3][2];
    cube[3][2] = cube[6][3];
    cube[6][3] = cube[5][6];
    cube[5][6] = temp;

    return;
}
void move_UA(){

    move_UC();
    move_UC();
    move_UC();
    return;
}
void move_DC(){

   move_DA();
   move_DA();
   move_DA();
    return;
}
void move_DA(){

     int temp;
    temp = cube[3][9];
    cube[3][9] = cube[5][9];
    cube[5][9] = cube[5][11];
    cube[5][11] = cube[3][11];
    cube[3][11] = temp;

    temp = cube[4][9];
    cube[4][9] = cube[5][10];
    cube[5][10] = cube[4][11];
    cube[4][11] = cube[3][10];
    cube[3][10] = temp;

    temp = cube[3][8];
    cube[3][8] = cube[8][5];
    cube[8][5] = cube[5][0];
    cube[5][0] = cube[0][3];
    cube[0][3] = temp;

    temp = cube[4][8];
    cube[4][8] = cube[8][4];
    cube[8][4] = cube[4][0];
    cube[4][0] = cube[0][4];
    cube[0][4] = temp;

    temp = cube[5][8];
    cube[5][8] = cube[8][3];
    cube[8][3] = cube[3][0];
    cube[3][0] = cube[0][5];
    cube[0][5] = temp;

    return;
}
void move_FC(){

    int temp;
    temp = cube[6][4];
    cube[6][4] = cube[7][3];
    cube[7][3] = cube[8][4];
    cube[8][4] = cube[7][5];
    cube[7][5] = temp;

    temp = cube[6][3];
    cube[6][3] = cube[8][3];
    cube[8][3] = cube[8][5];
    cube[8][5] = cube[6][5];
    cube[6][5] = temp;

    temp = cube[5][3];
    cube[5][3] = cube[5][0];
    cube[5][0] = cube[5][9];
    cube[5][9] = cube[5][6];
    cube[5][6] = temp;

    temp = cube[5][4];
    cube[5][4] = cube[5][1];
    cube[5][1] = cube[5][10];
    cube[5][10] = cube[5][7];
    cube[5][7] = temp;

    temp = cube[5][5];
    cube[5][5] = cube[5][2];
    cube[5][2] = cube[5][11];
    cube[5][11] = cube[5][8];
    cube[5][8] = temp;
    return;
}
void move_FA(){

    move_FC();
    move_FC();
    move_FC();
    return;
}
void move_BC(){

     int temp;
    temp = cube[0][4];
    cube[0][4] = cube[1][3];
    cube[1][3] = cube[2][4];
    cube[2][4] = cube[1][5];
    cube[1][5] = temp;

    temp = cube[0][3];
    cube[0][3] = cube[2][3];
    cube[2][3] = cube[2][5];
    cube[2][5] = cube[0][5];
    cube[0][5] = temp;

    temp = cube[3][3];
    cube[3][3] = cube[3][6];
    cube[3][6] = cube[3][9];
    cube[3][9] = cube[3][0];
    cube[3][0] = temp;

    temp = cube[3][4];
    cube[3][4] = cube[3][7];
    cube[3][7] = cube[3][10];
    cube[3][10] = cube[3][1];
    cube[3][1] = temp;

    temp = cube[3][5];
    cube[3][5] = cube[3][8];
    cube[3][8] = cube[3][11];
    cube[3][11] = cube[3][2];
    cube[3][2] = temp;

    return;
}
void move_BA(){
    move_BC();
    move_BC();
    move_BC();

    return;
}

void cube_init(){

    int i = 0, j=0;
    for(i=0; i<9; i++)
        for(j=0; j<12; j++){
            cube[i][j] = 0;
            solved[i][j];
        }

    return;
}

void cube_reset(){

    int i, j;
    for(i=0; i<3; i++)      //ORANGE FACE
        for(j=3; j<6; j++){
            cube[i][j]=79;
            solved[i][j]=79;
        }
    for(i=3; i<6; i++)      //GREEN FACE
        for(j=0; j<3; j++){
            cube[i][j]=71;
            solved[i][j]=71;
        }
    for(i=3; i<6; i++)      //WHITE FACE
        for(j=3; j<6; j++){
            cube[i][j]=87;
            solved[i][j]=87;
        }
    for(i=3; i<6; i++)      //BLU FACE
        for(j=6; j<9; j++){
            cube[i][j]=66;
            solved[i][j]=66;
        }
    for(i=3; i<6; i++)      //YELLOW FACE
        for(j=9; j<12; j++){
            cube[i][j]=89;
            solved[i][j]=89;
        }
    for(i=6; i<9; i++)      //RED FACE
        for(j=3; j<6; j++){
            cube[i][j]=82;
            solved[i][j]=82;
        }

}

void show_cube(){

 int i = 0, j=0;
 printf(" ");
 for(i=0; i<9; i++){
    for(j=0; j<12; j++)
        printf("%c ", cube[i][j]);

    printf("\n ");
 }

}

void cube_set(){
    int i, j;
    char value;
    for(i=0; i<9; i++){
        for(j=0; j<12; j++){
            if(cube[i][j]!=0){
                system("cls");
                printf("SET UP CUBE PROCEDURE\n");
                show_cube();
                printf("\nInsert value position [%d, %d] (Q - interrupt  S - specific position):", i, j);
                fflush(stdin);
                scanf("%c", &value);
                if(value == 'S'){
                        printf("Insert vertical position: ");
                        scanf("%d", &i);
                        printf("Insert horizontal position: ");
                        scanf("%d", &j);
                        printf("Insert value: ");
                        fflush(stdin);
                        scanf("%c", &value);

                }

                switch(value){
                    case 'B': cube[i][j] = 66; break;
                    case 'G': cube[i][j] = 71; break;
                    case 'O': cube[i][j] = 79; break;
                    case 'R': cube[i][j] = 82; break;
                    case 'W': cube[i][j] = 87; break;
                    case 'Y': cube[i][j] = 89; break;
                    case 'Q': return;

                    default: break;
                }



            }
        }
    }

return;
}
void cube_mix(){

    int i, ran;
    for(i=0; i<100; i++){
        ran = rand()%12 +1;
        perform_move(ran);
    }



}

int cube_evaluation(){
    int i, j, evaluation =0;
    for(i=0; i<3; i++)
        for(j=3; j<6; j++)
            if(cube[i][j] == solved[i][j])
                evaluation++;
     for(i=3; i<6; i++)
        for(j=0; j<12; j++)
            if(cube[i][j] == solved[i][j])
                evaluation++;
     for(i=6; i<9; i++)
        for(j=3; j<6; j++)
            if(cube[i][j] == solved[i][j])
                evaluation++;

    return evaluation;
}

int cube_evaluation_1_layer(){
    int i, j, evaluation =0;

     for(i=2; i<7; i++)
        for(j=2; j<7; j++)
            if(cube[i][j] == solved[i][j])
                evaluation++;

    return evaluation;
}


void cube_solve_casual(){

    int i, ran, evaluation, bestev = 0;
    for(i=0; i<90000000; i++){
        ran = rand()%12 +1;
        perform_move(ran);
        evaluation = cube_evaluation();
        if(evaluation > bestev){
            bestev = evaluation;
            system("cls");
            printf("Casual solver\n");
            show_cube();
            printf("Best evaluation found (MAX 54): %d", bestev);
            if( bestev == 54) break;

        }
    }
    printf("Press a key to terminate: ");
    scanf("%c", &i);

return;
}

void cube_solve_tree(int deep, int deepmax){

    int d, i, e, dm;
    dm = deepmax;
    d = deep;
    d++;
    e = cube_evaluation();
    if(e>=53){
        system("cls");
        show_cube();
        printf("\nPress a key to terminate: "); fflush(stdin);
        scanf("%c", &i);
        return;
    }
    if(d> deepmax){
            if( e> best_evaluation){
                best_evaluation = e;
                system("cls");
                printf("Tree sequential solver\n");
                show_cube();
                printf("\nBest evaluation found: %d", best_evaluation);
            }
            return;
    }
    if(best_evaluation>=53){
        system("cls");
        show_cube();
        printf("\nPress a key to terminate: "); fflush(stdin);
        scanf("%c", &i);
        return;
    }
    for(i = 1; i<13; i++){
        perform_move(i);
        cube_solve_tree(d, dm);

        perform_opposite_move(i);
    }

    if(d == 1){
        system("cls");
         printf("\nBest evaluation found: %d", best_evaluation);
        printf("\nPress a key to terminate: ");
        fflush(stdin);
        scanf("%c", &i);

    }

return;
}

void cube_solve_tree_with_heuristic(int deep, int deepmax, int prec){

int d, i,j, temp,  e, dm, move_order[12], evaluations[12], prev;
    prev = prec;
    dm = deepmax;
    d = deep;
    d++;
    e = cube_evaluation();
    if(e>=53){
        system("cls");
        printf("SOLUTION FOUND!!!\n");
        show_cube();
        printf("\nPress a key to terminate: "); fflush(stdin);
        scanf("%c", &i);
        return;
    }
    if(d> deepmax){
            if( e> best_evaluation){
                best_evaluation = e;
                system("cls");
                printf("Tree sequential solver with heuristic\n");
                show_cube();
                printf("\nBest evaluation found: %d ", best_evaluation);
            }
            return;
    }
    if(best_evaluation>=53){
        system("cls");
        show_cube();
        printf("\nPress a key to terminate: "); fflush(stdin);
        scanf("%c", &i);
        return;
    }

    for(i = 1; i<13; i++){
        perform_move(i);
        evaluations[i-1] = cube_evaluation();
        perform_opposite_move(i);
    }
    for(i = 1; i<13; i++) move_order[i] = i;

    for( i = 0; i < 11; i++) {
        for (j = i+1; j < 12; j++)
            if (evaluations[i] > evaluations[j]) {
                temp = evaluations[i];
                evaluations[i] = evaluations[j];
                evaluations[j] = temp;

                temp = move_order[i];
                move_order[i] = move_order[j];
                move_order[j] = temp;
            }
        }

    for(i = 0; i<beta; i++){
        if(move_order[i]!=get_opposite_move(prev)){
            perform_move(move_order[i]);
            cube_solve_tree_with_heuristic(d, dm, move_order[i]);
            perform_opposite_move(move_order[i]);
        }
    }

    if(d == 1){
        system("cls");
         printf("\nBest evaluation found: %d", best_evaluation);
        printf("\nPress a key to terminate: ");
        fflush(stdin);
        scanf("%c", &i);

    }

return;


}


void perform_move(int move){

    switch(move){
            case 1:
                move_LC();  break;
            case 2:
                move_LA();  break;
            case 3:
                move_RC();  break;
            case 4:
                move_RA();  break;
            case 5:
                move_UC();  break;
            case 6:
                move_UA();  break;
            case 7:
                move_DC();  break;
            case 8:
                move_DA();  break;
            case 9:
                move_FC();  break;
            case 10:
                move_FA();  break;
            case 11:
                move_BC();  break;
            case 12:
                move_BA();  break;
            case 13:
                cube_set(); break;
            case 14:
                system("cls");
                printf("Choose a method to solve the cube:\n1 - Casual\n2 - Tree entire sequential visit (optional: deep)\n3 - Tree visit with heuristic (optional: deep, best beta)\nEnter: ");
                int method;
                best_evaluation = 0;
                scanf("%d", &method);
                int deep;
                switch(method){
                    case 1: cube_solve_casual();
                            break;
                    case 2: printf("Choose max deep: ");
                            fflush(stdin);
                            scanf("%d" ,&deep);
                            cube_solve_tree(0, deep);
                            break;

                    case 3: printf("Choose max deep: ");
                            fflush(stdin);
                            scanf("%d" ,&deep);
                            printf("Choose beta(1 - 12): ");
                            fflush(stdin);
                            scanf("%d" ,&beta);
                            cube_solve_tree_with_heuristic(0, deep, -1);
                            break;
                }
                break;
            case 15:
                cube_reset(); break;
            case 16:
                cube_mix();   break;
            default:          break;
        }
        return;
}

void perform_opposite_move(int move){

    switch(move){
            case 1:
                move_LA();  break;
            case 2:
                move_LC();  break;
            case 3:
                move_RA();  break;
            case 4:
                move_RC();  break;
            case 5:
                move_UA();  break;
            case 6:
                move_UC();  break;
            case 7:
                move_DA();  break;
            case 8:
                move_DC();  break;
            case 9:
                move_FA();  break;
            case 10:
                move_FC();  break;
            case 11:
                move_BA();  break;
            case 12:
                move_BC();  break;
            default:          break;
        }
        return;
}

int get_opposite_move(int move){

    switch(move){
            case 1:
                return 2;
            case 2:
                return 1;
            case 3:
                return 4;
            case 4:
                return 3;
            case 5:
                return 6;
            case 6:
                return 5;
            case 7:
                return 8;
            case 8:
               return 7;
            case 9:
                return 10;
            case 10:
                return 9;
            case 11:
                return 12;
            case 12:
                return 11;
            default:
                return -1;
        }
        return;
}
