#pragma once
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
typedef signed char int8_t;
typedef signed short int  int16_t;
typedef signed int  int32_t;
typedef signed long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int  uint32_t;
typedef unsigned long long uint64_t;


//�ڵ�ṹ�壬ÿ���ڵ�ֱ𱣴���һ��ָ��ǰһ���ڵ��ָ���ָ���һ���ڵ��ָ�룬�Լ��������ݵ�ָ��

//����˫������Ľڵ� 
typedef struct Node
{
	struct Node *prior;
	struct Node *next;
	float longitude; //����
	float latitude;  //γ��
	float speed;     //�ٶ�
	uint32_t seconds;//unix ʱ���
	uint16_t millisecondes;//������
	float direction; //��λ�ǣ�����Ϊ0��
};

//��ʼ��һ������Ľڵ�
Node* create_node(void);

//��������N������˫������
Node* create_list(int n);


//����ĳ���
int len_list(Node * node);


//��λ�����������λ��
Node* pos_list(Node *head, int n);


//�������һ������
void out_front_list(Node *head);

//�������һ������
void out_reverse_list(Node *head);

//�������ͷ��������
Node* start_insert_list(Node *head);

//�����нڵ������������ĩβ
void insert_list(Node *head, Node *p);


//�������β��������
Node* end_insert_list(Node *head);


//���뵽����λ��֮ǰ
Node* insert_befor_list(Node *head, int a);

//���뵽����λ��֮�� 
Node* insert_after_list(Node *head, int a);

//ɾ��ͷ���
Node* delect_start_list(Node *head);


//ɾ��β���
Node* delect_end_list(Node *head);


//ɾ��ָ��λ�õĽڵ�
Node* delect_list(Node *head, int i);

//������ݵ��ڵ�
void fill_node_once(float dire, float lat, float lng, int time, float speed, Node * head);

void write_lap(float timediff);
