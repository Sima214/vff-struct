#include "mainlib.h"


bool sortlist(const Node &o1, const Node &o2)
{
    return o1.id < o2.id;
}
struct matchID
{
    explicit matchID(const unsigned int & id) : id_(id) {}
    bool operator()(const Node& obj)
    {
        return obj.id == id_;
    }
private:
    const unsigned int id_;
};
bool findID(unsigned int id,std::vector<Node> list, unsigned int &buffer)
{

    std::sort(list.begin(),list.end(),sortlist);

    auto it = find_if(list.begin(),list.end(),matchID(id));

    if(it == list.end())
    {
        return false;
    }
    unsigned int index =(unsigned int) std::distance(list.begin(),it);
    buffer = index;
    return true;

}

std::vector <Node> List::addToVec() {

    unsigned int id;
    unsigned int number;

    Node temp;
    std::vector<Node>::iterator it;
    while(file>>id && file>> number)
    {

        if(!findID(id,list,id))
        {


            temp.id= id;
            temp.connections.push_back(number);
            list.push_back(temp);
            temp.connections.clear();


        }
        else
        {
            list[id].connections.push_back(number);
            std::sort(list[id].connections.begin(),list[id].connections.end());
            list[id].connections.erase(std::unique(list[id].connections.begin(),list[id].connections.end()),list[id].connections.end());
        }

    }
    return list;
}


void List::insertLink(unsigned int id,unsigned int link)
{
    findID(id,list,id);
    list[id].connections.push_back(link);
    std::sort(list[id].connections.begin(),list[id].connections.end());
    list[id].connections.erase(std::unique(list[id].connections.begin(),list[id].connections.end()),list[id].connections.end());
}
void List::deleteLink(unsigned int id, unsigned int link)
{

    findID(id,list,id);
    if(link == 0)
    {
        list[id].connections.erase(list[id].connections.begin());
        return;
    }
    auto it = std::find(list[id].connections.begin(),list[id].connections.end(),link);
    if(it!= list[id].connections.begin())
    {
        unsigned int index =(const unsigned int) std::distance(list[id].connections.begin(),it);
        list[id].connections.erase(list[id].connections.begin()+index);
    }
}

void List::printVec()
{
    for(int i = 0; i < list.size();i++)
    {
        std::cout<<list[i].id<<": ";
        for(int j = 0; j <list[i].connections.size();j++)
        {
            std::cout<<list[i].connections[j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void List::findNeighbours(unsigned int id)
{
    std::ofstream ofile;
    ofile.open("output.txt");

    findID(id,list,id);
    ofile<< list[id].id << ": ";
    unsigned int i =0 ;
    while(i < list[id].connections.size())
    {
        ofile << list[id].connections[i] << " ";

        i++;
    }

}