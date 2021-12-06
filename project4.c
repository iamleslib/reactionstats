#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

int ReadDoublesIntoArray(FILE *fp, double data [], int arrayElements);
bool GenerateStatistics(FILE *fp, double data[], int dataElementsToProcess);

int main () 
{  
    double data [600];
    int arrayElements = sizeof(data)/sizeof(data[0]);
    FILE *filein;   //File pointer to input data file
    FILE *fileout;  //File pointer to output data file

    filein = fopen("C:\\Users\\Leslie I\\Documents\\Visual Studio Code Workspace\\C C++\\reactionstats\\reaction-data2.txt","r");
    fileout = fopen("C:\\Users\\Leslie I\\Documents\\Visual Studio Code Workspace\\C C++\\reactionstats\\stats.txt","w");
    
    if((filein == NULL) || (fileout == NULL)) {
        printf("Error: Can't open file.");    //Error message for unsuccessful file open
        return -1;
    }

    int n = ReadDoublesIntoArray(filein, data, arrayElements);
    fclose(filein);
    printf("Stats:\n----------------------------\nReaction Count = %i", n);
    printf("\nFirst reaction rate = %lf", data[0]);
    printf(" moles/sec\nLast reaction rate = %lf", data[n-1]);
    printf(" moles/sec\n");

    if(ReadDoublesIntoArray > 0) {
        if (GenerateStatistics(fileout, data, n) == true) {
            fclose(fileout);
            return 0;
        }
    }
    else {
        printf("Error.");
        return -1;
    }
} // END main function

int ReadDoublesIntoArray(FILE *fp, double data [], int arrayElements)
{
    if((fp != NULL) || (data != NULL) || (arrayElements >= 1)) {
        int count = 0;  //Count of successful times data is read from file
        for(int i = 0; i < arrayElements; i++) {
            double temp;
            if(fscanf(fp,"%lf", &temp) == 1) {
                data[i] = temp;
                count++;
            }
            else {
                break;
            }
        }
        return count;
    }
    else {
        return -1; 
    }
    
}

bool GenerateStatistics(FILE *fp, double data[], int dataElementsToProcess)
{
    if((fp != NULL) || (data != NULL) || (dataElementsToProcess >= 1)) {
        double sum = 0;
        double maxval = 0;
        double minval = DBL_MAX;
        double mean, variance, stdev;

        for(int i = 0; i < dataElementsToProcess; i++) {
            sum += data[i];
            maxval = fmax(data[i], maxval);
            minval = fmin(data[i], minval);
        }
        mean = sum/dataElementsToProcess;
        sum = 0;
        for(int j = 0; j < dataElementsToProcess; j++) {
            sum += pow((data[j] - mean),2);
        }
        variance = sum/dataElementsToProcess;
        stdev = sqrt(variance);

        fprintf(fp, "%s", "Reaction Rate Statistics: \n\nNumber of experiements = ");
        fprintf(fp, "%i", dataElementsToProcess);
        fprintf(fp, "%s", "\nMinimum rate = ");
        fprintf(fp, "%lf", minval);
        fprintf(fp, "%s", " moles/sec\nMaximum rate = ");
        fprintf(fp, "%lf", maxval);
        fprintf(fp, "%s", " moles/sec\nArithmetic mean = ");
        fprintf(fp, "%lf", mean);
        fprintf(fp, "%s", " moles/sec\nVariance = ");
        fprintf(fp, "%lf", variance);
        fprintf(fp, "%s", "\nStandard deviation = ");
        fprintf(fp, "%lf", stdev);
        fprintf(fp, "%s", " moles/sec\n\n");
        
        return true;
    }
    else {
        return false;
    }

    

}