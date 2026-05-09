#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <immintrin.h>
#include <string.h>

#define TILE_SIZE 8

struct SoA {
    alignas(32) int32_t values[8][TILE_SIZE]; //Alignas sounds like a high level spell tbh, also this is a box within a box or smh
};

void print_v256(__m256i v, const char* label) { //dont mind the helper, should probably remove it but ... nah i'm good
    int temp[8];
    _mm256_store_si256((__m256i*)temp, v);
    printf("%-10s: [ %d, %d, %d, %d, %d, %d, %d, %d ]\n", 
            label, temp[0], temp[1], temp[2], temp[3], 
            temp[4], temp[5], temp[6], temp[7]);
}


int32_t multiplySIMD(int32_t *a, int32_t *b) {
    //Operation block : Multilply LOW values of a and b -> store in result
    __m256i v1 = _mm256_load_si256((__m256i*)a);
    __m256i v2 = _mm256_load_si256((__m256i*)b);

    __m256i result = _mm256_mullo_epi32(v1,v2); //Doth shall multiply, curse the one who decided "lo" was a good thing.

    print_v256(result, "Register"); //checker lmao

    //store result in temp then add values to get proper matrix output
    alignas(32) int32_t temp[TILE_SIZE];
    _mm256_store_si256((__m256i*)temp, result);

    int32_t val = 0;
    for(int32_t i=0; i<TILE_SIZE; i++) {
        val += temp[i];
    }
    return val;
}


int main() {
    printf("This is an AVX2 SIMD test for N*N square matrices! (and a cry for help)\n"); //still true

    
    alignas(32) struct SoA Bigarr[2];
    int32_t n = 0;
    //printf("Please enter the first two lines (ie : a1,1,a2,1)\n");

    printf("Please enter matrix size (warning : square matrices up to 8*8 only) : \n"); //Excuse me? no one told me in/out was 80% of the pain in this code!!!
    scanf("%d",&n);
    memset(Bigarr,0, sizeof(Bigarr)); //zeroes bigarr
    int32_t results[n*n];

    for (int32_t i =0; i < n; i++){
        printf("Please enter values of matrix A row %d (Ie: 1,2,...): ",i);
        for (int32_t j=0;j<n; j++){
            scanf("%d",&Bigarr[0].values[i][j]); //input for first matrix (row major)
        }
    }

    for (int32_t i = 0; i<n; i++) {
        printf("Please enter values of matrix B row %d: ",i);
        for (int32_t j = 0; j<n;j++){
            scanf("%d",&Bigarr[1].values[j][i]); //input for 2nd matrix, dont tell them they've been played but its row major in that gets stored as col major
        }
    }

    for(int32_t i = 0; i < n; i++) {
        for(int32_t j = 0; j < n; j++) {
            results[i*n + j] = multiplySIMD( // Multiplication loop :3
            Bigarr[0].values[i],
            Bigarr[1].values[j]);
        }
    } 


    printf("Output of matrix %d²: \n",n);
    for(int32_t i = 0; i < n; i++) {
    printf("[");
    for(int32_t j = 0; j < n; j++)
        printf("%d ", results[i*n + j]); //Yes, YES its multiple O(n²) nightmares but i'm just a guy trying to do stuff without reading 5million pages
    printf("]\n");
    }   

    return 0;
}
// Pretty good for 80 lines, full cache locality with -O2 (fits in L1) and no leaks !