import java.util.*;
import java.io.*;

public class swapsort {
    //neighbors[i] is a list of all the vertices j which are adjacent to i
    //(We are treating the pairs (a_1, b_1) ... (a_n, b_n) as edges in a graph.)
    //I use linked list for the list of vertices for efficient insertions.
    //I use array list for the list of list of vertices for efficient random access, since we need to be able to easily access the neighbors of any given vertex for DFS to be efficient.
    private static ArrayList<LinkedList<Integer>> neighbors;
    
    //If two vertices i, j are in the same connected component of the graph,
    // then connectedComponent[i] == connectedComponent[j]
    //If we haven't found the connected component of vertex i yet,
    // then connectedComponent[i] is 0.
    private static int connectedComponent[];
    
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokens = new StringTokenizer(reader.readLine());
        //Read in N and K from the first line:
        int N = Integer.parseInt(tokens.nextToken());
        int K = Integer.parseInt(tokens.nextToken());

        //Initialize the arrays:
        neighbors = new ArrayList<LinkedList<Integer>>(N);
        for (int i = 0; i < N; i++) neighbors.add(new LinkedList<Integer>());
        connectedComponent = new int[N];

        //Read in all the edges in the graph and update the neighbors lists appropriately:
        for (int i = 0; i < K; i++) {
            tokens = new StringTokenizer(reader.readLine());
            int vertex1 = Integer.parseInt(tokens.nextToken());
            int vertex2 = Integer.parseInt(tokens.nextToken());
            //Convert zero-based indexing to one-based indexing
            vertex1--;
            vertex2--;
            
            neighbors.get(vertex1).add(vertex2);
            neighbors.get(vertex2).add(vertex1);
        }

        //Label all the vertices by connected component:
        int numComponents = 0;
        for (int i = 0; i < N; i++) {
            if (connectedComponent[i] == 0) {
                numComponents++;
                labelConnectedComponent(i, numComponents);
            }
        }

        //Output No if there is no way to swap i with N-i-1
        for (int i = 0; i < N/2; i++) {
            if (connectedComponent[N-i-1] != connectedComponent[i]) {
                System.out.println("No");
                return;
            }
        }
        //Otherwise, we can reverse the list, so output Yes
        System.out.println("Yes");
    }
    
    //Label all the vertices in the connected component of v with componentLabel
    private static void labelConnectedComponent(int v, int componentLabel) {
        //First, label v:
        connectedComponent[v] = componentLabel;
        
        //We use a Stack for our depth-first search to label all the vertices in this connected component.
        Stack<Integer> toBeLabeled = new Stack<>();
        toBeLabeled.add(v);
        while (!toBeLabeled.empty()) {
            int curVertex = toBeLabeled.pop();
            for (int neighboringVertex : neighbors.get(curVertex)) {
                //Only add vertices which haven't been visited before to the stack
                if (connectedComponent[neighboringVertex] == 0) {
                    connectedComponent[neighboringVertex] = componentLabel;
                    toBeLabeled.add(neighboringVertex);
                }
            }
        }
    }
}