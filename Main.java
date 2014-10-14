import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) throws IOException {
		new Main().solve();
	}
	public void solve() throws IOException{
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		PrintWriter cout = new PrintWriter(new BufferedOutputStream(System.out));
		
		int n = cin.nextInt();
		cout.println(n);
		
		cin.close(); cout.flush(); cout.close();
	}
}