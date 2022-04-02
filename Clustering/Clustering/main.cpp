//
//  main.cpp
//  Clustering
//
//  Created by Abel Dia on 31/03/22.
//

#include <iostream>
#include <list>
#include <set>
#include <random>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;

int datoss = 0;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, 100);

template<class G>
struct CNode
{
    typedef typename G::n N;
    N m_n;
    int nDatos = 0;
    list<N> ubi;
    CNode(N x)
    {   m_n = x;   }
};

template<class N>
class CGraph
{
public:
   /* CGraph();
    ~CGraph();*/
    
    typedef CGraph<N> self;
    typedef CNode<self> Node;
    typedef N n;
    vector<Node*> nodes;
    vector<N> aux;
    vector<Node*> distances;
    set<N> auxSet;
    
    bool InsNode(N n);
    bool InsPoints(Node* &p, N dim);
    void Print();
    void calcDistances();
};

template<class N>
void CGraph<N>::calcDistances()
{
    list<N> pointA;
    int sum = 0;
    N euclideanDistance;
    for (int i = 0; i < nodes.size(); i++)
    {
        Node* p = nodes[i];
        if (i == 0) {
            pointA = p->ubi;
        }
        else {
            for (typename list<N>::iterator it = p->ubi.begin(), _it = pointA.begin(); it != p->ubi.end(); ++it, ++_it){
                int rest = (*it)-(*_it);
                sum += pow(rest, 2);
            }
            euclideanDistance = sqrt(sum);
            aux.push_back(euclideanDistance);
            auxSet.insert(euclideanDistance);
        }
        sum = 0;
    }
    for (auto it = auxSet.begin(); it!=auxSet.end(); it++) {
        distances.push_back(new CNode<CGraph<N>>(*it));
    }
    for (int i = 0; i < distances.size(); i++)
    {
        int count = 0;
        Node* p = distances[i];
        for (int i = 0; i < aux.size(); i++)
        {
            count += p->m_n == aux[i]? 1 : 0;
        }
        p->nDatos = count;
        datoss+=count;
    }
    
    for (int i = 0; i < distances.size(); i++)
    {
        Node* p = distances[i];
        cout << p->m_n << endl;
        //cout << p->m_n << "    -> " << p->nDatos << endl;
    }
    cout << endl << endl;
    for (int i = 0; i < distances.size(); i++)
    {
        Node* p = distances[i];
        cout << p->nDatos << endl;
        //cout << p->m_n << "    -> " << p->nDatos << endl;
    }
}

template<class N>
bool CGraph<N>::InsPoints(Node* &p, N dim)
{
    for (int i = 1; i <= dim; i++) {
        p->ubi.push_back(distrib(gen));
    }
    return 1;
}

template<class N>
bool CGraph<N>::InsNode(N m)
{
    nodes.push_back(new CNode<CGraph<N>>(m));
    return 1;
}

template<class N>
void CGraph<N>::Print()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        Node* p = nodes[i];
        cout << "Nodo: " << p->m_n << endl;
        for (typename list<N>::iterator it = p->ubi.begin(); it != p->ubi.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << "\n";
    }
}

int main(int argc, const char * argv[])
{
    int dim = 100;
    int nodo = 20000;
    CGraph<int> T;
    
    for (int i = 1; i <= nodo; i++){
        T.InsNode(i);
        T.InsPoints(T.nodes[i-1], dim);
    }
    //T.Print();
    T.calcDistances();
    return 0;
}
