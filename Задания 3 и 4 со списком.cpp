#include <iostream>
using namespace std;

struct Node
{
	int val;
	Node* next;
};

void init(Node* node)
{
	node->val = 0;
	node->next = NULL;
}

void pushNode(Node* root, Node* node)
{
	Node* cur = root;
	while (cur->next != NULL)
		cur = cur->next;

	cur->next = new Node;
	init(cur->next);
	cur->val = node->val;
}

void lShiftList(Node* head, int n) {
	for (int i = 0; i < n; i++)
	{
		Node* elem = head;
		int num = elem->val;

		while (elem->next->next != NULL)
		{
			elem->val = elem->next->val;
			elem = elem->next;
		}

		elem->val = num;
	}
}

bool testPushNode()
{
	Node* head = new Node;

	init(head);
	pushNode(head, new Node{ 1 });
	pushNode(head, new Node{ 2 });
	return (head->next->val == 2 && head->val == 1);
}

bool testInitNode()
{
	Node* root = new Node;

	init(root);
	return (root->val == 0);

}

bool testlShiftList() {
	Node* head = new Node;

	init(head);
	pushNode(head, new Node{ 1 });
	pushNode(head, new Node{ 2 });
	pushNode(head, new Node{ 3 });
	pushNode(head, new Node{ 4 });
	lShiftList(head, 3);
	return (head->val == 4 && head->next->val == 1 && head->next->next->val == 2 && head->next->next->next->val == 3);
}

static void runTest(bool (*testFunction)(), const string& testName)
{
	if (testFunction() == 1)
		cout << "Test " << testName << " - OK" << endl;
	else
		cout << "Test " << testName << " - FAIL" << endl;
}

int main()
{
	runTest(testInitNode, "Init test");
	runTest(testPushNode, "Push test");
}
