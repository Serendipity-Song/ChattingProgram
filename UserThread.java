import java.io.*;
import java.net.*;

public class UserThread extends Thread {
    private Socket socket;
    private ChatServer server;
    private PrintWriter writer;
    private String currentRoom;

    public UserThread(Socket socket, ChatServer server) {
        this.socket = socket;
        this.server = server;
    }

    public void run() {
        try {
            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));

            OutputStream output = socket.getOutputStream();
            writer = new PrintWriter(output, true);

            String userName = reader.readLine();
            currentRoom = reader.readLine();
            server.addUserToRoom(currentRoom, this);

            String serverMessage = "New user connected: " + userName;
            server.broadcast(currentRoom, serverMessage, this);

            String clientMessage;

            do {
                clientMessage = reader.readLine();
                serverMessage = "[" + userName + "]: " + clientMessage;
                server.broadcast(currentRoom, serverMessage, this);
            } while (!clientMessage.equalsIgnoreCase("bye"));

            server.removeUserFromRoom(currentRoom, this);
            socket.close();

            serverMessage = userName + " has left the chat";
            server.broadcast(currentRoom, serverMessage, this);

        } catch (IOException ex) {
            System.out.println("Error in UserThread: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public void sendMessage(String message) {
        writer.println(message);
    }
}
