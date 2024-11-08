typedef int AtomType;
typedef enum{ATOM,LIST} ElemTag;
typedef struct GNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct
        {struct GNode *hp,*tp;}ptr;
    };
}*GList;