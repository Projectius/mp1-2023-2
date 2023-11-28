#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include <io.h>  
#include <time.h>  
#include <omp.h>
//#include<string.h>

typedef struct {
    long size;
    char* name;
}file;

enum Stype
{
    size = 0,
    name = 1,
    //time = 2
};

int cmp(file a, file b, enum Stype type, int rev) {
    int ans = 0;
    switch (type) {


    case size:
        if (rev)
            ans = a.size > b.size;
        else
            ans = a.size < b.size;
        break;

    case name:
        if (rev)
            ans = strcmp(a.name, b.name);
        else
            ans = -strcmp(a.name, b.name);
        break;
    }
}


void bubbleSort(file a[], long size, enum Stype type, int rev) {
    long i, j;
    file x;

    for (i = 0; i < size; i++) {            // i - ����� �������
        for (j = size - 1; j > i; j--) {     // ���������� ���� �������
            if (a[j - 1].size > a[j].size) {
                x = a[j - 1]; a[j - 1] = a[j]; a[j] = x;
            }
        }
    }
}

void selectSort(file a[], long size) {
    long i, j, k;
    file x;

    for (i = 0; i < size; i++) {   	// i - ����� �������� ����
        k = i; x = a[i];

        for (j = i + 1; j < size; j++)	// ���� ������ ����������� ��������
            if (a[j].size < x.size) {
                k = j; x = a[j];	        // k - ������ ����������� ��������
            }

        a[k] = a[i]; a[i] = x;   	// ������ ������� ���������� � a[i]
    }
}

void merge(file a[], long lb, long split, long ub) {
    // ������� ������� ������ �� ������ ������������������ a[lb]...a[split]
    long pos1 = lb;

    // ������� ������� ������ �� ������ ������������������ a[split+1]...a[ub]
    long pos2 = split + 1;

    // ������� ������� ������ � temp
    long pos3 = 0;

    file* temp = (file*)malloc((ub - lb + 1) * sizeof(file));

    // ���� �������, ���� ���� ���� ���� ������� � ������ ������������������
    while (pos1 <= split && pos2 <= ub) {
        if (a[pos1].size < a[pos2].size)
            temp[pos3++] = a[pos1++];
        else
            temp[pos3++] = a[pos2++];
    }

    // ���� ������������������ ����������� - 
    // ���������� ������� ������ � ����� ������
    while (pos2 <= ub)   // ���� ������ ������������������ �������
        temp[pos3++] = a[pos2++];
    while (pos1 <= split)  // ���� ������ ������������������ �������
        temp[pos3++] = a[pos1++];

    // ����������� ����� temp � a[lb]...a[ub]
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        a[lb + pos3] = temp[pos3];

    free(temp);
}

void mergeSort(file a[], long lb, long ub) {
    long split;

    if (lb < ub) {
        split = (lb + ub) / 2;

        mergeSort(a, lb, split);
        mergeSort(a, split + 1, ub);
        merge(a, lb, split, ub);
    }
}

void callMergeSort(file a[], long size) {
    mergeSort(a, 0, size-1);
}

void swap(file* a, file* b) {
    file temp = *a;
    *a = *b;
    *b = temp;
}

