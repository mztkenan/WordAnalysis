#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 32

// ===========================================
//                 STRUCTURE
//============================================
typedef struct word
{
    char *str;
    int count;
    struct word *pNext;
}WordNode;

// ===========================================
//             FUNCTION PROTOTYPES
//============================================

int getNextWord(FILE *fp, char *buf);   //������һ������
void addWord(char *pWord);              //�����ʼ�������
void print();                           //����Ļ�ϴ�ӡ
WordNode* createWordNode(char *word);   //�����µĵ��ʽڵ�
// ===========================================
//             GLOBAL VARIABLES
//============================================

WordNode *head=NULL;            //����ͷ�ڵ�
int totalcount=0;               //��������
int uniquecount=0;               //���ظ��ĵ�������

// ===========================================
//                 MAIN
//============================================

int main()
{
    char temp[MAX_WORD];
    FILE *fp;

    if((fp=fopen("article.txt","r"))==NULL)
    {
        printf("�ļ������ڣ���ʧ�ܣ�");
        exit(0);
    }

    while(getNextWord(fp,temp))
    {
        addWord(temp);
        totalcount++;   //������������
    }

    fclose(fp);
    print();

    //�ͷ��ڴ�
    if(head!=NULL)
    {
        WordNode *tempNode;
        while(head->pNext!=NULL)
        {
            tempNode=head->pNext;
            free(head);
            head=tempNode;

        }
    }
    return 0;
}
// ===========================================
//                 FUNCTIONS
//============================================
int getNextWord(FILE *fp, char *buf)
{
        char c;
        //�������з���ĸ
        while(!isalpha(c=fgetc(fp)))
        {
            if(c==EOF)
            {
                return 0;
            }
        }
        //��ȡ������ĸ
        while(isalpha(c))
        {
            *buf++=tolower(c);  //����д��ĸתΪСд
            c=fgetc(fp);

        }
        *buf='\0';
        return 1;

}
void addWord(char *pWord)
{
    WordNode *pTemp = NULL;

    if(head==NULL)
    {
        head=createWordNode(pWord);
        return;
    }

    pTemp=head;
    while(pTemp->pNext!=NULL)
    {
        if(strcasecmp(pWord,pTemp->str)==0)
        {
            pTemp->count++;     //�������Ѵ��ڣ�������һ
            return;
        }
        pTemp=pTemp->pNext;
    }
    pTemp->pNext=createWordNode(pWord);  //�����ʲ��������У����½��ڵ�
    uniquecount++;
}
void print()
{
    printf("\nͳ�ƽ����\n\n");
    printf("  %d words\n",totalcount);
    printf("  %d unique words\n",uniquecount);

    WordNode *pCurrent=head;
    while(pCurrent->pNext!=NULL)
    {
        printf("\n%-30s   %5d", pCurrent->str,pCurrent->count);
        pCurrent=pCurrent->pNext;
    }
}
WordNode* createWordNode(char *pWord)
{
    WordNode *pTemp=NULL;
    pTemp=(WordNode*)malloc(sizeof(WordNode));
    pTemp->str=(char*)malloc(strlen(pWord)+1);
    strcpy(pTemp->str,pWord);
    pTemp->count=1;
    pTemp->pNext=NULL;
    return pTemp;
}








