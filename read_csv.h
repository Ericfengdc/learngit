#pragma once
#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok


#define MAX_LINE_SIZE 256   //fgets������ȡ������ֽ���


int* giCsvData;           //��̬���������ڴ��ָ��
int giNumData;            //��ȡ�������ֽ���
int giNumRow;             //ÿ�е��ֽ���
int giNumCol;             // ÿ�е��ֽ���


int GetTotalLineCount(FILE* fp);              //����csv�ļ��е�������
int GetTotalColCount(FILE * fp);              //����csv�ļ��е����������Ե�һ�е�����Ϊ��׼��
int AssignSpaceForData(int inumdata);         //ͨ��ָ��*giCsvData�����ݶ�̬�����ڴ�ռ�
void FreeCsvData();                           //�ͷŶ�̬�����ڴ�
int ReadCsvData(char* csvFilePath);           //��ȡCsv�����ݣ�����Ĭ����������Ϊint��
void  ShowCsvData();                           //ͨ������̨��ʾ��ȡ��csv����
//����csv�ļ��е�������
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
//����csv�ļ��е����������Ե�һ�е�����Ϊ��׼��
int GetTotalColCount(FILE * fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	if (fgets(strLine, MAX_LINE_SIZE, fp))
	{
		i = strlen(strLine) / 2;   //��Ϊcsv�ļ��Զ���','��Ϊ�ָ��������Դ˴�����2
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	return i;
}
// ͨ��ָ��*giCsvData�����ݶ�̬�����ڴ�ռ�
int AssignSpaceForData(int inumdata) {
	giCsvData = NULL;
	giCsvData = (int*)malloc(sizeof(int)*inumdata);
	if (giCsvData == NULL)
		return 0;
	memset(giCsvData, 0, sizeof(int)*inumdata);
	return 1;
}

// �ͷŶ�̬�����ڴ�
void FreeCsvData() {
	free(giCsvData);
	giCsvData = NULL;
}

// ��csv�ļ��ж�ȡ����
int ReadCsvData(char* csvFilePath)
{
	FILE* fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	int i;
	int j;
	// �Ѿ��������ݣ�����ɾ��
	if (giCsvData != NULL)
		FreeCsvData();
	// ���ļ�
	if (fopen_s(&fCsv, csvFilePath, "r") != 0)
	{
		printf("open file %s failed", csvFilePath);
		return -1;
	}
	else
	{
		// ȷ����̬����Ĵ�С��Ȼ�󿪱ٿռ�
		giNumRow = GetTotalLineCount(fCsv);
		giNumCol = GetTotalColCount(fCsv);
		giNumData = giNumRow * giNumCol;
		AssignSpaceForData(giNumData);

		// ��ȡ����
		for (i = 0; i < giNumRow; i++)
		{

			j = 0;
			if (fgets(strLine, MAX_LINE_SIZE, fCsv))
			{
				char *pTmp = NULL;
				ptr = strtok_s(strLine, ",",&pTmp);  //�����ַ��������ַ���,��֮ǰ���ַ���ʣ�µı�������̬�����У��˷���vs��Ϊ����ȫ��
				//���Գ���ʹ��strtok_s�滻
				printf("%s\n", ptr);
				while (ptr != NULL)
				{
					giCsvData[i*giNumCol + j] = atoi(ptr);     //���ַ�ת��Ϊint�������ݲ����浽��̬������
					j++;
					ptr = strtok_s(NULL, ",",&pTmp);                //�����ļ��ж�ȡ�ĵ�ǰ��ʣ���ַ����飬��ȡ�ַ���,��ǰ����ֽ�
				}
			}
		}
		// �ر��ļ�
		fclose(fCsv);
	}
	return 1;
}

//ͨ������̨��ʾ��ȡ��csv����
void  ShowCsvData()
{
	int i;
	int j;
	for (i = 0; i < giNumRow; i++)
	{
		printf("Line %i :", i + 1);    //���ÿ�е��к� Line :
		for (j = 0; j < giNumCol; j++)
		{
			printf("%i", giCsvData[i*giNumCol + j]);  // ��ӡCSV����
		}
		printf("\n");                           //�������
	}
}