long partition(file arr[], long low, long high) {
    long pivot = arr[high].size;
    long i = (low - 1);

    for (long j = low; j <= high - 1; j++) {
        // ���������� �� ���� size
        if (arr[j].size < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortR(file arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);

        quickSortR(arr, low, pi - 1);
        quickSortR(arr, pi + 1, high);
    }
}

void callquickSortR(file a[], long size) {
    quickSortR(a, 0, size-1);
}

void insertSort(file a[], long size) {
    file x;
    long i, j;

    for (i = 0; i < size; i++) {  // ���� ��������, i - ����� �������
        x = a[i];

        // ����� ����� �������� � ������� ������������������ 
        for (j = i - 1; j >= 0 && a[j].size > x.size; j--)
            a[j + 1] = a[j];  	// �������� ������� �������, ���� �� �����

        // ����� �������, �������� �������
        a[j + 1] = x;
    }
}



void printfiles(file* f, int count) {
    printf("FILES SORTED\n");
    for (int i = 0; i < count;i++) {
        //printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
        //printf("%s %d\n", f[i].name, f[i].size);
        printf("%-25.25s %25u\n", f[i].name, f[i].size);
    }
}

//void printsarr(char** arr, int size) {
//    for (int i = 0; i < size;i++) {
//        printf("%s\n", arr[i]);
//    }
//}

void extend(file** arr, long* cap) {
    file* narr = (file*)realloc(*arr, *cap*2*sizeof(file));
    if (narr) {
        *arr = narr;
        *cap *= 2;
    }
    else {
        printf("! REALLOC ERROR");
    }

}

void isSortValid(file a[], long size) {
    for (long i = 1;i < size;i++) {
        if (a[i].size < a[i - 1].size) {
            printf("INVALID SORT!!!!!!!!!!!");
        }
            
    }

}

int main() {
	setlocale(LC_ALL, "");
    /*char* a[] = {"�����","�������","�����","���������","�������"};
    long size = 5;
    printsarr(a, size);
    bubbleSort(a, size);
    printsarr(a, size);*/
    file *files = (file*)malloc(10*sizeof(file));
    long fcap = 10;

    struct _finddata_t c_file;
    intptr_t hFile;
    char path[200] = "E:\\TVR4\\3D\\Render\\*.*";
    long count = 0;

    if ((hFile = _findfirst(path, &c_file)) == -1L)
        printf("No files in current directory!\n");
    else
    {
        printf("Listing of .c files\n\n");
        printf("FILE         DATE %24c   SIZE\n", ' ');
        printf("----         ---- %24c   ----\n", ' ');
        do {
            char buffer[30];
            ctime_s(buffer, _countof(buffer), &c_file.time_write); 
            //printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
            if (count >= fcap)
                extend(&files, &fcap);

            files[count].size = c_file.size;
            files[count].name = (char*)malloc(strlen(c_file.name) * sizeof(char));
            if (files[count].name) {
                strcpy(files[count].name, c_file.name);
            }
            else {
                printf("! MALLOC ERROR\n");
            }
                
            
            
            count++;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
        printf("\ncount of files: %d\n", count);
    }

    void (*sort) (file a[], long size);

    sort = callquickSortR;
    ///////////////////////////////////////////////////////////////////
    double start = omp_get_wtime();
    sort(files, count);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //mergeSort(files, 0, count);

    double end = omp_get_wtime();
    double wtick = omp_get_wtick();

    printfiles(files, count);

    printf("Execution time = %lf\n", end - start);

    //printf("wtick = %.16g\n", wtick);



    //clock_t start, end;
    //start = clock();

    //end = clock();
    //printf("Total time:%g\n", (double)(end - start) / CLOCKS_PER_SEC);

    isSortValid(files, count);
    
    system("pause");
}

//int main2(void)
//{
//    struct _finddata_t c_file;
//    intptr_t hFile;
//    char path[200];
//    int count = 0;
//
//    // Find first file in directory c:\temp
//    if ((hFile = _findfirst("c:\\temp\\*.*", &c_file)) == -1L)
//        printf("No files in current directory!\n");
//    else
//    {
//        printf("Listing of .c files\n\n");
//        printf("FILE         DATE %24c   SIZE\n", ' ');
//        printf("----         ---- %24c   ----\n", ' ');
//        do {
//            char buffer[30];
//            ctime_s(buffer, _countof(buffer), &c_file.time_write);
//            if (count <= 20)
//                printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
//            count++;
//        } while (_findnext(hFile, &c_file) == 0);
//        _findclose(hFile);
//        printf("\ncount of files: %d", count);
//    }
//    system("pause");
//}

//����������� �������� ��������� ��������� � �������� ������ ������ � �������� ��������, ������������� �� ����������� / �������� �������.
//
//������� ������ :
//���� �� ����������, � ������� ���������� ������������� ����������.
//����� ����������.
//�������� ������ :
//��������������� ������ ���� ������ � ��������� �������.
//����� ����������.
//��������� ������ ������������� ������������ ����������� ������� ����� ���������� � �������� ����������� �������� ������.
//
//��������� ������ ������������� ������ � ������������� ����������� ����������, ������� �������� :
//����������� ����� ���� �� ��������� ��������;
//����������� ������ ������ ����������;
//����������� ��������� ���������������� ������ ������ � ��������� �������.
//C����� ������� ���������� :
//���������
//�������
//���������
//��������
//�����
//�����
//���������
//https://metanit.com/c/tutorial/5.11.php
//https://www.techiedelight.com/ru/find-execution-time-c-program/