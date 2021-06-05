#include "kd_tree.h"
#include <iostream>
using namespace std;

kd_tree::Node* kd_tree::insert(kd_tree::Node* root, float point [], unsigned depth)
{
	if (root == NULL)
	{
		kd_tree::Node* tmp = new kd_tree::Node;
		for (int i = 0; i < k; i++)
		{
			tmp->point[i] = point[i];
		}
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
		
	}

	unsigned axis = depth % k;
	if (point[axis] < root->point[axis])
	{
		
		root -> left = insert(root->left, point, depth+1);
	}
	else
	{
		root->right = insert(root->right, point, depth+1);
		
	
	}
	
	return root;

}

float distance2D(float point1[], float point2[])
{
	return sqrt(pow(point2[0] - point1[0], 2) +
		pow(point2[1] - point1[1], 2) * 1.0);
}

kd_tree::Node* kd_tree::nnSearch(kd_tree::Node* root, float point[], unsigned depth)
{
	
	
	unsigned axis = depth % k;
	if (point[axis] < root->point[axis])
	{
		if (root->left == NULL)
		{
			float dist = distance2D(root->point, point);
			if (best_dist == NULL ||  dist < best_dist)
			{
				best_dist = dist;
				best = root;
			}
		}
		else
		{
			nnSearch(root->left, point, depth + 1);

			if (root->right != NULL)
			{
				float splitPoint[k];
				for (int i = 0; i < k; i++)
				{
					if (axis == i)
						splitPoint[i] = root->point[i];
					else
						splitPoint[i] = point[i];
				}

				float dist = distance2D(splitPoint, point);
				if (best_dist == NULL || dist < best_dist)
				{
					nnSearch(root->right, point, depth + 1);
				}
			}
		}
	}
	else
	{
		if (root->right == NULL)
		{
			float dist = distance2D(root->point, point);
			if (best_dist == NULL || dist < best_dist)
			{
				best_dist = dist;
				best = root;
			}
		}
		else
		{
			nnSearch(root->right, point, depth + 1);

			if (root->left != NULL)
			{
				float splitPoint[k];
				for (int i = 0; i < k; i++)
				{
					if (axis == i)
						splitPoint[i] = root->point[i];
					else
						splitPoint[i] = point[i];
				}

				float dist = distance2D(splitPoint, point);
				if (best_dist == NULL || dist < best_dist)
				{
					nnSearch(root->left, point, depth + 1);
				}
			}

		}

	}

	return best;

}

int main() {
	kd_tree tree{};
	float x[][k] = { {  0.0f, 1.0f }, { 0.0f, -1.0f}, { 1.0f,-2.0f},{2.0f,-1.1f},{3.0f,-1.5f},{4.0f,0.0f},{3.0f,-1.1f} };

	int n = sizeof(x) / sizeof(x[0]);
	for (int i = 0; i < n; i++)
		tree.root = tree.insert(tree.root, x[i],0);

	kd_tree::Node *l = tree.root;
	float searchPoint[] = { 3.2f,-0.5f };
	kd_tree::Node *b = tree.nnSearch(tree.root, searchPoint, 0);
	cout << b->point[0] << ", " << b->point[1] << endl;

}
