#include<stdio.h>
#include<stdlib.h>

typedef int DATATYPE;

typedef struct TreeNode
{
	DATATYPE data;
	struct TreeNode* Left;
	struct TreeNode* Right;
}TreeNode;

void PreorderTraversal(TreeNode* tree);
void InorderTraversal(TreeNode* tree);
void PostorderTraversal(TreeNode* tree);

TreeNode* MakeTree(void);
DATATYPE RetData(TreeNode* tree);
void SaveData(TreeNode* tree, DATATYPE data);

TreeNode* RetSubTreeLeft(TreeNode* tree);
TreeNode* RetSubTreeRight(TreeNode* tree);

void MakeSubTreeLeft(TreeNode* tree, TreeNode* Subtree);
void MakeSubTreeRight(TreeNode* tree, TreeNode* Subtree);

int main(int argc, char* argv[])
{
	TreeNode* tree1 = MakeTree();
	TreeNode* tree2 = MakeTree();
	TreeNode* tree3 = MakeTree();
	TreeNode* tree4 = MakeTree();
	TreeNode* tree5 = MakeTree();

	SaveData(tree1, 1);
	SaveData(tree2, 2);
	SaveData(tree3, 3);
	SaveData(tree4, 4);
	SaveData(tree5, 5);

	MakeSubTreeLeft(tree1, tree2);
	MakeSubTreeRight(tree1, tree3);
	MakeSubTreeLeft(tree2, tree4);
	MakeSubTreeRight(tree2, tree5);

	//printf tree
	printf("preorder : ");
	PreorderTraversal(tree1);
	printf("\n");

	printf("inorder : ");
	InorderTraversal(tree1);
	printf("\n");

	printf("postorder : ");
	PostorderTraversal(tree1);
	printf("\n");


	return 0;
}
TreeNode* MakeTree(void)
{
	TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
	tree->Left = NULL;
	tree->Right = NULL;

	return tree;
}//change to pass by argument

void PreorderTraversal(TreeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}

	printf("%d ", tree->data);
	PreorderTraversal(tree->Left);
	PreorderTraversal(tree->Right);
}

void InorderTraversal(TreeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}

	InorderTraversal(tree->Left);
	printf("%d ", tree->data);
	InorderTraversal(tree->Right);
}

void PostorderTraversal(TreeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}

	PostorderTraversal(tree->Left);
	PostorderTraversal(tree->Right);
	printf("%d ", tree->data);
}



DATATYPE RetData(TreeNode* tree)
{
	return tree->data;
}

void SaveData(TreeNode* tree, DATATYPE data)
{
	tree->data = data;
}

TreeNode* RetSubTreeLeft(TreeNode* tree)
{
	return tree->Left;
}

TreeNode* RetSubTreeRight(TreeNode* tree)
{
	return tree->Right;
}

void MakeSubTreeLeft(TreeNode* tree, TreeNode* subtree)
{
	if (tree->Left != NULL)
	{
		free(tree->Left);
	}

	tree->Left = subtree;
}

void MakeSubTreeRight(TreeNode* tree, TreeNode* subtree)
{
	if (tree->Right != NULL)
	{
		free(tree->Right);
	}

	tree->Right = subtree;
}