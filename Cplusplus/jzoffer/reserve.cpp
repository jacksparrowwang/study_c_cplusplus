
// 链表的反转

#include <iostream>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if (pHead == NULL)
        {
            return NULL;
        }
        if (pHead->next == NULL)
        {
            return pHead;
        }
        ListNode* fast = pHead->next->next;
        ListNode* pre = pHead->next;
        ListNode* cur = pHead;
        pHead->next = NULL;
        pre->next = pHead;
        while (fast != NULL)
        {
            cur = pre;
            pre = fast;
            fast = fast->next;
            pre->next = cur;
        }
        return pre;
    }
};
