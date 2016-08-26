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

int getNextWord(FILE *fp, char *buf);   //读入下一个单词
void addWord(char *pWord);              //将单词加入链表
void print();                           //在屏幕上打印
WordNode* createWordNode(char *word);   //创建新的单词节点
// ===========================================
//             GLOBAL VARIABLES
//============================================

WordNode *head=NULL;            //链表头节点
int totalcount=0;               //单词总数
int uniquecount=0;               //不重复的单词总数

// ===========================================
//                 MAIN
//============================================

int main()
{
    char temp[MAX_WORD];
    FILE *fp;

    if((fp=fopen("article.txt","r"))==NULL)
    {
        printf("文件不存在，打开失败！");
        exit(0);
    }

    while(getNextWord(fp,temp))
    {
        addWord(temp);
        totalcount++;   //单词总数增加
    }

    fclose(fp);
    print();

    //释放内存
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
        //跳过所有非字母
        while(!isalpha(c=fgetc(fp)))
        {
            if(c==EOF)
            {
                return 0;
            }
        }
        //读取连续字母
        while(isalpha(c))
        {
            *buf++=tolower(c);  //将大写字母转为小写
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
            pTemp->count++;     //若单词已存在，数量加一
            return;
        }
        pTemp=pTemp->pNext;
    }
    pTemp->pNext=createWordNode(pWord);  //若单词不在链表中，则新建节点
    uniquecount++;
}
void print()
{
    printf("\n统计结果：\n\n");
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








