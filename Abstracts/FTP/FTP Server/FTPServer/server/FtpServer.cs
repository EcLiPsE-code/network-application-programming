using FTPServer.client;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace FTPServer.server
{
    public class FtpServer
    {
        private TcpListener listener;

        public FtpServer() { }

        public void Start()
        {
            listener = new TcpListener(IPAddress.Any, 8000);
            listener.Start();
            listener.BeginAcceptTcpClient(HandleAcceptTcpClient, listener); //когда кто-то подклбчается
            Console.WriteLine("Server wait connection...");
        }

        ~FtpServer()
        {
            if (listener != null)
            {
                listener.Stop();
            }
        }

        private void HandleAcceptTcpClient(IAsyncResult result)
        {
            listener.BeginAcceptTcpClient(HandleAcceptTcpClient, listener);
            TcpClient client = listener.EndAcceptTcpClient(result);

            ClientConnection connection = new ClientConnection(client);

            ThreadPool.QueueUserWorkItem(connection.HandleClient, client);
        }
    }
}
