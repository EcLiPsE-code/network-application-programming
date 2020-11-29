using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace FTPServer.client
{
    public class ClientConnection
    {
        private TcpClient _controlClient;

        private NetworkStream _controlStream;
        private StreamReader _controlReader;
        private StreamWriter _controlWriter;

        private string _username;

        public ClientConnection(TcpClient client)
        {
            _controlClient = client;

            _controlStream = _controlClient.GetStream();

            _controlReader = new StreamReader(_controlStream);
            _controlWriter = new StreamWriter(_controlStream);
        }

        public void HandleClient(object obj)
        {
            _controlWriter.WriteLine("220 Service Ready.");
            _controlWriter.Flush();

            string line;

            try
            {
                while (!string.IsNullOrEmpty(line = _controlReader.ReadLine()))
                {
                    string response = null;

                    string[] command = line.Split(' ');

                    string cmd = command[0].ToUpperInvariant();
                    string arguments = command.Length > 1 ? line.Substring(command[0].Length + 1) : null;

                    if (string.IsNullOrWhiteSpace(arguments))
                        arguments = null;

                    if (response == null)
                    {
                        switch (cmd)
                        {
                            case "USER":
                                response = User(arguments);
                                break;
                            case "PASS":
                                response = Password(arguments);
                                break;
                            case "CWD":
                                response = ChangeWorkingDirectory(arguments);
                                break;
                            case "CDUP":
                                response = ChangeWorkingDirectory("..");
                                break;
                            case "PWD":
                                response = "257 \"/\" is current directory.";
                                break;
                            case "QUIT":
                                response = "221 Service closing control connection";
                                break;
                            case "LIST":
                                //Создаем объект запроса
                                FtpWebRequest ftpRequest = (FtpWebRequest)WebRequest.Create("ftp://" + "192.168.43.162" + "/");
                                //логин и пароль
                                //команда фтп LIST
                                ftpRequest.Method = WebRequestMethods.Ftp.ListDirectoryDetails;

                                //Получаем входящий поток
                                FtpWebResponse ftpResponse = (FtpWebResponse)ftpRequest.GetResponse();

                                //переменная для хранения всей полученной информации
                                string content = "";

                                StreamReader sr = new StreamReader(ftpResponse.GetResponseStream(), System.Text.Encoding.ASCII);
                                content = sr.ReadToEnd();
                                sr.Close();
                                ftpResponse.Close();

                                _controlWriter.WriteLine(content);
                                _controlWriter.Flush();
                                break;
                            case "RETR":
                                // Создаем объект FtpWebRequest
                                FtpWebRequest request = (FtpWebRequest)WebRequest.Create("ftp://192.168.43.162/../AngularJS/angular-1.8.0/angular-animate.js");
                                // устанавливаем метод на загрузку файлов
                                request.Method = WebRequestMethods.Ftp.DownloadFile;

                                // если требуется логин и пароль, устанавливаем их
                                //request.Credentials = new NetworkCredential("login", "password");
                                //request.EnableSsl = true; // если используется ssl

                                // получаем ответ от сервера в виде объекта FtpWebResponse
                                FtpWebResponse resp = (FtpWebResponse)request.GetResponse();

                                // получаем поток ответа
                                Stream responseStream = resp.GetResponseStream();
                                // сохраняем файл в дисковой системе
                                // создаем поток для сохранения файла
                                FileStream fs = new FileStream("newTest.txt", FileMode.Create);

                                //Буфер для считываемых данных
                                byte[] buffer = new byte[64];
                                int size = 0;

                                while ((size = responseStream.Read(buffer, 0, buffer.Length)) > 0)
                                {
                                    fs.Write(buffer, 0, size);

                                }
                                fs.Close();
                                resp.Close();

                                _controlWriter.WriteLine("Load and save file completed");
                                _controlWriter.Flush();
                                break;
                            default:
                                response = "502 Command not implemented";
                                break;
                        }
                    }

                    if (_controlClient == null || !_controlClient.Connected)
                    {
                        break;
                    }
                    else
                    {
                        if (response != null){
                            _controlWriter.WriteLine(response);
                            _controlWriter.Flush();

                            if (response.StartsWith("221"))
                            {
                                break;
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                throw;
            }
        }

        #region FTP Commands

        private string User(string username)
        {
            _username = username;

            return "331 Username ok, need password";
        }

        private string Password(string password)
        {
            if (true)
            {
                return "230 User logged in";
            }
            else
            {
                return "530 Not logged in";
            }
        }

        private string ChangeWorkingDirectory(string pathname)
        {
            return "250 Changed to new directory";
        }

        #endregion
    }
}

