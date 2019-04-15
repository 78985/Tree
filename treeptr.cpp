#include<iostream>
using namespace std;
struct node 
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) 
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) 
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p)
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}

node* insert(node* p, int k) 
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

node* findmin(node* p) 
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) 
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) 
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = remove(p->left,k);
	else if( k > p->key )
		p->right = remove(p->right,k);	
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
void print_tree(node* root)
{
	cout<<root->key<<' ';
	if(root->left!=NULL)
		print_tree(root->left);
	if(root->right!=NULL)
		print_tree(root->right);
}
void deleteTree(node* node)  
{  
    if (node == NULL) return;  
  
    deleteTree(node->left);  
    deleteTree(node->right);  
      
    cout << "\n Deleting node: " << node->key;  
    delete(node);
}
class tree;
class tree
{
	public:
		tree(int k) {
			node a(k);
			this->root=&a;	
		}
		~tree() {
			cout<<endl;
			cout<<"DESTRUCTOR CALLED"<<endl;
			cout<<"=================="<<endl;
			node* p=this->root;
			deleteTree(p);
		}
		void Tinsert(int k) {
			node* p=this->root;
			this->root=insert(p,k);
		}
		void Tremove(int k) {
			node* p=this->root;
			p=remove(p,k);
			this->root=p; 
		}
		void Tprint(){
			node* p=this->root;
			print_tree(p);
		}
		void Theight() {
			//node* p=this->root;
		//fixheight(p);
			//unsigned char x=p->height;
			cout<<"HEIGHT: "<<(int)(this->root->height)<<endl;
		}
	protected:
		node* root;
};
int main()
{
	tree t(5);
	t.Tinsert(6);
	t.Tinsert(123);
	t.Tinsert(12);
	t.Tinsert(3);
	t.Tinsert(56);
	t.Tinsert(23);
	t.Tremove(3);
	t.Theight();
	t.Tprint();
	return 0;
}
