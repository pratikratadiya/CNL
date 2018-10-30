import java.util.*;
import java.net.*;
public class program{
	public static void main(String[] args) throws SocketException{
		Scanner scanner = new Scanner(System.in);

		System.out.print("Name:");
		String name = scanner.nextLine();

		System.out.print("Source Port:");
		int sourcePort = Integer.parseInt(scanner.nextLine());

		System.out.print("Destination IP:");
		String destinationIP = scanner.nextLine();

		System.out.print("Destination Port:");
		int destinationPort = Integer.parseInt(scanner.nextLine());

		channel chan = new channel();
		chan.bind(sourcePort);
		chan.start();

		System.out.println("Started");

		InetSocketAddress address = new InetSocketAddress(destinationIP,destinationPort);

		while (true) {
			String msg = scanner.nextLine();
			if (msg.isEmpty()) {
				break;
			}
			msg = name + " -> " + msg;
			chan.sendTo(address,msg);
			System.out.println(msg);
		}

		scanner.close();
		chan.stop();
		System.out.println("Closed");
 	}
}