class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
              vector<vector<int>>adjList(n+1);

              for(auto it:edges){
                adjList[it[0]].push_back(it[1]);
                adjList[it[1]].push_back(it[0]);
              }

              vector<vector<int>>distance(n+1,vector<int>(2,1e9)); 
              queue<pair<int,int>>q;

              q.push({1,0});
              distance[1][0]=0;

              while(!q.empty()){
                int node=q.front().first;
                int currTime=q.front().second;
                q.pop(); 
                

                if((currTime / change) % 2 == 1){
                  currTime += (change - (currTime % change));
                }

                for(auto it:adjList[node]){
                    if(currTime+time<distance[it][0]){
                         distance[it][0]=currTime+time;
                         q.push({it,currTime+time});
                    }else if(currTime+time > distance[it][0] && currTime+time<distance[it][1]){
                          distance[it][1]=currTime+time;

                          q.push({it,currTime+time});
                    }
                }

              }

              return distance[n][1];


    }
};