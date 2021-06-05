
#ifndef KD_TREE_H
#define KD_TREE_H


	const int k = 2;
	
	class kd_tree
	{
	public:
		struct Node
		{
			float point[k];
			Node* left, * right;
		};
		Node* insert(Node* root, float point[], unsigned depth);
		Node* nnSearch(Node* root, float point[], unsigned depth);
		Node* root;
		Node* best;
		float best_dist;
	private:
		
	};


#endif
