typedef struct DuNode
{
    int data;
    struct DuNode *prior;
    struct DuNode *next;
    int freq;
}DuNode,*DuLinklist;
