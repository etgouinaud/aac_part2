// This algorithm has been inspired from the book Numerical Recipes in C

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/*
 * Print an array
 */
void printTab(float * tab,int n){
    int i;
    printf("[ ");
    for(i = 0 ; i < n-1 ; i++){
        printf("%f, ",tab[i]);
    }
    printf("%f]\n", tab[i]);
}

/*
 * Print an array using exponent notation
 */
void printTabExponent(float * tab,int n){
    int i;
    printf("[ ");
    for(i = 0 ; i < n-1 ; i++){
        printf("%e, ",tab[i]);
    }
    printf("%e]\n", tab[i]);
}

/*
* Initializes the array randomly.
*/
void initRandTab(float * tab, int n){
    srand(n);
    for(int i = 0 ; i < n ; i++){
            //tab[i] = rand() * 1.0;
            tab[i] = n - i ;//* rand()%10;
        }
}

/*
 * This function is made to heapsort an array.
 * The principle is to isolate the bigger value and at the end of a cycle you put it at the end of the array.
 * This allow to have an N*log2(N) complexity, because when you put a value at the end the algortihm don't analyse it again.
 * The result could be compare to heapsort from the <stdlib.h> library.
 */
void myheapsort(float *tab, int n){
    int i;
    int boucle = 0;
    float tmp;
    while (boucle < n - 1){
        i = 0;
        // Try to isolate the biggest value at the start
        while (i < n - boucle){
            if (tab[i] > tab[(i - 1) / 2]){
                tmp = tab[i];
                tab[i] = tab[(i - 1) / 2];
                tab[(i - 1) / 2] = tmp;
                i = 0;
                continue;
            }
            i++;
        }
        // We put the biggest value at the end
        tmp = tab[0];
        tab[0] = tab[n - boucle - 1];
        tab[n - boucle - 1] = tmp;
        boucle++;
    }
}

/*
 * Test heap sort algorithm with an empty tab
 */
void testHeapSortEmpty(){
    float tab[0] = {};

    printTab(tab, 0);
    myheapsort(tab, 0);
    printTab(tab, 0);
}

/*
 * Test heap sort algorithm with one element
 */
void testHeapSortOne(){
    float tab[1] = {8.0};

    printTab(tab, 1);
    myheapsort(tab, 1);
    printTab(tab, 1);
}

/*
 * Test heap sort algorithm with two elements
 */
void testHeapSortTwo(){
    float tab[2] = {8.0, -16.0};

    printTab(tab, 2);
    myheapsort(tab, 2);
    printTab(tab, 2);
}

/*
 * Test heap sort algorithm with duplicated elements
 */
void testHeapSortDuplicates(){
    float tab[5] = {2.0, 5.5, 5.5, -3.0, 2.0};

    printTab(tab, 5);
    myheapsort(tab, 5);
    printTab(tab, 5);
}

/*
 * Test heap sort algorithm with only negative values
 */
void testHeapSortNegative(){
    float tab[5] = {-1.2, -0.6, -2.5, -3.3, -6.1};

    printTab(tab, 5);
    myheapsort(tab, 5);
    printTab(tab, 5);
}

/*
 * Test heap sort algorithm with positive values
 */
void testHeapSortPositive(){
    float tab[5] = {1.2, 0.6, 2.5, 3.3, 6.1};

    printTab(tab, 5);
    myheapsort(tab, 5);
    printTab(tab, 5);
}

/*
 * Test heap sort algorithm with bounds values
 */
void testHeapSortBounds(){
    float tab[4] = {FLT_MAX, -FLT_MAX, -FLT_MIN, FLT_MIN};
    printTabExponent(tab, 4);
    myheapsort(tab, 4);
    printTabExponent(tab, 4);
}

/*
 * Test heap sort algorithm with already sorted values
 */
void testHeapSortSorted(){
    float tab[5] = {-5.0, -2.3, 0.0, 5.0, 36.0};
    printTab(tab, 5);
    myheapsort(tab, 5);
    printTab(tab, 5);
}

int main(){
    testHeapSortEmpty();
    testHeapSortOne();
    testHeapSortTwo();
    testHeapSortDuplicates();
    testHeapSortNegative();
    testHeapSortPositive();
    testHeapSortBounds();
    testHeapSortSorted();
}