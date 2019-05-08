#pragma once
#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok


#define MAX_LINE_SIZE 256   //fgets函数读取的最大字节数


int* giCsvData;           //动态分配数据内存的指针
int giNumData;            //读取的数据字节数
int giNumRow;             //每行的字节数
int giNumCol;             // 每列的字节数


int GetTotalLineCount(FILE* fp);              //计算csv文件中的总行数
int GetTotalColCount(FILE * fp);              //计算csv文件中的总列数（以第一行的列数为基准）
int AssignSpaceForData(int inumdata);         //通过指针*giCsvData给数据动态分配内存空间
void FreeCsvData();                           //释放动态数据内存
int ReadCsvData(char* csvFilePath);           //读取Csv中数据（本例默认数据类型为int）
void  ShowCsvData();                           //通过控制台显示读取的csv数据
//计算csv文件中的总行数
int GetTotalLineCount(FILE * fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	while (fgets(strLine, MAX_LINE_SIZE, fp))
		i++;
	fseek(fp, 0, SEEK_SET);
	return i;
}
//计算csv文件中的总列数（以第一行的列数为基准）
int GetTotalColCount(FILE * fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	if (fgets(strLine, MAX_LINE_SIZE, fp))
	{
		i = strlen(strLine) / 2;   //因为csv文件以逗号','作为分隔符，所以此处除以2
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	return i;
}
// 通过指针*giCsvData给数据动态分配内存空间
int AssignSpaceForData(int inumdata) {
	giCsvData = NULL;
	giCsvData = (int*)malloc(sizeof(int)*inumdata);
	if (giCsvData == NULL)
		return 0;
	memset(giCsvData, 0, sizeof(int)*inumdata);
	return 1;
}

// 释放动态数据内存
void FreeCsvData() {
	free(giCsvData);
	giCsvData = NULL;
}

// 从csv文件中读取数据
int ReadCsvData(char* csvFilePath)
{
	FILE* fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	int i;
	int j;
	// 已经有了数据，则先删除
	if (giCsvData != NULL)
		FreeCsvData();
	// 打开文件
	if (fopen_s(&fCsv, csvFilePath, "r") != 0)
	{
		printf("open file %s failed", csvFilePath);
		return -1;
	}
	else
	{
		// 确定动态数组的大小，然后开辟空间
		giNumRow = GetTotalLineCount(fCsv);
		giNumCol = GetTotalColCount(fCsv);
		giNumData = giNumRow * giNumCol;
		AssignSpaceForData(giNumData);

		// 读取数据
		for (i = 0; i < giNumRow; i++)
		{

			j = 0;
			if (fgets(strLine, MAX_LINE_SIZE, fCsv))
			{
				char *pTmp = NULL;
				ptr = strtok_s(strLine, ",",&pTmp);  //返回字符数组中字符‘,’之前的字符，剩下的保留到静态数组中（此方法vs认为不安全）
				//可以尝试使用strtok_s替换
				printf("%s\n", ptr);
				while (ptr != NULL)
				{
					giCsvData[i*giNumCol + j] = atoi(ptr);     //将字符转换为int类型数据并保存到动态数组中
					j++;
					ptr = strtok_s(NULL, ",",&pTmp);                //将从文件中读取的当前行剩余字符数组，读取字符‘,’前面的字节
				}
			}
		}
		// 关闭文件
		fclose(fCsv);
	}
	return 1;
}

//通过控制台显示读取的csv数据
void  ShowCsvData()
{
	int i;
	int j;
	for (i = 0; i < giNumRow; i++)
	{
		printf("Line %i :", i + 1);    //输出每行的行号 Line :
		for (j = 0; j < giNumCol; j++)
		{
			printf("%i", giCsvData[i*giNumCol + j]);  // 打印CSV数据
		}
		printf("\n");                           //输出换行
	}
}