import java.util.*;
import java.io.*;

// write your matric number here:A0098997U
// write your name here:Mitchelle 
// write list of collaborators here (reading someone's post in Facebook Group and using the idea is counted as collaborating): Harry 

class HospitalTour {
	private int V; // number of vertices in the graph (number of rooms in the hospital)
	/*  private int[][] AdjMatrix; // the graph (the hospital)
  private int[] RatingScore; // the weight of each vertex (rating score of each room)
	 */
	// if needed, declare a private data structure here that
	// is accessible to all methods in this class
	private Vector<Vector<Integer>> adjList;
	private Vector<Integer> roomIndex;
	private Vector<Integer> RatingScore;
	//  private boolean[] visit;
	// private int[] roomIndex;

	public HospitalTour() {
		// Write necessary codes during construction
		//
		// write your answer here
	}

	int Query() {
		//   int ans = 0;
		// You have to report the rating score of the important room (vertex)
		// with the lowest rating score in this hospital
		//
		// or report -1 if that hospital has no important room
		//
		// write your answer here
		roomIndex = new Vector<Integer>();
		//visit = new boolean[100];
		//no room return -1

		//roomIndex = new int[100];
		//use dfs to find min value,add to roomIndex 
		for (int i=0; i<V; i++){

			int valueContainer = dfs(0 , i , new boolean[V]);

			if (valueContainer < (V-1)){ //found room
				roomIndex.add(i);
			}
		}

		if (roomIndex.isEmpty()){ 
			return -1; 
		}

		//compare rating 
		int ans = RatingScore.get(roomIndex.get(0));;
		for(int curr=1; curr<roomIndex.size(); curr++){
			int temp = RatingScore.get(roomIndex.get(curr));
			if (temp<ans){
				ans = temp;
			}
		}

		return ans;


	}

	// You can add extra function if needed
	// --------------------------------------------
	public int dfs(int curr, int index, boolean[] visited){
		int count=0;


		//set visited verte
		if(index != curr){
			visited[curr]=true; 
			count++;
		}
		Vector<Integer> neighbour = adjList.get(curr);
		for(int i=0; i<neighbour.size(); i++){

			int next = neighbour.get(i); 

			if((visited[next] == false) && (next!=index) && (index==curr)) { 
				count = dfs(next,index,visited);
			} 

			if((visited[next] == false) && (next!=index)) { 
				count += dfs(next,index,visited);
			} 



		}

		return count;

	}




	// --------------------------------------------

	void run() throws Exception {
		// for this PS3, you can alter this method as you see fit

		/* BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    int TC = Integer.parseInt(br.readLine()); // there will be several test cases
    while (TC-- > 0) {
      br.readLine(); // ignore dummy blank line
      V = Integer.parseInt(br.readLine());

      StringTokenizer st = new StringTokenizer(br.readLine());
      // read rating scores, A (index 0), B (index 1), C (index 2), ..., until the V-th index
      RatingScore = new int[V];
      for (int i = 0; i < V; i++)
        RatingScore[i] = Integer.parseInt(st.nextToken());

      // clear the graph and read in a new graph as Adjacency Matrix
      AdjMatrix = new int[V][V];
      for (int i = 0; i < V; i++) {
        st = new StringTokenizer(br.readLine());
        int k = Integer.parseInt(st.nextToken());
        while (k-- > 0) {
          int j = Integer.parseInt(st.nextToken());
          AdjMatrix[i][j] = 1; // edge weight is always 1 (the weight is on vertices now)
        }
      }

      pr.println(Query());
    }
    pr.close();*/

		Scanner sc = new Scanner(System.in);

		int TC = sc.nextInt(); 
		while (TC-- > 0) {
			V = sc.nextInt();

			/*	  BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	    int TC = Integer.parseInt(br.readLine()); // there will be several test cases
	    while (TC-- > 0) {
	      br.readLine(); // ignore dummy blank line
	      V = Integer.parseInt(br.readLine());*/


			//StringTokenizer st = new StringTokenizer(br.readLine());
			// read rating scores, A (index 0), B (index 1), C (index 2), ..., until the V-th index
			RatingScore = new Vector<Integer>();
			//int f = 0;
			for (int i = 0; i < V; i++)
				//f =  Integer.parseInt(st.nextToken());
				RatingScore.add(sc.nextInt());
			// RatingScore.add(f);
			//RatingScore.add(Integer.parseInt(st.nextToken()));

			//inserting 
			adjList=new Vector<Vector<Integer>>();
			for(int i=0; i<V; i++){
				Vector<Integer> vertex = new Vector<Integer>();
				int k = sc.nextInt();
				//  st = new StringTokenizer(br.readLine());
				//   int k = Integer.parseInt(st.nextToken());
				while(k-- >0){
					int m=sc.nextInt(); 
					//	int j = Integer.parseInt(st.nextToken());
					vertex.add(m);
				}
				adjList.add(vertex);
			}
			System.out.println(Query());
		}
		sc.close();
	}

	public static void main(String[] args) throws Exception {
		// do not alter this method
		HospitalTour ps3 = new HospitalTour();
		ps3.run();
	}
}



class IntegerPair implements Comparable {
	Integer _first, _second;

	public IntegerPair(Integer f, Integer s) {
		_first = f;
		_second = s;
	}

	public int compareTo(Object o) {
		if (!this.first().equals(((IntegerPair)o).first()))
			return this.first() - ((IntegerPair)o).first();
		else
			return this.second() - ((IntegerPair)o).second();
	}

	Integer first() { return _first; }
	Integer second() { return _second; }
}
