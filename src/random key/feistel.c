#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bintochar(const char *binaryString) {
    int num = strtol(binaryString, NULL, 2); 
    printf("  %c", (char)num); 
    FILE *outputFile = fopen("output.txt", "a+");
    fprintf(outputFile,"%c",num);
    fclose(outputFile);
}

void charToBinary(char c, char *binaryString) {
    int asciiValue = (int)c;
    for (int i = 7; i >= 0; --i) {
        binaryString[i] = (asciiValue % 2) + '0';
        asciiValue /= 2;
    }
    binaryString[8] = '\0'; 
}

char* strtobin(const char *input) {
    int inputLength = strlen(input);
    char binaryChar[9];
    char* binaryOutput = (char*)malloc((inputLength * 8 + 1) * sizeof(char));
    
    binaryOutput[0] = '\0'; 
    
    for (int i = 0; i < inputLength; ++i) {
        charToBinary(input[i], binaryChar);
        strcat(binaryOutput, binaryChar);
    }
    return binaryOutput;
}
void feistelCipher(char *block, int blocksize, char *key) {
    int i;
    char L1[5], L2[5], L3[5], R1[5], R2[5], R3[5], temp[5], F1[5], F2[5], k1[5], k2[5];

    strncpy(L1, block, blocksize / 2);
    strncpy(R1, block + blocksize / 2, blocksize / 2);
    L1[blocksize / 2] = '\0';
    R1[blocksize / 2] = '\0';

    strncpy(k1, key, blocksize / 2);
    strncpy(k2, key + blocksize / 2, blocksize / 2);

    // Round 1
    for (i = 0; i < blocksize / 2; i++) F1[i] = ((k1[i] - '0') ^ (R1[i] - '0')) + '0';
    strcpy(temp, R1);
    strcpy(L2, temp);
    for (i = 0; i < blocksize / 2; i++) R2[i] = ((F1[i] - '0') ^ (L1[i] - '0')) + '0';

    // Round 2
    for (i = 0; i < blocksize / 2; i++) F2[i] = ((k2[i] - '0') ^ (R2[i] - '0')) + '0';
    strcpy(temp, R2);
    strcpy(L3, temp);
    for (i = 0; i < blocksize / 2; i++) R3[i] = ((F2[i] - '0') ^ (L2[i] - '0')) + '0';

    // Concatenate R3 and L3 to form the Cipherblock
    char Cipherblock[blocksize + 1];
    strcpy(Cipherblock, R3);
    strcat(Cipherblock, L3);
    Cipherblock[blocksize] = '\0';
    printf("%s\t\t",Cipherblock);
    bintochar(Cipherblock);

}

char* generateRandomKey() {
    char* key = (char*)malloc(9 * sizeof(char)); 
    srand(time(NULL)); 
    for (int i = 0; i < 8; ++i) {
        key[i] = (rand() % 2) + '0'; 
    }
    key[8] = '\0';
    return key;
}

int main() {
    char inputFileName[100], word[100];
    printf("Enter the filename containing the plaintext: ");
    scanf("%s", inputFileName);

    FILE *inputFile = fopen(inputFileName, "r");
   

    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char key[] = "10011010";
    int blocksize = 8;

    printf("Plain Text Block\tCipher Text Block\tChar\n");

    while (fscanf(inputFile, "%s", word) != EOF) {
        char *PT = strtobin(word);

        int totalBlocks = strlen(PT) / blocksize;
        for (int i = 0; i < totalBlocks; ++i) {
            char block[9];
            strncpy(block, PT + i * blocksize, blocksize);
            block[blocksize] = '\0';
            printf("\n%s\t\t", block);
            feistelCipher(block, blocksize, key);
        }
        free(PT);
    }
    fclose(inputFile);
    return 0;
}