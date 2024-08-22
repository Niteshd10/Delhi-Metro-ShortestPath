#include<bits/stdc++.h>
using namespace std;

class pathAndDistance {
public:
    vector<int> path;
    int dist;
    pathAndDistance(vector<int> path, int dist) {
        this->path = path;
        this->dist = dist;
    }
};

class Graph {
public:
    vector<vector<pair<int, int>>> adjList;

    Graph(int n) {
        adjList.resize(n);
    }

    void add_edge(int u, int v, int d) {
        adjList[u].push_back({v, d});
        adjList[v].push_back({u, d});
    }

    void dfs(int source, int destination, vector<int>& visited, vector<int>& path, int dist, vector<pathAndDistance>& ans) {
        if(source == destination) {
            path.push_back(source);
            ans.push_back(pathAndDistance(path, dist));
            path.pop_back();
            return;
        }
        
        for(int i = 0; i < adjList[source].size(); i++) {
            if(!visited[source]) {
                visited[source] = 1;
                path.push_back(source);
                dfs(adjList[source][i].first, destination, visited, path, dist+adjList[source][i].second, ans);
                path.pop_back();
                visited[source] = 0;
            }
        }
    }

    vector<pathAndDistance> shortest_reach(int& source, int& destination) {
        int n = adjList.size();
        vector<int> visited(n, 0);
        vector<int> path;
        vector<pathAndDistance> ans;
        dfs(source, destination, visited, path, 0, ans);
        return ans;
    }

};
int addStations(unordered_map<int, string>& stations) {
    int id = 0;
    stations[id++] = "Noida Sector 62~B";       //0
    stations[id++] = "Botanical Garden~B";      //1
    stations[id++] = "Yamuna Bank~B";           //2
    stations[id++] = "Rajiv Chowk~BY";          //3
    stations[id++] = "Vaishali~B";              //4
    stations[id++] = "Moti Nagar~B";            //5
    stations[id++] = "Janak Puri West~BO";      //6
    stations[id++] = "Dwarka Sector 21~B";      //7
    stations[id++] = "Huda City Center~Y";      //8
    stations[id++] = "Saket~Y";                 //9
    stations[id++] = "Vishwavidyalaya~Y";       //10
    stations[id++] = "Chandni Chowk~Y";         //11
    stations[id++] = "New Delhi~YO";            //12
    stations[id++] = "AIIMS~Y";                 //13
    stations[id++] = "Shivaji Stadium~O";       //14
    stations[id++] = "DDS Campus~O";            //15
    stations[id++] = "IGI Airport~O";           //16
    stations[id++] = "Rajouri Garden~BP";       //17
    stations[id++] = "Netaji Subhash Place~PR"; //18
    stations[id++] = "Punjabi Bagh West~P";     //19
    return id;
}
int main() {
    unordered_map<int, string> stations;
    int n = addStations(stations);

    //ADDING EDGES/CONNECTIONS
    Graph graph(n);
    graph.add_edge(0, 1, 8);
    graph.add_edge(1, 2, 10);
    graph.add_edge(2, 4, 8);
    graph.add_edge(2, 3, 6);
    graph.add_edge(3, 5, 9);
    graph.add_edge(5, 6, 7);
    graph.add_edge(6, 7, 6);
    graph.add_edge(8, 9, 15);
    graph.add_edge(9, 13, 6);
    graph.add_edge(13, 3, 7);
    graph.add_edge(3, 12, 1);
    graph.add_edge(12, 11, 2);
    graph.add_edge(11, 10, 7);
    graph.add_edge(12, 14, 2);
    graph.add_edge(14, 15, 7);
    graph.add_edge(15, 16, 8);
    graph.add_edge(5, 17, 2);
    graph.add_edge(19, 17, 2);
    graph.add_edge(19, 18, 3);
    graph.add_edge(8, 12, 1);
    graph.add_edge(8, 18, 1);

    cout<<"Enter SourceID and DestinationID :"<<endl;
    int source, destination;
    cin>>source>>destination;

    vector<pathAndDistance> ans = graph.shortest_reach(source, destination);
    sort( ans.begin( ), ans.end( ), [ ]( const auto& p1, const auto& p2 )
    {
       return p1.dist < p2.dist;
    });

    cout<<"ALL PATHS"<<endl;
    cout<<"-----------------------------------------------------------"<<endl;

    for(int i = 0; i < ans.size(); i++) {
        vector<int> arr = ans[i].path;
        if(i == 0) cout<<"SHORTEST_PATH  : )"<<endl;
        for(int j = 0; j < arr.size(); j++) {
            cout<<stations[arr[j]];
            if(j < arr.size()-1)cout<<" <-----> ";
        }
        cout<<endl;
        cout<<"Dist = "<<ans[i].dist<<endl;
        if(i < ans.size()-1)cout<<"-----------------------------------------------------------"<<endl;
    }

    return 0;
}
