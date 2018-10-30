import java.net.*;
import java.io.*;
public class channel implements Runnable{

	private DatagramSocket socket;
	private boolean running;

	public void bind(int port) {
		try{
			socket = new DatagramSocket(port);
		}
		catch (Exception e) {
		}
	}

	public void start(){
		Thread thread  = new Thread(this);
		thread.start();
	}

	public void stop(){
		running = false;
		socket.close();
	}

	@Override
	public void run(){
		byte[] buffer = new byte[1024];
		DatagramPacket packet = new DatagramPacket(buffer,buffer.length);
		running = true;
		while (running) {
			try{
				socket.receive(packet);
				String msg = new String(buffer,0,packet.getLength());
				System.out.println(msg);
			}
			catch (Exception e) {
				e.printStackTrace();
				break;
			}
		}
	}

	public void sendTo(InetSocketAddress address, String msg) {
		try{
			byte[] buffer = msg.getBytes();
			DatagramPacket packet = new DatagramPacket(buffer,buffer.length);
			packet.setSocketAddress(address);
			socket.send(packet);
		}
		catch (Exception e) {
			
		}
	}
}