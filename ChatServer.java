import java.io.*;
import java.net.*;
import java.util.*;

public class ChatServer {
    private int port;
    private Map<String, Set<UserThread>> chatRooms = new HashMap<>();

    public ChatServer(int port) {
        this.port = port;
    }

    public void execute() {
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Chat Server is listening on port " + port);

            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("New user connected");

                UserThread newUser = new UserThread(socket, this);
                newUser.start();
            }
        } catch (IOException ex) {
            System.out.println("Error in the server: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public static void main(String[] args) {
        int port = 8989;
        ChatServer server = new ChatServer(port);
        server.execute();
    }

    public void addUserToRoom(String roomName, UserThread user) {
        if (!chatRooms.containsKey(roomName)) {
            chatRooms.put(roomName, new HashSet<>());
        }
        chatRooms.get(roomName).add(user);
    }

    public void removeUserFromRoom(String roomName, UserThread user) {
        if (chatRooms.containsKey(roomName)) {
            chatRooms.get(roomName).remove(user);
        }
    }

    public void broadcast(String roomName, String message, UserThread excludeUser) {
        if (chatRooms.containsKey(roomName)) {
            for (UserThread user : chatRooms.get(roomName)) {
                if (user != excludeUser) {
                    user.sendMessage(message);
                }
            }
        }
    }
}
