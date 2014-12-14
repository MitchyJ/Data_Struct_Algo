import java.util.*;
import java.io.*;

//Name of collaborator: Eugene

class Knight{

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in); 
		while (sc.hasNextInt()) {
			int a = sc.nextInt();	
			int container = 1+4*a+(7*a*a);
			System.out.println(container);
		}
		sc.close();
	}

}

//1 + 4d + 7d2
