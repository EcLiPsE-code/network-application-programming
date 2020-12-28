package by.gstu.itp.server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.net.Socket;

public class HttpClientHandler implements Runnable {
    private static final Logger logger = LogManager.getLogger();
    private final Socket clientSocket;

    public HttpClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }
    @Override
    public void run() {
        boolean flag = true;
        while(flag){
            try (HttpRequest in = new HttpRequest(clientSocket.getInputStream());
                HttpResponse out = new HttpResponse(clientSocket.getOutputStream())){
                switch (in.getUrlContextPath()) {
                    case "/":
                        String builder = "";
                        if (in.getMethod().equals("GET")) {
                            builder = "<p>Проверка пароля</p>" +
                                    "<form action='/' method='POST'>" +
                                    "<p>" +
                                    "<label>Введите пароль, который хотите проверить: </label>" +
                                    "<input name='password' type='password'>" +
                                    "<button>Проверить</button>" +
                                    "</p>" +
                                    "</form>";
                        } else if (in.getMethod().equals("POST")) {
                            String password = (String) in.getRawData().split("=")[1];
                            boolean resultCheckPassword = new Parser(password).checkPassword();
                            builder = "<p>Введенный пароль:</p>" +
                                    "<p>" +
                                    password+
                                    "</p>" +
                                    "<hr>" +
                                    "<p>Результат проверки папроля на сервере(true-подходит, false-не подходит)" +
                                    ":</p>" +
                                    "<p>" +
                                    resultCheckPassword +
                                    "</p>"
                            ;
                        }
                        out.sendText(builder);
                        break;
                    case "/exit":
                        clientSocket.close();
                        flag = false;
                        break;
                    default:
                        out.sendNotFound();
                }
                // по окончанию выполнения блока try-with-resources потоки,
                // а вместе с ними и соединение будут закрыты
                System.out.println("Client disconnected!");
            } catch (IOException e) {
                logger.error(e);
            }
        }
    }
}
