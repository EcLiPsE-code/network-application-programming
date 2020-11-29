package by.gstu.itp.server.api;

import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;
import java.util.Vector;

@ServerEndpoint(value = "/websocket")
public class WebSocketServer {

    private static final Set<Session> clients = new HashSet<>();
    private static int nextId;

    public static void sendingMessagesToClients(String message) {
        synchronized (clients) {
            for (Session client : clients) {
                try {
                    client.getBasicRemote().sendText(message);
                } catch (IOException e) {
                    System.out.println("client error");
                    clients.remove(client);
                }
            }
        }
    }

    @OnMessage
    public void onMessage(String message, Session session) {
        String[] commandContent = message.split(":");
        try {
            switch (commandContent[0]) {
                case "check":
                    String password = commandContent[1].trim();
                    boolean resCheckPaass = new Parser(password).checkPassword();
                    new Thread(() -> sendingMessagesToClients("" + resCheckPaass)).start();
                    break;
                case "quit":
                    synchronized (clients) {
                        clients.remove(session);
                    }
                    break;
                default:
                    session.getBasicRemote().sendText("undefined command");
            }
        } catch (IOException e) {
            System.out.println("client error");
            synchronized (clients) {
                clients.remove(session);
            }
        } catch (Exception e) {
            System.out.println("msg error");
            System.out.println(e.toString());
        }
    }

    @OnOpen
    public void onOpen(Session session) {
        session.getUserProperties().put("username", "user_" + nextId++);
        String username = session.getUserProperties().get("username").toString();
        System.out.println(username + " connected to server");
        sendingMessagesToClients(username + " connected to server");

        synchronized (clients) {
            clients.add(session);
        }
    }

    @OnClose
    public void onClose(Session session) {
        synchronized (session) {
            clients.remove(session);
        }

        System.out.println("client disconnected: " + session.getUserProperties().get("username"));
    }

    @OnError
    public void onError(Session session, Throwable throwable ) {
        System.out.println("Error socket, maybe someone disconnected.");
    }
}
