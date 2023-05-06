import java.io.*;
import java.net.*;

public class ChatClient {
    private String hostname;
    private int port;

    public ChatClient(String hostname, int port) {
        this.hostname = hostname;
        this.port = port;
    }

    public void execute() {
        try {
            Socket socket = new Socket(hostname, port);

            System.out.println("Connected to the chat server");

            new ReadThread(socket, this).start();
            new WriteThread(socket, this).start();

        } catch (UnknownHostException ex) {
            System.out.println("Server not found: " + ex.getMessage());
        } catch (IOException ex) {
            System.out.println("I/O Error: " + ex.getMessage());
        }
    }

    public static void main(String[] args) {
        String hostname = "localhost";
        int port = 8989;

        ChatClient client = new ChatClient(hostname, port);
        client.execute();
    }
}
class ReadThread extends Thread {
    private BufferedReader reader;
    private ChatClient client;

    public ReadThread(Socket socket, ChatClient client) {
        this.client = client;

        try {
            InputStream input = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(input));
        } catch (IOException ex) {
            System.out.println("Error getting input stream: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void run() {
        while (true) {
            try {
                String response = reader.readLine();
                System.out.println("\n" + response);
            } catch (IOException ex) {
                System.out.println("Error reading from server: " + ex.getMessage());
                ex.printStackTrace();
                break;
            }
        }
    }
}

class WriteThread extends Thread {
    private PrintWriter writer;
    private ChatClient client;

    public WriteThread(Socket socket, ChatClient client) {
        this.client = client;

        try {
            OutputStream output = socket.getOutputStream();
            writer = new PrintWriter(output, true);
        } catch (IOException ex) {
            System.out.println("Error getting output stream: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void run() {
        Console console = System.console();

        String userName = console.readLine("\nEnter your name: ");
        writer.println(userName);

        String roomName = console.readLine("Enter the room name: ");
        writer.println(roomName);

        String text;

        do {
            text = console.readLine("[" + userName + "]: ");
            writer.println(text);

        } while (!text.equalsIgnoreCase("bye"));
    }
}